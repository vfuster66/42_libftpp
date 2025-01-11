#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

class Logger {
public:
    enum Level {
        INFO,
        WARNING,
        ERROR
    };

private:
    Level currentLevel;

    std::string getTimestamp() const {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm localTime{};
        localtime_r(&time, &localTime);

        std::ostringstream oss;
        oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    std::string levelToString(Level level) const {
        switch (level) {
            case INFO: return "INFO";
            case WARNING: return "WARNING";
            case ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }

public:
    Logger() : currentLevel(INFO) {}

    void setLevel(Level level) {
        currentLevel = level;
    }

    void log(Level level, const std::string &message) const {
        if (level >= currentLevel) {
            std::cout << "[" << getTimestamp() << "] [" << levelToString(level) << "] " << message << std::endl;
        }
    }

    void info(const std::string &message) const {
        log(INFO, message);
    }

    void warning(const std::string &message) const {
        log(WARNING, message);
    }

    void error(const std::string &message) const {
        log(ERROR, message);
    }
};

#endif // LOGGER_HPP
