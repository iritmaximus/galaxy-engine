#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "gwindow.h"

// TODO change this to utilize Logger
static void glfw_errorCallback(int error, const char *description) {
  fprintf(stderr, "GLFW error, %d: %s\n", error, description);
}

void GWindow::init() {
  LOG_DEBUG("Initializing the GWindow...");

  glfwSetErrorCallback(glfw_errorCallback);

  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
  if (!glfwInit()) {
    LOG_ERROR("Failed to initialize GLFW."); // TODO move to caller
    throw std::runtime_error("Failed to initialize GLFW.");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->window =
      glfwCreateWindow(this->width, this->height, "Galaxy-engine", NULL, NULL);

  if (this->window == NULL) {
    LOG_ERROR("Failed to create GLFW window."); // TODO move to caller
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window.");
  }

  glfwMakeContextCurrent(this->window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    LOG_ERROR("Failed to initialize GLAD");
    throw std::runtime_error("Failed to initialize GLAD");
  }
}

GWindow::~GWindow() {
  LOG_DEBUG("Shutting down glfw window...");
  glfwTerminate();
}

void GWindow::processInput() {
  if (glfwGetKey(this->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(this->getWindow(), true);
}
