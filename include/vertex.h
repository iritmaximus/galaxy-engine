#pragma once

#include <cstdint>

class PosColVertex {
public:
  PosColVertex(float x, float y, float z, uint32_t abgr)
      : x(x), y(y), z(z), abgr(abgr) {
    this->init();
  };
  ~PosColVertex() {};
  void init();

private:
  float x;
  float y;
  float z;

  uint32_t abgr;
};
