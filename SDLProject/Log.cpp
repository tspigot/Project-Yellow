#include "Log.h"
#include <fstream>
#include <string>
#include <sstream>

static FILE *file;
static Log::Level level;

void Log::init(Log::Level l) {
	file = fopen("log.txt", "w");
	level = l;
}

void Log::cleanup() {
	fclose(file);
}

void Log::_Errorf(const char *format, const char *filename, const int line, ...) {
	va_list arglist;
	va_start(arglist, line);
	std::stringstream ss;
	ss << "ERROR: " << filename << ": " << line << ": " << format << std::endl;
	vfprintf(file, ss.str().c_str(), arglist);
	fflush(file);
	va_end(arglist);
}

void Log::_Infof(const char *format, const char *filename, const int line, ...) {
	va_list arglist;
	va_start(arglist, line);
	std::stringstream ss;
	ss << "INFO: " << filename << ": " << line << ": " << format << std::endl;
	vfprintf(file, ss.str().c_str(), arglist);
	fflush(file);
	va_end(arglist);
}