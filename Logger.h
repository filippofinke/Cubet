#pragma once
#include <Windows.h>
#include <stdio.h>

#define LOG(prefix, message, ...) Logger::Log("Cubet - " ## prefix ## " - " ## message, __VA_ARGS__)
#define LOG_DEBUG(message, ...) LOG("Debug", message, __VA_ARGS__)
#define LOG_INFO(message, ...) LOG("Info", message, __VA_ARGS__)
#define LOG_WARN(message, ...) LOG("Warn", message, __VA_ARGS__)
#define LOG_ERROR(message, ...) LOG("Error", message, __VA_ARGS__)
#define LOG_FATAL(message, ...) LOG("Fatal", message, __VA_ARGS__)

class Logger
{
public:
	static void Log(const char* fmt, ...);
};

