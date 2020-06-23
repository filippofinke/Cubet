#include "Logger.h"

#pragma region Public methods

void Logger::Log(const char* fmt, ...) {
	char buf[512];
	va_list arg_list;
	ZeroMemory(buf, sizeof(buf));
	va_start(arg_list, fmt);
	vsnprintf(buf, sizeof(buf), fmt, arg_list);
	va_end(arg_list);
	OutputDebugStringA(buf);
}

#pragma endregion