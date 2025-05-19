#include "glad/glad.h"

#include "env-vars.h"
#include "grenderer.h"
#include "gshader.h"
#include "logger.h"

float vertices[] = {
    -0.5f, -0.5f, 0.0f, // left
    0.5f,  -0.5f, 0.0f, // right
    0.0f,  0.5f,  0.0f  // top
};

unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

GRenderer::GRenderer(GWindow *w, Logger *l) : window(w), logger(l), VAO(0), VBO(0) {
  this->shader = new GShader(l);
}

GRenderer::~GRenderer() {
  LOG_DEBUG("Shutting down renderer...");
  delete this->shader;
}

void GRenderer::init() {
  LOG_DEBUG("Initializing the GRenderer...");
  this->shader->init();

  // Create Vertex attribute object and vertex buffer objects
  glGenVertexArrays(1, &this->VAO);
  glGenBuffers(1, &this->VBO);

  // Bind both of them
  glBindVertexArray(this->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

  // Send data to VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Describe data send to VBO
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void GRenderer::update() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(this->shader->getProgram());
  glBindVertexArray(this->VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glfwSwapBuffers(this->window->getWindow());
}
