#pragma once

#include "gwindow.h"
#include "gshader.h"
#include "logger.h"

class GRenderer {
public:
  GRenderer(GWindow *w, Logger *l);
  ~GRenderer();
  void init();
  void update();

private:
  Logger *logger;
  GWindow *window;
  GShader *shader;

  unsigned int VAO;
  unsigned int VBO;
};
