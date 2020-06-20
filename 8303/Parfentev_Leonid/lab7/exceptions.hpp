#ifndef _H_EXCEPTIONS_HPP
#define _H_EXCEPTIONS_HPP

#include <string>
#include <sstream>
#include <stdexcept>


class NoSavegameFile: public std::exception {
    std::string _fn;

    mutable std::string _msg {""};

public:
    NoSavegameFile(const std::string &fn)
        :_fn{fn} {}

    virtual const char *
    what() const noexcept override
    {
        if (!_msg.length()) {
            std::ostringstream oss {};
            oss << "Can't open savegame file: " << _fn;
            _msg = oss.str();
        }
        return _msg.c_str();
    }
};

class InvalidSaveFileContents: public std::exception {
    using pos_t = std::istream::pos_type;

    std::string _fn;
    pos_t _pos;

    mutable std::string _msg {""};

public:
    InvalidSaveFileContents(const std::string &fn, pos_t pos)
        :_fn{fn}, _pos{pos} {}

    virtual const char *
    what() const noexcept override
    {
        if (!_msg.length()) {
            std::ostringstream oss {};
            oss << "Error while reading savegame file " << _fn;
            if (_pos >= 0) {
                oss << " around position " << _pos;
            }
            _msg = oss.str();
        }
        return _msg.c_str();
    }
};

#endif
