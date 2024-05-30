#include "Logger.h"


// +---------------------------------------------------------------------------+
// | Constructor                                                               |
// +---------------------------------------------------------------------------+
Logger::Logger()
{

}

// +---------------------------------------------------------------------------+
// | Initialize()                                                              |
// +---------------------------------------------------------------------------+
void Logger::Initialize()
{
    // Set up logging to file
    //if (LogToFile)
    //{
    //    if (AppendLog)
    //        LogFile.open(LogFilePath, std::ios::out | std::ios::ate | std::ios::app);
    //    else
    //        LogFile.open(LogFilePath, std::ios::out | std::ios::trunc);
    //}

    // Create header format
    // [11.04.2012 11:11:11 Trace        Class.Member():  30]
    char header[1000];
    sprintf_s(header, "[%%s %%s %%%ds():%%4d]", HeaderFuctionWidth);

    // Convert C string (char[]) to C++ std::string
    HeaderFormat = header;

    Here(__FILE__, __FUNCTION__, __LINE__);
    //LogInformation("Log created");
}

// +---------------------------------------------------------------------------+
// | Finialize()                                                               |
// +---------------------------------------------------------------------------+
void Logger::Finialize()
{
    // Flush and close logging file
}

// +---------------------------------------------------------------------------+
// | Destructor                                                                |
// +---------------------------------------------------------------------------+
Logger::~Logger()
{
    //LogFile.close();
}


// +---------------------------------------------------------------------------+
// | Setters                                                                   |
// +---------------------------------------------------------------------------+

// +---------------------------------------------------------------------------+
// | SetLogLevel(LogLevel newLevel)                                            |
// +---------------------------------------------------------------------------+
void Logger::SetLogLevel(LogLevel newLevel)
{
    Level = newLevel;
}

// +---------------------------------------------------------------------------+
// | SetLogToConsole(bool logToConsole)                                        |
// +---------------------------------------------------------------------------+
void Logger::SetLogToConsole(bool logToConsole)
{
    LogToConsole = logToConsole;
}

// +---------------------------------------------------------------------------+
// | SetLogToFile(bool logToFile)                                              |
// +---------------------------------------------------------------------------+
void Logger::SetLogToFile(bool logToFile)
{
    LogToFile = logToFile;
}

// +---------------------------------------------------------------------------+
// | SetLogFilePath(std::string logFilePath)                                   |
// +---------------------------------------------------------------------------+
void Logger::SetLogFilePath(std::string logFilePath)
{
    LogFilePath = logFilePath;
}

// +---------------------------------------------------------------------------+
// | SetAppendExistingLog(bool append)                                         |
// +---------------------------------------------------------------------------+
void Logger::SetAppendExistingLog(bool append)
{
    AppendLog = append;
}

// +---------------------------------------------------------------------------+
// | SetHeaderFunctionWidth(int headerWidth)                                   |
// +---------------------------------------------------------------------------+
void Logger::SetHeaderFunctionWidth(int headerWidth)
{
    HeaderFuctionWidth = headerWidth;
}


// +---------------------------------------------------------------------------+
// | Logging methods                                                           |
// +---------------------------------------------------------------------------+

// +---------------------------------------------------------------------------+
// | LogTrace(std::string messageOrFormat, ...)                                |
// +---------------------------------------------------------------------------+
void Logger::LogTrace(std::string messageOrFormat, ...)
{
    if (!ShouldLog(LogLevel::Trace))
        return;

    va_list va;
    va_start(va, messageOrFormat);
    LogMessage(LogLevel::Trace, messageOrFormat, va);
    va_end(va);
}

// +---------------------------------------------------------------------------+
// | LogDebug(std::string messageOrFormat, ...)                                |
// +---------------------------------------------------------------------------+
void Logger::LogDebug(std::string messageOrFormat, ...)
{
    if (!ShouldLog(LogLevel::Debug))
        return;

    va_list va;
    va_start(va, messageOrFormat);
    LogMessage(LogLevel::Debug, messageOrFormat, va);
    va_end(va);
}

// +---------------------------------------------------------------------------+
// | LogInformation(std::string messageOrFormat, ...)                          |
// +---------------------------------------------------------------------------+
void Logger::LogInformation(std::string messageOrFormat, ...)
{
    if (!ShouldLog(LogLevel::Information))
        return;

    va_list va;
    va_start(va, messageOrFormat);
    LogMessage(LogLevel::Information, messageOrFormat, va);
    va_end(va);
}

// +---------------------------------------------------------------------------+
// | LogWarning(std::string messageOrFormat, ...)                              |
// +---------------------------------------------------------------------------+
void Logger::LogWarning(std::string messageOrFormat, ...)
{
    if (!ShouldLog(LogLevel::Warning))
        return;

    va_list va;
    va_start(va, messageOrFormat);
    LogMessage(LogLevel::Warning, messageOrFormat, va);
    va_end(va);
}

// +---------------------------------------------------------------------------+
// | LogError(std::string messageOrFormat, ...)                                |
// +---------------------------------------------------------------------------+
void Logger::LogError(std::string messageOrFormat, ...)
{
    if (!ShouldLog(LogLevel::Error))
        return;

    va_list va;
    va_start(va, messageOrFormat);
    LogMessage(LogLevel::Error, messageOrFormat, va);
    va_end(va);
}

// +---------------------------------------------------------------------------+
// | LogFatal(std::string messageOrFormat, ...)                                |
// +---------------------------------------------------------------------------+
void Logger::LogFatal(std::string messageOrFormat, ...)
{
    if (!ShouldLog(LogLevel::Fatal))
        return;

    va_list va;
    va_start(va, messageOrFormat);
    LogMessage(LogLevel::Fatal, messageOrFormat, va);
    va_end(va);
}

// +---------------------------------------------------------------------------+
// | Here()                                                                    |
// +---------------------------------------------------------------------------+
Logger* Logger::Here(std::string fileName, std::string functionName, int line)
{
    FileName = fileName;
    FunctionName = functionName;
    Line = line;
    return this;
}

// +---------------------------------------------------------------------------+
// | ShouldLog(LogLevel level)                                                 |
// +---------------------------------------------------------------------------+
bool Logger::ShouldLog(LogLevel level)
{
    bool shouldLog = level >= Level;
    return shouldLog;
}

// +---------------------------------------------------------------------------+
// | CreateHeader(LogLevel level)                                              |
// +---------------------------------------------------------------------------+
std::string Logger::CreateHeader(LogLevel level)
{
    // Get current date and time
    std::time_t currentTime = std::time(0);

    time_t rawtime;
    struct tm* timeinfo{};
    time(&rawtime);
    localtime_s(timeinfo, &rawtime);

    char buffer[80];
    strftime(buffer, 80, "Now it's %I:%M%p.", timeinfo);
    puts(buffer);



    // Create the header
    char header[1000];
    sprintf_s(header, HeaderFormat.c_str(), buffer, LogLevelToString.at(level), FunctionName, Line);

    return header;
}

// +---------------------------------------------------------------------------+
// | LogMessage(LogLevel level, std::string messageOrFormat, va_list args)     |
// +---------------------------------------------------------------------------+
void Logger::LogMessage(LogLevel level, std::string messageOrFormat, va_list args)
{
    char buffer[MAX_MESSAGE_LENGTH];
    vsprintf_s(buffer, messageOrFormat.c_str(), args);
    std::cout << buffer << std::endl;
}
