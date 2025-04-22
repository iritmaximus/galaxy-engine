#include <iostream>

#define BX_CONFIG_DEBUG 1
#include "bx/bx.h"
#include "bgfx/bgfx.h"
#include "bgfx/platform.h"

#include "GLFW/glfw3.h"

#define GLFW_EXPOSE_NATIVE_X11
#include "GLFW/glfw3native.h"

const int W_WIDTH = 800;
const int W_HEIGHT = 600;


static void glfw_errorCallback(int error, const char *description)
{
    fprintf(stderr, "GLFW error, %d: %s\n", error, description);
}


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main (int argc, char* args[]) 
{
    std::cout << "Starting the engine..." << std::endl;
    glfwSetErrorCallback(glfw_errorCallback);

    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow* window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Galaxy-engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Call bgfx::renderFrame before bgfx::init to signal to bgfx not to create a render thread.
	// Most graphics APIs must be used on the same thread that created the window.
    bgfx::renderFrame();


    bgfx::PlatformData pd;
    pd.ndt = glfwGetX11Display();
    pd.nwh = (void *)(uintptr_t) glfwGetX11Window(window);

    bgfx::Init init;
    init.type = bgfx::RendererType::Count;
    init.resolution.width = W_WIDTH;
    init.resolution.height = W_HEIGHT;
    init.resolution.reset = BGFX_RESET_VSYNC;
    init.platformData = pd;

    if (bgfx::init(init) != true)
    {
        std::cout << "Failed to initialize bgfx" << std::endl;
        glfwTerminate();
        return -1;
    }

    bgfx::setDebug(BGFX_DEBUG_TEXT);
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, W_WIDTH, W_HEIGHT);

    std::cout << "Initialization done." << std::endl;

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        bgfx::touch(0);
        bgfx::frame();
        glfwPollEvents();    
    }


    bgfx::shutdown();
    glfwTerminate();
    return 0;
}

