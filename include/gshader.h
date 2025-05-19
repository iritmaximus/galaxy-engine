#pragma once

#include "logger.h"

class GShader {
public:
  GShader(Logger *l) : logger(l) {};
  ~GShader() {};
  void init();

private:
  Logger *logger;
};
