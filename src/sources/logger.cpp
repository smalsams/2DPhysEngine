#include "logger.hpp"

void seng::logger::log(seng::log_level level, const std::string& message)
{
	const auto now = std::chrono::system_clock::now();
	time_t tt = std::chrono::system_clock::to_time_t(now);
	const auto local_time = std::localtime(&tt);
	std::stringstream ss;
	ss << std::put_time(local_time, "%Y-%m-%d %H:%M:%S ");
	const auto result = ss.str();
	switch (level)
	{
	case seng::log_level::info:
		log_file_ << "[INFO] " << result << message << std::endl;
		break;
	case log_level::warning:
		log_file_ << "[WARNING] " << result << message << std::endl;
		break;
	case log_level::error:
		log_file_ << "[ERROR] " << result << message << std::endl;
		break;
	case log_level::debug:
		log_file_ << "[DEBUG] " << result << message << std::endl;
		break;
	case log_level::critical:
		log_file_ << "[CRITICAL] " << result << message << std::endl;
		break;
	}
}

seng::logger::~logger()
{
	log_file_.close();
}

