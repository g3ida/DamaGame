#include "logger.h"
#include <iostream>
#include <ctime>

unsigned int Logger::m_log_line_number = 0;
std::stringstream Logger::m_log_stream;


void
Logger::write(std::ostream& s, const std::string& msg)
{
	s << msg;
	//s.flush();
}

void
Logger::print_impl()
{
	write(std::cout, get_logline_header() + m_log_stream.str());
	m_log_stream.str("");
}

std::string
Logger::get_time()
{
	std::string time_str;
	time_t raw_time;

	time( & raw_time );
	time_str = ctime( &raw_time );

	//without the newline character
	return time_str.substr( 0 , time_str.size() - 1 );
}

std::string
Logger::get_logline_header()
{
	std::stringstream header;

	header.str("");
	header.fill('0');
	header.width(7);
	header << m_log_line_number++ << " < " << get_time() << " - ";

	header.fill('0');
	header.width(7);
	header << clock() << " > ~ ";

	return header.str();
}
