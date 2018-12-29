// Copyright 2013 Axel Rasmussen
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use euler::math::stats;
use euler::util::duration::Duration;
use euler::util::error::*;
use euler::util::problem;
use euler::util::profiler::Profiler;
use failure::bail;
use std::collections::HashMap;
use std::env;
use std::os::unix::fs::PermissionsExt;
use std::path::PathBuf;
use std::process;
use std::time;

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
        percentiles.insert(
            *percentile,
            results[(percentile * results.len()) / 100].time.clone(),
        );
    }
    percentiles
}

impl Timings {
    fn new(results: &Vec<ExecutionResult>) -> Timings {
        Timings {
            successes: results.iter().filter(|r| r.success).count(),

            average: Duration::from_total_nanos(
                stats::iaverage(results.iter().map(|r| r.time.total_nanos())).unwrap_or(0),
            ),
            minimum: results
                .iter()
                .map(|r| r.time.clone())
                .min()
                .unwrap_or(Duration::from(time::Duration::new(0, 0))),
            maximum: results
                .iter()
                .map(|r| r.time.clone())
                .max()
                .unwrap_or(Duration::from(time::Duration::new(0, 0))),
            stddev: Duration::from_total_nanos(
                stats::istddev_population(results.iter().map(|r| r.time.total_nanos()))
                    .unwrap_or(0),
            ),
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
            println!(
                "PROBLEM FAILED: {}",
                path.file_name().unwrap().to_str().unwrap()
            );
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
    let debug: bool = cfg!(debug_assertions);
    bdrck::logging::init(
        bdrck::logging::OptionsBuilder::new()
            .set_filters(match debug {
                false => "warn".parse().unwrap(),
                true => "debug".parse().unwrap(),
            })
            .set_panic_on_output_failure(debug)
            .set_always_flush(true)
            .build()
            .unwrap(),
    );

    if debug {
        println!("Problems were built in debug mode. Timings may not be useful.");
    }

    let mut results = execute_problems().unwrap();
    results.sort_by(|a, b| a.time.cmp(&b.time));
    let timings = Timings::new(&results);

    println!(
        "Executed {} problems ({} successes, {} failures).",
        results.len(),
        timings.successes,
        results.len() - timings.successes
    );
    println!(
        "Execution time: average {}, min {}, max {}, stddev {}, total {}",
        timings.average, timings.minimum, timings.maximum, timings.stddev, timings.total
    );
    for percentile in PERCENTILES {
        println!(
            "{}th percentile execution time: {}",
            percentile,
            timings.percentiles.get(percentile).unwrap()
        );
    }

    println!("Top {} slowest problems:", TOP_N_SLOWEST);
    for result in results.iter().rev().take(TOP_N_SLOWEST) {
        println!("{} ({})", result.problem, result.time);
    }

    process::exit(match timings.successes == results.len() {
        false => problem::EXIT_FAILURE,
        true => problem::EXIT_SUCCESS,
    });
}
