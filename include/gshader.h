#pragma once

#include "logger.h"

class GShader {
public:
  GShader(Logger *l) : logger(l), vertex_shader(0), fragment_shader(0) {};
  ~GShader();

  void init();
  void vertex_init();
  void fragment_init();

  unsigned int getProgram() { return this->program; }

private:
  Logger *logger;
  unsigned int vertex_shader;
  unsigned int fragment_shader;
  unsigned int program;
};
