#pragma once
#include "bgfx/bgfx.h"

#include "logger.h"

class GShader {
public:
  GShader(Logger *l) : logger(l) {};
  ~GShader() {};
  void init();

  bgfx::ShaderHandle loadShader(const char *name);

private:
  Logger *logger;
};
