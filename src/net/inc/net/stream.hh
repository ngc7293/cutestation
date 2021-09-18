#ifndef STREAM_HH_
#define STREAM_HH_

#include <iostream>
#include <sstream>

namespace net {

/** net::closeable
 * An iostream than can be close()'d
 */
class closeable : public std::iostream {
public:
    closeable(std::streambuf* s) : std::iostream(s) { }
    virtual void close() {}
};

/** net::stringstream
 * A stringstream, but with an empty close() method.
 * 
 * @note I know this is probably considered unclean or bad practice on account
 * of creating diamond inheritance. And it is not fully functionnal: you cannot
 * call operator<< directly on this class, you have to downcast it before.
 * 
 * But this allows me to simplify the threading in io::Client by closing the
 * stream and thus cancelling the blocking read() WITHOUT having to complexify
 * the test functions; test_client makes extensive use of this class.
 */
class stringstream : public closeable {
public:
    stringstream() : closeable(new std::stringbuf()) { }
    virtual ~stringstream() { delete rdbuf(); }

    std::string str() const { return static_cast<std::stringbuf *>(rdbuf())->str(); }
};

}

#endif