#include <iostream>
#include <string>

#include "logger.h"

#define TERMINAL_COLOR_PRE(col) "\033[" #col "m"
#define TERMINAL_COLOR_END "\033[0m"

Logger::Logger() : outputDest(&std::cout) {}
Logger::Logger(std::ostream *oDest) : outputDest(oDest) {}
Logger::Logger(const Logger &old_logger) {
  this->outputDest = old_logger.outputDest;
}

void Logger::info(const std::string msg) {
  *(this->outputDest) << TERMINAL_COLOR_PRE(36) << "[INFO]\t"
                      << TERMINAL_COLOR_END << msg << std::endl;
}

void Logger::debug(const std::string msg) {
  *(this->outputDest) << TERMINAL_COLOR_PRE(35) << "[DEBUG]\t"
                      << TERMINAL_COLOR_END << msg << std::endl;
}

void Logger::error(const std::string msg) {
  *(this->outputDest) << TERMINAL_COLOR_PRE(31) << "[ERROR]\t"
                      << TERMINAL_COLOR_END << msg << std::endl;
}

void Logger::warn(const std::string msg) {
  *(this->outputDest) << TERMINAL_COLOR_PRE(33) << "[WARN]\t"
                      << TERMINAL_COLOR_END << msg << std::endl;
}
