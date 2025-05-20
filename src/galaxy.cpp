#include "logger.h"
#include "galaxy.h"
#include "gconfig.h"

const int W_WIDTH = 800;
const int W_HEIGHT = 600;

Galaxy::Galaxy() {
  Logger *logger = new Logger(&std::cout);
  this->logger = logger;
  LOG_INFO("Starting the engine...");

  GConfig *config = new GConfig(logger);
  GWindow *window = new GWindow(W_WIDTH, W_HEIGHT, logger);
  GRenderer *renderer = new GRenderer(window, logger, config);

  this->window = window;
  this->renderer = renderer;

  LOG_DEBUG("Done creating new things.");
}

Galaxy::~Galaxy() {
  LOG_INFO("Shutting down the engine...");

  delete this->renderer;
  delete this->window;
  delete this->config;
  delete this->logger;
}

void Galaxy::init() {
  LOG_DEBUG("Initializing the engine...");
  this->window->init();
  this->renderer->init();
}

void Galaxy::run() {
  LOG_DEBUG("Running the main loop...");

  unsigned int counter = 0;
  while (!glfwWindowShouldClose(this->window->getWindow())) {
    this->window->processInput();
    this->renderer->update();

    glfwPollEvents();
    counter++;
  }
}
