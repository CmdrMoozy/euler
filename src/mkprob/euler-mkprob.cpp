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

#include <iostream>
#include <vector>

#include <bdrck/params/Argument.hpp>
#include <bdrck/params/Command.hpp>
#include <bdrck/params/Option.hpp>
#include <bdrck/params/parseAndExecute.hpp>

namespace
{
void mkprobCommand(bdrck::params::OptionsMap const &,
                   bdrck::params::FlagsMap const &,
                   bdrck::params::ArgumentsMap const &)
{
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
