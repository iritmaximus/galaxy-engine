#pragma once

#include "gconfig.h"
#include "gwindow.h"
#include "logger.h"

class GMenu {
public:
  GMenu(Logger *l, GWindow *w, GConfig *c) : logger(l), window(w), config(c) {};
  ~GMenu() {};

  void init();
  void update();
  void default_menu();

private:
  Logger *logger;
  GWindow *window;
  GConfig *config;
};
