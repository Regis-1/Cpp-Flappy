#include "Logger.h"
#include <iostream>

void Logger::ILog(const std::string msg) {
	std::cout << msg << std::endl;
}

void Logger::ISuccess(const std::string msg, bool highlight) {
	std::string status = highlight ? ">>> [SUCCESS] " : "[SUCCESS] ";
	ILog(status + msg);
}

void Logger::IWarning(const std::string msg, bool highlight) {
	std::string status = highlight ? ">>> [WARNING] " : "[WARNING] ";
	ILog(status + msg);
}

void Logger::IError(const std::string msg, bool highlight) {
	std::string status = highlight ? ">>> [ERROR] " : "[ERROR] ";
	ILog(status + msg);
}

void Logger::IInfo(const std::string msg, bool highlight) {
	std::string status = highlight ? ">>> [INFO] " : "[INFO] ";
	ILog(status + msg);
}