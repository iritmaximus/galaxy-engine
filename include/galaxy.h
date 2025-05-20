#pragma once

#include "gconfig.h"
#include "grenderer.h"
#include "gwindow.h"
#include "logger.h"

class Galaxy {
public:
  Galaxy();
  ~Galaxy();
  Galaxy(GWindow *w, GRenderer *r, Logger *l, GConfig *c)
      : window(w), renderer(r), logger(l), config(c) {};
  void init();
  void run();

private:
  Logger *logger;
  GWindow *window;
  GRenderer *renderer;
  GConfig *config;
};

static void glfw_errorCallback(int error, const char *description);
