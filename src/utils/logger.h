#ifndef LIBGPHOTO_CPP_UTILS_LOGGER_H
#define LIBGPHOTO_CPP_UTILS_LOGGER_H
/*
 * libgphoto++ - modern c++ wrapper library for gphoto2
 * Copyright (C) 2016 Marco Gulino <marco AT gulinux.net>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "dptr.h"
#include <memory>
#include <list>
#include <string>
#include <sstream>
#include <functional>
#include <chrono>



namespace GPhotoCPP {
class Logger {
public:
  typedef std::shared_ptr<Logger> ptr;
  enum Level {TRACE = 0, DEBUG = 10, INFO = 20, WARNING = 30, ERROR = 40};
  typedef std::function<void(const std::string &message, Level level)> Printer;
  Logger(const Printer &printer);
  ~Logger();
  friend class Out;
  class Out;  
  std::shared_ptr<Out> out(Level level);
private:
  DPTR
};
}

GPhotoCPP::Logger::Out& operator<<(GPhotoCPP::Logger::Out& out, const std::string& s);

namespace GPhotoCPP {
  class Logger::Out {
  public:
    typedef std::shared_ptr<Out> ptr;
    ~Out();
    friend Out &::operator<<(Out &out, const std::string &t);
    friend class Logger;
  private:
    Out(Logger &logger, Level level);
    DPTR
  };
};

#include <iostream>
template<typename T> GPhotoCPP::Logger::Out::ptr operator<<(const GPhotoCPP::Logger::Out::ptr &p, const T &t) {
  *p << t;
  return p;
}
template<typename T> GPhotoCPP::Logger::Out& operator<<(GPhotoCPP::Logger::Out& out, const T& t)
{
  std::stringstream s;
  s << t;
  return out << s.str();
}

inline std::ostream &operator<<(std::ostream &o, const std::chrono::time_point<std::chrono::system_clock> &t) {
  std::time_t tt = std::chrono::system_clock::to_time_t(t);
  return o << std::ctime(&tt);
}

#define lLog(level, logger) if(logger) logger->out(GPhotoCPP::Logger::level)
#define lTrace(logger) lLog(TRACE, logger)
#define lDebug(logger) lLog(DEBUG, logger)
#define lInfo(logger) lLog(INFO, logger)
#define lWarning(logger) lLog(WARNING, logger)
#define lError(logger) lLog(ERROR, logger)
#endif // LIBGPHOTO_CPP_UTILS_LOGGER_H
