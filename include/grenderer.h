#pragma once

#include "gconfig.h"
#include "gmenu.h"
#include "gshader.h"
#include "gwindow.h"
#include "logger.h"

class GRenderer {
public:
  GRenderer(GWindow *w, Logger *l, GConfig *c);
  ~GRenderer();
  void init();
  void update();

  void init_imgui();
  void update_imgui();

private:
  Logger *logger;
  GConfig *config;
  GWindow *window;
  GShader *shader;
  GMenu *menu;

  unsigned int VAO;
  unsigned int VBO;
};
