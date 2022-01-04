#pragma once
#include <string>

class Logger {
private:

	//Hidden constructor
	Logger() {};

	//Internal methods
	void ISuccess(const std::string msg, bool highlight);
	void IWarning(const std::string msg, bool highlight);
	void IError(const std::string msg, bool highlight);
	void IInfo(const std::string msg, bool highlight);
	void ILog(const std::string msg);

public:
	//Deleted copy constructor
	Logger(const Logger&) = delete;

	//Delete assign operator
	void operator=(const Logger&) = delete;

	//Get method to retreive instance of singleton
	static Logger& Get() {
		static Logger instance;
		return instance;
	}

	//Public methods for functionality
	static void Success(const std::string msg, bool highlight = false) { Get().ISuccess(msg, highlight); }
	static void Warning(const std::string msg, bool highlight = false) { Get().IWarning(msg, highlight); }
	static void Error(const std::string msg, bool highlight = false) { Get().IError(msg, highlight); }
	static void Info(const std::string msg, bool highlight = false) { Get().IInfo(msg, highlight); }
};