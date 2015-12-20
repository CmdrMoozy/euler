/*
 * euler - A collection of ProjectEuler libraries, tools, and solutions.
 * Copyright (C) 2013 Axel Rasmussen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstddef>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <bdrck/fs/Util.hpp>
#include <bdrck/params/Argument.hpp>
#include <bdrck/params/Command.hpp>
#include <bdrck/params/Option.hpp>
#include <bdrck/params/parseAndExecute.hpp>

#include "common/util/Path.hpp"

namespace
{
constexpr int MAX_PROBLEM = 9999;
constexpr std::size_t PROBLEM_FIELD_WIDTH = 4;

// clang-format off
constexpr char const *PROBLEM_TEMPLATE[] = {
"/""*"										,
" * euler - A collection of ProjectEuler libraries, tools, and solutions."	,
" * Copyright (C) 2013 Axel Rasmussen"						,
" *"										,
" * This program is free software: you can redistribute it and/or modify"	,
" * it under the terms of the GNU General Public License as published by"	,
" * the Free Software Foundation, either version 3 of the License, or"		,
" * (at your option) any later version."					,
" *"										,
" * This program is distributed in the hope that it will be useful,"		,
" * but WITHOUT ANY WARRANTY; without even the implied warranty of"		,
" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"		,
" * GNU General Public License for more details."				,
" *"										,
" * You should have received a copy of the GNU General Public License"		,
" * along with this program.  If not, see <http://www.gnu.org/licenses/>."	,
" *""/"									,
""										,
"#include \"common/util/Process.hpp\""						,
""										,
"namespace"									,
"{"										,
"constexpr int EXPECTED_RESULT = 0;"						,
""										,
"euler::util::process::ProblemResult<int> problem()"				,
"{"										,
"\treturn {0, EXPECTED_RESULT};"						,
"}"										,
"}"										,
""										,
"EULER_PROBLEM_ENTRYPOINT"
};
// clang-format on

constexpr std::size_t PROBLEM_TEMPLATE_LINE_LENGTH =
        sizeof(PROBLEM_TEMPLATE) / sizeof(char const *);

constexpr char const *CMAKE_TEMPLATE = "eulerAddProblem()";

std::string toProblemName(std::string const &problemArg)
{
	int problem = std::stoi(problemArg);
	if((problem <= 0) || (problem > MAX_PROBLEM))
	{
		throw std::runtime_error(
		        "Problem number must be in the range [1, 9999].");
	}

	std::ostringstream oss;
	oss << std::setw(PROBLEM_FIELD_WIDTH) << std::setfill('0') << problem;
	return oss.str();
}

void mkprobCommand(bdrck::params::OptionsMap const &,
                   bdrck::params::FlagsMap const &,
                   bdrck::params::ArgumentsMap const &args)
{
	// Just double-check that our source path is correct (this binary must
	// have been built without later moving the source directory).
	std::string sourceDirectory = euler::util::path::sourcePath({"src"});
	if(!bdrck::fs::exists(sourceDirectory))
		throw std::runtime_error("Source directory doesn't exist!");

	std::string problem = toProblemName(args.at("number")[0]);
	std::string doneProblemDirectory =
	        bdrck::fs::combinePaths({sourceDirectory, "done", problem});
	std::string newProblemDirectory =
	        bdrck::fs::combinePaths({sourceDirectory, "new", problem});

	// Ensure the problem doesn't already exist.
	if(bdrck::fs::exists(doneProblemDirectory) ||
	   bdrck::fs::exists(newProblemDirectory))
	{
		throw std::runtime_error("Problem already exists!");
	}

	std::string cppPath =
	        bdrck::fs::combinePaths(newProblemDirectory, "main.cpp");
	std::string cmakePath =
	        bdrck::fs::combinePaths(newProblemDirectory, "CMakeLists.txt");

	bdrck::fs::createPath(newProblemDirectory);

	// Write the C++ source file.
	std::ofstream cppOut(cppPath, std::ios::out | std::ios::binary |
	                                      std::ios::trunc);
	if(!cppOut.is_open())
	{
		throw std::runtime_error(
		        "Opening CPP file for writing failed.");
	}
	for(std::size_t i = 0; i < PROBLEM_TEMPLATE_LINE_LENGTH; ++i)
		cppOut << PROBLEM_TEMPLATE[i] << "\n";
	cppOut.flush();
	cppOut.close();

	// Write the CMake build file.
	std::ofstream cmakeOut(cmakePath, std::ios::out | std::ios::binary |
	                                          std::ios::trunc);
	if(!cmakeOut.is_open())
	{
		throw std::runtime_error(
		        "Opening CMake file for writing failed.");
	}
	cmakeOut << CMAKE_TEMPLATE << "\n";
	cmakeOut.flush();
	cmakeOut.close();
}

const std::vector<bdrck::params::Argument> MKPROB_COMMAND_ARGUMENTS{
        bdrck::params::Argument("number",
                                "The number of the problem to create.")};

const bdrck::params::Command MKPROB_COMMAND("mkprob",
                                            "Create a new ProjectEuler problem",
                                            mkprobCommand, {},
                                            MKPROB_COMMAND_ARGUMENTS);
}

int main(int argc, char const *const *argv)
{
	return bdrck::params::parseAndExecute(argc, argv, MKPROB_COMMAND);
}
