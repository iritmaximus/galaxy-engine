#pragma once

#include "gwindow.h"
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
};
