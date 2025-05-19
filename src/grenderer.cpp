#define BX_CONFIG_DEBUG 0
#include "bgfx/bgfx.h"
#include "bgfx/platform.h"
#include "bx/math.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstring>

#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_X11
#include "GLFW/glfw3native.h"

#include "env-vars.h"
#include "grenderer.h"
#include "logger.h"

static PosColVertex st_vertexes[] =
{
    {-1.0f,  1.0f,  1.0f, 0xff000000 },
    { 1.0f,  1.0f,  1.0f, 0xff0000ff },
    {-1.0f, -1.0f,  1.0f, 0xff00ff00 },
    { 1.0f, -1.0f,  1.0f, 0xff00ffff },
    {-1.0f,  1.0f, -1.0f, 0xffff0000 },
    { 1.0f,  1.0f, -1.0f, 0xffff00ff },
    {-1.0f, -1.0f, -1.0f, 0xffffff00 },
    { 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t st_tri_list[] =
{
    0, 1, 2,
    1, 3, 2,
    4, 6, 5,
    5, 6, 7,
    0, 2, 4,
    4, 2, 6,
    1, 5, 3,
    5, 7, 3,
    0, 4, 1,
    4, 5, 1,
    2, 3, 6,
    6, 3, 7,
};


GRenderer::GRenderer(GWindow *w, Logger *l) : window(w), logger(l) {
  // TODO this is obviously static data
  static std::vector<PosColVertex> vertexes = {{0.5f, 0.5f, 0.0f, 0xff0000ff},
                                               {0.5f, -0.5f, 0.0f, 0xff0000ff},
                                               {-0.5f, -0.5f, 0.0f, 0xff00ff00},
                                               {-0.5f, 0.5f, 0.0f, 0xff00ff00}};
  static std::vector<int> tri_list = {0, 1, 3, 1, 2, 3};

  this->vertexes = &vertexes;
  this->tri_list = &tri_list;
}

GRenderer::~GRenderer() {
  LOG_DEBUG("Shutting down renderer...");
  bgfx::shutdown();
}

void GRenderer::init() {
  LOG_DEBUG("Initializing the GRenderer...");
  this->bgfx_init();
  this->shader_init();
}

void GRenderer::bgfx_init() {
  // Call bgfx::renderFrame before bgfx::init to signal to bgfx not to create a
  // render thread. Most graphics APIs must be used on the same thread that
  // created the window.
  bgfx::renderFrame();

  bgfx::PlatformData pd;
  pd.ndt = glfwGetX11Display();
  pd.nwh = (void *)(uintptr_t)glfwGetX11Window(this->window->getWindow());

  bgfx::Init init;
  init.type = bgfx::RendererType::Count;
  init.resolution.width = this->window->getWidth();
  init.resolution.height = this->window->getHeight();
  init.resolution.reset = BGFX_RESET_VSYNC;
  init.platformData = pd;

  if (bgfx::init(init) != true) {
    LOG_ERROR("Failed to initialize bgfx.");
    glfwTerminate();
    throw std::runtime_error("Failed to initialize bgfx.");
  }

  /* 
  bgfx::setDebug(BGFX_DEBUG_TEXT);
  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f,
                     0);
  bgfx::setViewRect(0, 0, 0, this->window->getWidth(),
                    this->window->getHeight());

  bgfx::touch(0);
  */

  // Todo move this to some fancy class
  static bgfx::VertexLayout layout;
  this->layout = layout;

  this->layout.begin()
      .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
      .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
      .end();
}

void GRenderer::shader_init() {
  LOG_DEBUG("Loading shaders...");

  LOG_DEBUG("Galaxy shader bin: " GALAXY_SHADER_BIN_DIR);

  const char *path_v = GALAXY_SHADER_BIN_DIR "/glsl/v_simple.sc.bin";
  const char *path_f = GALAXY_SHADER_BIN_DIR "/glsl/f_simple.sc.bin";

  this->vsh = this->load_shader(path_v);
  this->fsh = this->load_shader(path_f);

  this->vbh = bgfx::createVertexBuffer(
      // bgfx::makeRef(this->vertexes, sizeof(*this->vertexes)), this->layout);
      bgfx::makeRef(&st_vertexes, sizeof(st_vertexes)), this->layout);

  this->ibh = bgfx::createIndexBuffer(
      // bgfx::makeRef(this->tri_list, sizeof(*this->tri_list)));
      bgfx::makeRef(&st_tri_list, sizeof(st_tri_list)));

  this->program = bgfx::createProgram(this->vsh, this->fsh, true);

  // Reset window
  bgfx::reset(this->window->getWidth(), this->window->getHeight(), BGFX_RESET_VSYNC);

  // Enable debug text.
  bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

  // Set view rectangle for 0th view
  bgfx::setViewRect(0, 0, 0, uint16_t(this->window->getWidth()), uint16_t(this->window->getHeight()));

  // Clear the view rect
  bgfx::setViewClear(0,
                     BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
                     0x443355FF, 1.0f, 0);
}

bgfx::ShaderHandle GRenderer::load_shader(const char *name) {
  char *data = new char[4098];
  std::ifstream file;
  size_t file_size;

  file.open(name);
  if (file.is_open()) {
    // Get file size
    file.seekg(0, std::ios::end);
    file_size = file.tellg();

    file.seekg(0, std::ios::beg);
    file.read(data, file_size);

    file.close();
  } else {
    delete[] data;
    throw std::runtime_error(std::string("Failed to open shader file: ") +
                             std::string(name));
  }

  // create bgfx::Memory object and create shader from it
  const bgfx::Memory *mem = bgfx::copy(data, file_size + 1);
  mem->data[mem->size - 1] = '\0';
  bgfx::ShaderHandle handle = bgfx::createShader(mem);
  bgfx::setName(handle, name);

  delete[] data;
  return handle;
}

void GRenderer::update() {
  LOG_DEBUG("Starting rendening update loop...");

  const bx::Vec3 at = {0.0f, 0.0f, 0.0f};
  const bx::Vec3 eye = {0.0f, 0.0f, 10.0f};

  // Set view and projection matrix for view 0.
  float view[16];
  bx::mtxLookAt(view, eye, at);

  float proj[16];
  bx::mtxProj(proj, 60.0f,
              float(this->window->getWidth()) /
                  float(this->window->getHeight()),
              0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

  bgfx::setViewTransform(0, view, proj);

  // Set view 0 default viewport.
  bgfx::setViewRect(0, 0, 0, this->window->getWidth(),
                    this->window->getHeight());

  bgfx::touch(0);

  float mtx[16];
  bx::mtxRotateY(mtx, 0.0f);

  // position x,y,z
  mtx[12] = 0.0f;
  mtx[13] = 0.0f;
  mtx[14] = 0.0f;

  // Set model matrix for rendering.
  bgfx::setTransform(mtx);

  // Set vertex and index buffer.
  bgfx::setVertexBuffer(0, this->vbh);
  bgfx::setIndexBuffer(this->ibh);

  // Set render states.
  bgfx::setState(BGFX_STATE_DEFAULT);

  // Submit primitive for rendering to view 0.
  bgfx::submit(0, this->program);

  LOG_DEBUG("Rendering...");
  bgfx::frame();
}
