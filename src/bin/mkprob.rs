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

use std::collections::HashMap;
use std::env;
use std::fs::File;
use std::io::Write;
use std::path::PathBuf;

#[macro_use]
extern crate error_chain;

#[macro_use]
extern crate log;

extern crate bdrck_log;

extern crate bdrck_params;
use self::bdrck_params::*;

extern crate euler;
use self::euler::util::error::*;

static TEMPLATE: &'static str = include_str!("problem_template.rs.txt");

const MAX_PROBLEM: u64 = 99999;

fn to_problem_name(problem_arg: &str) -> Result<String> {
    let n: u64 = problem_arg.parse()?;
    if n > MAX_PROBLEM {
        bail!("Problem number {} is too large", n);
    }
    Ok(format!("{:05}", n))
}

fn get_source_root() -> Result<PathBuf> {
    let mut path = env::current_exe()?.canonicalize()?;
    while !path.ends_with("target") {
        if !path.pop() {
            bail!("Failed to locate source directory");
        }
    }

    if !path.pop() {
        bail!("Failed to locate source directory");
    }

    Ok(path)
}

fn mkprob(
    _: HashMap<String, String>,
    _: HashMap<String, bool>,
    arguments: HashMap<String, Vec<String>>,
) -> Result<()> {
    let vs = arguments.get("number").unwrap();
    assert!(vs.len() == 1);
    let mut problem_file = to_problem_name(vs.first().unwrap().as_str()).unwrap();
    problem_file.push_str(".rs");

    let mut problem_path = get_source_root().unwrap();
    problem_path.push("src");
    problem_path.push("bin");
    problem_path.push(problem_file);
    info!("Writing problem: {}", problem_path.to_str().unwrap());
    if problem_path.exists() {
        bail!("Problem already exists");
    }

    let mut f = File::create(problem_path.as_path()).unwrap();
    f.write_all(TEMPLATE.as_bytes()).unwrap();

    Ok(())
}

fn main() {
    bdrck_log::init_debug_logger().unwrap();

    main_impl_single_command(ExecutableCommand::new(
        Command::new(
            "mkprob",
            "Create a new ProjectEuler \
             problem",
            vec![],
            vec![
                Argument::new("number", "The number of the problem to create", None),
            ],
            false,
        ).unwrap(),
        Box::new(mkprob),
    ));
}
