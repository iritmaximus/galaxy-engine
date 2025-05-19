#pragma once

#include <vector>

#include "gwindow.h"
#include "logger.h"
#include "vertex.h"

class GRenderer {
public:
  GRenderer(GWindow *w, Logger *l);
  ~GRenderer();
  void init();
  void update();

private:
  Logger *logger;
  GWindow *window;

  bgfx::ShaderHandle vsh;
  bgfx::ShaderHandle fsh;
  bgfx::ProgramHandle program;

  bgfx::VertexBufferHandle vbh;
  bgfx::IndexBufferHandle ibh;
  std::vector<PosColVertex> *vertexes;
  std::vector<int> *tri_list;

  bgfx::VertexLayout layout;

  void bgfx_init();
  void shader_init();
  bgfx::ShaderHandle load_shader(const char *name);
};
