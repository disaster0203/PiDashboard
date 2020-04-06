#pragma once

#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <array>

#include "../exceptions/HALException.h"

namespace hal
{
	namespace utils
	{
		//! Provides access to the Linux terminal and allows to pass commands to it.
		/*!
		* Provides access to the Linux terminal and allows to pass commands to it.
		*/
		class TerminalAccess
		{
		public:
			//! Executes the given command in a Linux terminal process.
			/*!
			* Executes the given command in a Linux terminal process and returns the result of the command.
			* \returns The result of the command.
			* \throws HALException if calling popen() fails.
			*/
			static std::string call_command(const std::string& cmd)
			{
				std::array<char, 128> buffer{};
				std::string result;
				const std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
				if (!pipe) {
					throw exception::HALException("TerminalAccess", "call_command", "popen() failed!");
				}
				while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
					result += buffer.data();
				}

				// Remove \n at end of result
				const auto start_pos = result.find('\n');
				if (start_pos != std::string::npos)
				{
					return result.replace(start_pos, 2, "");
				}
				return result;
			}
		};
	}
}