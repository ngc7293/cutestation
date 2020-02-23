#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <ostream>

namespace cute {

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
    static Log& get();

    static std::ostream& debug(std::string component, std::string message = "");
    static std::ostream& info(std::string component, std::string message = "");
    static std::ostream& warn(std::string component, std::string message = "");
    static std::ostream& err(std::string component, std::string message = "");

public:
    ~Log();

    std::ostream& log(Level level, std::string component, std::string message = "");

private:
    Log();
};

} // namespace

#endif