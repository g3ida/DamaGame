#pragma once

#define LOGGING

#ifdef LOGGING

	#include "Logger.h"

	#define LOG Logger::print<Logger::Severity::debug>
	#define LOG_ERR Logger::print<Logger::Severity::error>
	#define LOG_WARN Logger::print<Logger::Severity::warning>

#else

	#define LOG(...)
	#define LOG_ERR(...)
	#define LOG_WARN(...)

#endif
