#pragma once

#include "GLFW/glfw3.h"

#include "logger.h"

class GWindow {
public:
  GWindow(int w, int h, Logger *l) : width(w), height(h), logger(l) {};
  ~GWindow();
  void init();
  void processInput();

  GLFWwindow *getWindow() { return window; };
  int getWidth() const { return width; }
  int getHeight() const { return height; }

private:
  int width;
  int height;
  Logger *logger;
  GLFWwindow *window;
};
