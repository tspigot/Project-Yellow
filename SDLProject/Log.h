#pragma once
#include <string>
#include <stdio.h>
#include <stdarg.h>
#ifndef _LOG_H_
#define _LOG_H_

namespace Log
{
	enum Level {
		LOG_LEVEL_DEBUG,
		LOG_LEVEL_NORMAL
	};

	void init(Log::Level l);
	void cleanup();

	void _Infof(const char *format, const char *file, const int line, ...);
	#define Infof(fmt, ...) _Infof(fmt, __FILE__, __LINE__, ##__VA_ARGS__)
	void _Errorf(const char *format, const char *file, const int line, ...);
	#define Errorf(fmt, ...) _Errorf(fmt, __FILE__, __LINE__, ##__VA_ARGS__)
};
#endif