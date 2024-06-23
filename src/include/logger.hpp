#pragma once
#ifndef LOGGER_H
#define LOGGER_H


#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
namespace seng {

	enum class log_level {
		debug,
		info,
		warning,
		error,
		critical
	};
	class logger {
	public:
		explicit logger(const std::string& name = "physics_log_file.log") : log_file_(name) {}
		void log(log_level level, const std::string& message);
		~logger();
	private:
		std::ofstream log_file_;
	};
}
#endif // !LOGGER_H