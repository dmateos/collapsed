#include "main.h"
#include "sprite.h"
#include "gl_program.h"
#include "gl_window.h"
#include "camera.h"
#include "util.h"

using namespace collapsed;

struct game_state {
  std::vector<Sprite*> sprites;
  Camera camera;
  Sprite *avatar;
} gs;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  float step = 2.0f;
  switch(key) {
    case GLFW_KEY_W:
      gs.avatar->offset_position(0.0, +step);
      break;
    case GLFW_KEY_S:
      gs.avatar->offset_position(0.0, -step);
      break;
    case GLFW_KEY_A:
      gs.avatar->offset_position(-step, 0.0);
      break;
    case GLFW_KEY_D:
      gs.avatar->offset_position(+step, 0.0);
      break;
    case GLFW_KEY_O:
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
      break;
  }
}

static void handle_mouse(GLFWwindow *window) {
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  gs.camera.offset_position(glm::vec2(x, -y));
  glfwSetCursorPos(window, 0.0f, 0.0f);
}

int main(int argc, char **argv) {
  collapsed::GLWindow window(XRES, YRES); 
  glfwMakeContextCurrent(window.get_window());
  glfwSetKeyCallback(window.get_window(), key_callback);
  glfwSetInputMode(window.get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPos(window.get_window(), XRES/2, YRES/2);

  GLProgram program("shaders/vshader.gsl", "shaders/fshader.gsl");

  Texture texture("assets/platformer.png");
  SpriteAsset sprite_asset_grass(&program, &texture, 7, 7);
  SpriteAsset sprite_asset_avatar(&program, &texture, 1, 3);

  for(float x = -100.0; x < 500.0; x += 10.0) {
    for(float y = -100.0; y < 500.0; y += 10.0) {
      Sprite *s;
      s = new Sprite(&sprite_asset_grass);
      s->offset_position(x, y);
      gs.sprites.push_back(s);
    }
  }

  gs.avatar = new Sprite(&sprite_asset_avatar);
  gs.sprites.push_back(gs.avatar);

  while(!glfwWindowShouldClose(window.get_window())) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(std::vector<Sprite*>::iterator it = gs.sprites.begin(); it != gs.sprites.end(); it++) {
      Sprite *sprite = *it;

//      if( sprite->get_position().x / XRES >= gs.camera.get_position().x / XRES &&
  //        sprite->get_position().y / YRES >= gs.camera.get_position().y / YRES) {

        sprite->m_asset->m_program->use();
        sprite->m_asset->m_program->set_uniform("transform", glm::translate(glm::mat4(), glm::vec3(sprite->get_position(), 1.0)));
        sprite->m_asset->m_program->set_uniform("camera", gs.camera.matrix());
        glBindVertexArray(sprite->m_asset->m_vao);
        sprite->m_asset->m_texture->bind_texture();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //  }
    }

    handle_mouse(window.get_window());
    window.update_fps_counter();
    glfwSwapBuffers(window.get_window());
    glfwPollEvents();
  }
  return 0;
}
