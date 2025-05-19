#pragma once

#include <iostream>
#include <string>

// TODO add log levels => for ex. display only info and errors
#define LOG_INFO(x) this->logger->info(x);
#define LOG_DEBUG(x) this->logger->debug(x);
#define LOG_ERROR(x) this->logger->error(x);
#define LOG_WARN(x) this->logger->warn(x);

class Logger {
public:
  Logger();
  Logger(std::ostream *l);
  Logger(const Logger &old_logger);
  void info(const std::string msg);
  void debug(const std::string msg);
  void error(const std::string msg);
  void warn(const std::string msg);

private:
  std::ostream *outputDest;
};
