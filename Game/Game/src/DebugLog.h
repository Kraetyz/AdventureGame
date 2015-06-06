//Credits to Oscar Roosvall
#ifndef DEBUGLOG_HPP
#define DEGUBLOG_HPP
#include "Settings.h"
#include <fstream>
namespace Debug
{
	void OpenDebugStream(bool append, bool console, bool file);
	void DebugOutput(const char *format, ...);
	void CloseDebugStream();
}
#endif