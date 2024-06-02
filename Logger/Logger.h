// +---------------------------------------------------------------------------+
// | Matthew Anderson, Copyright 2021                                          |
// | U64025757                                                                 |
// | Logging utility                                                           |
// | Version History                                                           |
// | 1.0             Original created in MQL for MT4 circa 2021                |
// | 1.1             Rewritten in C++                                          |
// |                 Logging to file not implemented                           |
// +---------------------------------------------------------------------------+


// +---------------------------------------------------------------------------+
// | Include Guard                                                             |
// +---------------------------------------------------------------------------+
#pragma once

#ifndef LOGGER_H
#define LOGGER_H


// +---------------------------------------------------------------------------+
// | Includes                                                                  |
// +---------------------------------------------------------------------------+
#include <iostream>
#include <cstdarg>
#include <string>
#include <map>
#include <ctime>
//#include <vector>


// +---------------------------------------------------------------------------+
// | Namespace                                                                 |
// +---------------------------------------------------------------------------+
namespace Anderson
{
    namespace Logging
    {


// +---------------------------------------------------------------------------+
// | Defines                                                                   |
// +---------------------------------------------------------------------------+
#define Log Logger->Here(__FILE__, __func__, __LINE__)
#define MAX_MESSAGE_LENGTH 1000


// +---------------------------------------------------------------------------+
// | Enums                                                                     |
// +---------------------------------------------------------------------------+
enum LogLevel
{
    Trace = 0,
    Debug = 1,
    Information = 2,
    Warning = 3,
    Error = 4,
    Fatal = 5,
    None = 6
};


// +---------------------------------------------------------------------------+
// | class Logger                                                              |
// +---------------------------------------------------------------------------+
class Logger
{
public:
    Logger();
    Logger(LogLevel level, std::string className);
    void Initialize();
    void Finialize();
    ~Logger();

    // Setters
    void SetLogLevel(LogLevel newLevel);
    void SetLogToConsole(bool logToConsole);
    void SetLogToFile(bool logToFile);
    void SetLogFilePath(std::string logFilePath);
    void SetAppendExistingLog(bool append);
    void SetClassName(std::string className);
    void SetHeaderFunctionWidth(int headerWidth);
    bool IsInitialized();

    // Logging methods
    void LogTrace(std::string messageOrFormat, ...);
    void LogDebug(std::string messageOrFormat, ...);
    void LogInformation(std::string messageOrFormat, ...);
    void LogWarning(std::string messageOrFormat, ...);
    void LogError(std::string messageOrFormat, ...);
    void LogFatal(std::string messageOrFormat, ...);

    // Helper methods
    bool WillLog(LogLevel level);
    //template <typename T>
    //std::string VectorToString(std::vector<T> v);

    Logger* Here(std::string file, std::string function, int line);
private:
    const std::map<LogLevel, std::string> LogLevelToString =
    {
        { LogLevel::Trace, "TRACE" },
        { LogLevel::Debug, "DEBUG" },
        { LogLevel::Information, "INFO" },
        { LogLevel::Warning, "WARN" },
        { LogLevel::Error, "ERROR" },
        { LogLevel::Fatal, "FATAL" },
    };

    bool Initialized = false;
    LogLevel Level = LogLevel::Information;
    bool LogToConsole = true;
    bool LogToFile = false;
    std::string LogFilePath = "";
    bool AppendLog = true;
    int HeaderFuctionWidth = 40;
    std::string HeaderFormat = "";

    std::string ClassName = "";
    std::string FileName;
    std::string FunctionName;
    int Line = 0;

    //std::ofstream LogFile;

    bool ShouldLog(LogLevel level);
    std::string CreateHeader(LogLevel level);
    void LogMessage(LogLevel level, std::string format, va_list args);
};

#endif // LOGGER_H
    } // namespace Logging
} // namespace Anderson