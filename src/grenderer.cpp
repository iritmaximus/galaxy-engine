#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_X11
#include "GLFW/glfw3native.h"

#include "env-vars.h"
#include "grenderer.h"
#include "logger.h"

GRenderer::GRenderer(GWindow *w, Logger *l) : window(w), logger(l) {
}

GRenderer::~GRenderer() {
  LOG_DEBUG("Shutting down renderer...");
}

void GRenderer::init() {
  LOG_DEBUG("Initializing the GRenderer...");
}

void GRenderer::update() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glfwSwapBuffers(this->window->getWindow());
}
