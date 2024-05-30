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
// | Defines                                                                   |
// +---------------------------------------------------------------------------+
#define Log Logger.Here(__FILE__, __func__, __LINE__)
#define MAX_MESSAGE_LENGTH 1000


// +---------------------------------------------------------------------------+
// | Includes                                                                  |
// +---------------------------------------------------------------------------+
#include <iostream>
#include <cstdarg>
#include <string>
#include <map>
#include <ctime>


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
    void Initialize();
    void Finialize();
    ~Logger();

    // Setters
    void SetLogLevel(LogLevel newLevel);
    void SetLogToConsole(bool logToConsole);
    void SetLogToFile(bool logToFile);
    void SetLogFilePath(std::string logFilePath);
    void SetAppendExistingLog(bool append);
    void SetHeaderFunctionWidth(int headerWidth);

    // Logging methods
    void LogTrace(std::string messageOrFormat, ...);
    void LogDebug(std::string messageOrFormat, ...);
    void LogInformation(std::string messageOrFormat, ...);
    void LogWarning(std::string messageOrFormat, ...);
    void LogError(std::string messageOrFormat, ...);
    void LogFatal(std::string messageOrFormat, ...);

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

    LogLevel Level = LogLevel::Information;
    bool LogToConsole = true;
    bool LogToFile = false;
    std::string LogFilePath = "";
    bool AppendLog = true;
    int HeaderFuctionWidth = 40;
    std::string HeaderFormat = "";

    std::string FileName;
    std::string FunctionName;
    int Line = 0;

    //std::ofstream LogFile;

    bool ShouldLog(LogLevel level);
    std::string CreateHeader(LogLevel level);
    void LogMessage(LogLevel level, std::string format, va_list args);
};

#endif // LOGGER_H