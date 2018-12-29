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

use bdrck::flags::*;
use euler::util::error::*;
use failure::bail;
use std::env;
use std::fs::File;
use std::io::Write;
use std::path::PathBuf;

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

fn mkprob(values: Values) -> Result<()> {
    let problem_file = format!(
        "{}.rs",
        to_problem_name(values.get_positional_single("number"))?
    );
    let mut problem_path = get_source_root().unwrap();
    problem_path.push("src");
    problem_path.push("bin");
    problem_path.push(problem_file);
    println!("Writing problem: {}", problem_path.to_str().unwrap());
    if problem_path.exists() {
        bail!("Problem already exists");
    }

    let mut f = File::create(problem_path.as_path()).unwrap();
    f.write_all(TEMPLATE.as_bytes()).unwrap();

    Ok(())
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

    main_impl_single_command(Command::new(
        "mkprob",
        "Create a new ProjectEuler problem",
        Specs::new(vec![Spec::positional(
            "number",
            "The number of the problem to create",
            None,
            false,
        )
        .unwrap()])
        .unwrap(),
        Box::new(mkprob),
    ));
}
