#pragma once

#include <ostream>
#include <sstream>
#include <string>
//#include <thread>
//#include <mutex>

class Logger
{
public:
	enum class Severity
	{
		debug,
		error,
		warning
	};

	template<Logger::Severity severity, typename...Args>
	static void print(Args...args);

	// disable construction
	Logger() = delete;

private :
	static unsigned int m_log_line_number;

	static std::string get_time();
	static std::string get_logline_header();

	static std::stringstream m_log_stream;
	static void write(std::ostream& s, const std::string& msg);

	// to be thread safe
	//static std::mutex m_write_mutex;

	// core printing functionality
	static void print_impl();
	template<typename First, typename...Rest>
	static void print_impl(First parm1, Rest...parm);
};

template<typename First, typename...Rest>
void
Logger::print_impl(First parm1, Rest...parm)
{
	m_log_stream << parm1;
	print_impl(parm...);
}

template< Logger::Severity severity , typename...Args >
void
Logger::print( Args...args )
{
	//m_write_mutex.lock();
	switch( severity )
	{
		case Severity::debug:
			m_log_stream << "<DEBUG> :";
			break;
		case Severity::warning:
			m_log_stream << "<WARNING> :";
			break;
		case Severity::error:
			m_log_stream << "<ERROR> :";
			break;
	};
	print_impl( args... );
	//m_write_mutex.unlock();
}
