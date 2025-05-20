#include "glad/glad.h"

#include "gconfig.h"
#include "logger.h"

GConfig::GConfig(Logger *l)
    : logger(l), render_wireframe(0), show_menus(1), show_demo_menu(0) {}
GConfig::~GConfig() {};

void GConfig::update_render_wireframe() {
  // Test variable to enable wireframe rendering
  if (this->render_wireframe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
