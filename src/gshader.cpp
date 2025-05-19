#include "glad/glad.h"

#include "env-vars.h"
#include "gshader.h"
#include "logger.h"

void GShader::init() {
  LOG_DEBUG("Initializing the GShader...");
  this->vertex_init();
  this->fragment_init();

  unsigned int program = glCreateProgram();

  glAttachShader(program, this->vertex_shader);
  glAttachShader(program, this->fragment_shader);
  glLinkProgram(program);

  // Check for errors
  int success;
  char info_log[512];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, info_log);

    LOG_ERROR("Failed to link the shaders");
    LOG_ERROR(info_log);

    glDeleteShader(this->vertex_shader);
    glDeleteShader(this->fragment_shader);
    throw std::runtime_error("Failed to link the shaders");
  }

  // Not needed after binding
  glDeleteShader(this->vertex_shader);
  glDeleteShader(this->fragment_shader);

  this->program = program;
  glUseProgram(this->program);

  // Test variable to enable wireframe rendering
  if (WIREFRAME_RENDERING) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
};

GShader::~GShader() {
  glDeleteShader(this->vertex_shader);
  glDeleteShader(this->fragment_shader);
}

void GShader::vertex_init() {
  const char *vertex_shader_source =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\n\0";

  // Create empty vertex shader
  unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);

  // Add source and compile the vertex shader created above
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);

  // Check for errors
  int success;
  char info_log[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);

    LOG_ERROR("Creating the shader failed: ");
    LOG_ERROR(info_log);

    throw std::runtime_error("Creating the shader failed");
  }

  // Success
  this->vertex_shader = vertex_shader;
}

void GShader::fragment_init() {
  const char *fragment_shader_source =
      "#version 330 core\n"
      "out vec4 FragColor;\n"

      "void main()\n"
      "{\n"
      "  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
      "}\0";

  // Create empty fragment shader
  unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

  // Add source to the shader and compile it
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);

  // Check for errors
  int success;
  char info_log[512];
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
    LOG_ERROR("Creating the shader failed:");
    LOG_ERROR(info_log);
    throw std::runtime_error("Creating the shader failed");
  }

  // Success
  this->fragment_shader = fragment_shader;
}
