#include "main.h"
#include "sprite.h"
#include "gl_program.h"
#include "camera.h"

using namespace collapsed; 

struct game_state {
  std::vector<Sprite*> sprites;
};

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

static void handle_mouse(GLFWwindow *window) {

}

int main(int argc, char **argv) {
  GLFWwindow *window;

  if(!glfwInit()) {
    std::cout << "could not init glfw3" << std::endl;
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  if(!(window = glfwCreateWindow(XRES, YRES, "", NULL, NULL))) {
    std::cout << "could not make glfw window" << std::endl;
    return 1;
  }

  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glewExperimental = GL_TRUE;
  glewInit();

  GLProgram program("shaders/vshader.gsl", "shaders/fshader.gsl");
  Camera camera;

  Texture texture("assets/circle.png");
  SpriteAsset sprite_asset(&program, &texture);
  Sprite sprite(&sprite_asset);

  while(!glfwWindowShouldClose(window)) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sprite.m_asset->m_program->use();
    sprite.m_asset->m_program->set_uniform("camera", camera.matrix());

    glBindVertexArray(sprite.m_asset->m_vao);
    sprite.m_asset->m_texture->bind_texture();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  return 0;
}
