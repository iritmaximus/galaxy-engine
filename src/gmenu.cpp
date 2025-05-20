#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

#include "gmenu.h"

void GMenu::init() {
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(
      this->window->getWindow(),
      true); // Second param install_callback=true will install GLFW callbacks
             // and chain to existing ones.
  ImGui_ImplOpenGL3_Init();
}

void GMenu::default_menu() {
  ImGui::Begin("Default menu");
  ImGui::Text("Inside this menu you can edit the config variables");

  ImGui::Checkbox("Render only wireframes", &this->config->render_wireframe);
  ImGui::Checkbox("Show demo menu", &this->config->show_demo_menu);
  ImGui::Checkbox("Show menus in general", &this->config->show_menus);

  ImGui::End();
}

void GMenu::update() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  if (this->config->show_demo_menu)
    ImGui::ShowDemoWindow(); // Show demo window! :)

  if (this->config->show_menus)
    this->default_menu();

  this->config->update_render_wireframe();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
