#include <bits/stdc++.h>
using namespace std;

enum LogLevel
{
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

class LogMessage
{
public:
    LogLevel level;
    string message;
    time_t timestamp;

    LogMessage(LogLevel lvl, string msg)
    {
        level = lvl;
        message = msg;
        timestamp = time(nullptr);
    }
};

class LogFormatter
{
public:
    virtual string format(LogMessage *log) = 0;

    string getLevel(LogLevel level)
    {
        switch (level)
        {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARN:
            return "WARN";
        case ERROR:
            return "ERROR";
        case FATAL:
            return "FATAL";
        default:
            return "UNKNOWN";
        }
    }
};

class PlainTextFormatter : public LogFormatter
{
public:
    string format(LogMessage *log) override
    {
        tm *timeinfo = localtime(&log->timestamp);

        stringstream ss;
        ss << put_time(timeinfo, "%Y-%m-%d %H:%M:%S");

        return getLevel(log->level) + ": " + log->message + " at " + ss.str();
    }
};

class JSONFormatter : public LogFormatter
{
public:
    string format(LogMessage *log) override
    {
        tm *timeinfo = localtime(&log->timestamp);

        stringstream ss;
        ss << put_time(timeinfo, "%Y-%m-%d %H:%M:%S");

        return "{ \"level\":\"" + getLevel(log->level) +
               "\", \"message\":\"" + log->message +
               "\", \"time\":\"" + ss.str() + "\" }";
    }
};

class LogAppender
{
protected:
    LogFormatter *formatter;

public:
    LogAppender(LogFormatter *fmt)
    {
        formatter = fmt;
    }

    virtual void append(LogMessage *msg) = 0;
};

class ConsoleAppender : public LogAppender
{
public:
    ConsoleAppender(LogFormatter *fmt) : LogAppender(fmt) {}

    void append(LogMessage *msg) override
    {
        cout << formatter->format(msg) << endl;
    }
};

class FileAppender : public LogAppender
{
private:
    string filename;

public:
    FileAppender(string file, LogFormatter *fmt) : LogAppender(fmt)
    {
        filename = file;
    }

    void append(LogMessage *msg) override
    {
        ofstream out(filename, ios::app);
        out << formatter->format(msg) << endl;
        out.close();
    }
};

class LogHandler
{
protected:
    LogLevel level;
    vector<LogAppender *> appenders;
    LogHandler *next;

public:
    LogHandler(LogLevel lvl)
    {
        level = lvl;
        next = nullptr;
    }

    void setNext(LogHandler *n)
    {
        next = n;
    }

    void addAppender(LogAppender *app)
    {
        appenders.push_back(app);
    }

    virtual void handle(LogMessage *msg)
    {
        if (msg->level == level)
        {
            for (auto app : appenders)
                app->append(msg);
        }

        if (next)
            next->handle(msg);
    }
};

class Logger
{
private:
    static Logger *instance;
    LogHandler *chainStart;

    Logger()
    {
        chainStart = nullptr;
    }

public:
    static Logger *getInstance()
    {
        if (!instance)
            instance = new Logger();
        return instance;
    }

    void setChain(LogHandler *start)
    {
        chainStart = start;
    }

    void log(LogLevel level, string message)
    {
        if (!chainStart)
            return;

        LogMessage *msg = new LogMessage(level, message);
        chainStart->handle(msg);
        delete msg;
    }

    void info(string msg) { log(INFO, msg); }
    void warn(string msg) { log(WARN, msg); }
    void error(string msg) { log(ERROR, msg); }
};

Logger *Logger::instance = nullptr;

int main()
{
    LogFormatter *textFormatter = new PlainTextFormatter();
    LogFormatter *jsonFormatter = new JSONFormatter();

    LogAppender *consoleText = new ConsoleAppender(textFormatter);
    LogAppender *fileJson = new FileAppender("logs.txt", jsonFormatter);

    LogHandler *infoHandler = new LogHandler(INFO);
    LogHandler *warnHandler = new LogHandler(WARN);
    LogHandler *errorHandler = new LogHandler(ERROR);

    infoHandler->addAppender(consoleText);
    warnHandler->addAppender(consoleText);
    errorHandler->addAppender(consoleText);
    errorHandler->addAppender(fileJson);

    infoHandler->setNext(warnHandler);
    warnHandler->setNext(errorHandler);

    Logger *logger = Logger::getInstance();
    logger->setChain(infoHandler);

    logger->info("System started");
    logger->warn("Memory getting high");
    logger->error("Database crashed");

    return 0;
}
