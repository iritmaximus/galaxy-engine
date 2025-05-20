#pragma once

#include "logger.h"

class GConfig {
public:
  GConfig(Logger *l);
  ~GConfig();

  void update_render_wireframe();

  bool render_wireframe;
  bool show_demo_menu;
  bool show_menus;

private:
  Logger *logger;
};
