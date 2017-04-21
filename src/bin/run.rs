// euler - A collection of ProjectEuler libraries, tools, and solutions.
// Copyright (C) 2013 Axel Rasmussen
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

use std::collections::HashMap;
use std::env;
use std::os::unix::fs::PermissionsExt;
use std::path::PathBuf;
use std::process;
use std::string::String;
use std::time;
use std::vec::Vec;

#[macro_use]
extern crate error_chain;

extern crate glob;

#[macro_use]
extern crate log;

extern crate bdrck_log;

extern crate euler;
use self::euler::math::stats;
use self::euler::util::duration::Duration;
use self::euler::util::error::*;
use self::euler::util::problem;
use self::euler::util::profiler::Profiler;

const TOP_N_SLOWEST: usize = 10;

struct ExecutionResult {
    problem: String,
    time: Duration,
    success: bool,
}

struct Timings {
    successes: usize,

    average: Duration,
    minimum: Duration,
    maximum: Duration,
    stddev: Duration,
    total: Duration,

    percentiles: HashMap<usize, Duration>,
}

const PERCENTILES: &'static [usize] = &[50, 75, 85, 95, 99];

fn compute_percentiles(results: &Vec<ExecutionResult>) -> HashMap<usize, Duration> {
    if results.is_empty() {
        return HashMap::new();
    }

    let mut percentiles: HashMap<usize, Duration> = HashMap::new();
    for percentile in PERCENTILES {
        percentiles.insert(*percentile,
                           results[(percentile * results.len()) / 100].time.clone());
    }
    percentiles
}

impl Timings {
    fn new(results: &Vec<ExecutionResult>) -> Timings {
        Timings {
            successes: results.iter().filter(|r| r.success).count(),

            average: Duration::from_total_nanos(stats::iaverage(results.iter()
                    .map(|r| r.time.total_nanos()))
                .unwrap_or(0)),
            minimum: results.iter()
                .map(|r| r.time.clone())
                .min()
                .unwrap_or(Duration::from(time::Duration::new(0, 0))),
            maximum: results.iter()
                .map(|r| r.time.clone())
                .max()
                .unwrap_or(Duration::from(time::Duration::new(0, 0))),
            stddev: Duration::from_total_nanos(stats::istddev_population(results.iter()
                    .map(|r| r.time.total_nanos()))
                .unwrap_or(0)),
            total: results.iter().map(|r| &r.time).sum(),

            percentiles: compute_percentiles(&results),
        }
    }
}

fn get_target_root() -> Result<PathBuf> {
    let mut path = env::current_exe()?.canonicalize()?;
    if !path.pop() {
        bail!("Failed to locate targets directory");
    }
    Ok(path)
}

fn execute_problems() -> Result<Vec<ExecutionResult>> {
    let mut results: Vec<ExecutionResult> = Vec::new();
    for p in glob::glob(format!("{}/?????", get_target_root()?.to_str().unwrap()).as_str())? {
        let path = p?;
        let metadata = path.metadata()?;
        if metadata.is_dir() || metadata.permissions().mode() & 0o111 == 0 {
            continue;
        }

        let profiler = Profiler::new(false, "");
        let output = process::Command::new(path.to_str().unwrap()).output()?;
        if !output.status.success() {
            warn!("PROBLEM FAILED: {}",
                  path.file_name().unwrap().to_str().unwrap());
        }
        results.push(ExecutionResult {
            problem: path.file_name().unwrap().to_str().unwrap().to_owned(),
            time: profiler.get_elapsed(),
            success: output.status.success(),
        });
    }
    Ok(results)
}

fn main() {
    bdrck_log::init_debug_logger().unwrap();

    if cfg!(debug_assertions) {
        warn!("Problems were built in debug mode. Timings may not be useful.");
    }

    let mut results = execute_problems().unwrap();
    results.sort_by(|a, b| a.time.cmp(&b.time));
    let timings = Timings::new(&results);

    info!("Executed {} problems ({} successes, {} failures).",
          results.len(),
          timings.successes,
          results.len() - timings.successes);
    info!("Execution time: average {}, min {}, max {}, stddev {}, total {}",
          timings.average,
          timings.minimum,
          timings.maximum,
          timings.stddev,
          timings.total);
    for percentile in PERCENTILES {
        info!("{}th percentile execution time: {}",
              percentile,
              timings.percentiles.get(percentile).unwrap());
    }

    info!("Top {} slowest problems:", TOP_N_SLOWEST);
    for result in results.iter().rev().take(TOP_N_SLOWEST) {
        info!("{} ({})", result.problem, result.time);
    }

    process::exit(match timings.successes == results.len() {
        false => problem::EXIT_FAILURE,
        true => problem::EXIT_SUCCESS,
    });
}
