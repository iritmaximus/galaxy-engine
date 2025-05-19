#include "bgfx/bgfx.h"

#include "vertex.h"

void PosColVertex::init() {
  this->layout.begin()
      .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
      .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
      .end();
}
