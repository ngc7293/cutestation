#ifndef LOG_H_
#define LOG_H_

#include <mutex>
#include <string>
#include <ostream>

// namespace cute {

class Log {
public:
    enum Level {
        DEBUG = -1,
        INFO = 0,
        WARNING = 1,
        ERROR = 2,
        MAX = 99
    };

public:
    /** get
     * @return the Log singleton
     */
    static Log& get();

    static std::ostream& debug(const std::string& component, const std::string& message = "");
    static std::ostream& info(const std::string& component, const std::string& message = "");
    static std::ostream& warn(const std::string& component, const std::string& message = "");
    static std::ostream& err(const std::string& component, const std::string& message = "");

public:
    ~Log();

    std::ostream& log(Level level, const std::string& component, const std::string& message = "");

private:
    Log();

private:
    std::mutex mutex;
};

// } // namespace

#endif