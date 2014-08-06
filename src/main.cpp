#include "main.h"
#include "sprite.h"
#include "gl_program.h"
#include "camera.h"
#include "util.h"

using namespace collapsed; 

struct game_state {
  std::vector<Sprite*> sprites;
  Camera camera;
  Sprite *avatar;
} gs;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  switch(key) {
    case GLFW_KEY_W:
      gs.avatar->offset_position(0.0, +10.0);
      break;
    case GLFW_KEY_S:
      gs.avatar->offset_position(0.0, -10.0);
      break;
    case GLFW_KEY_A:
      gs.avatar->offset_position(-10.0, 0.0);
      break;
    case GLFW_KEY_D:
      gs.avatar->offset_position(+10.0, 0.0);
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
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPos(window, XRES/2, YRES/2);
  glewExperimental = GL_TRUE;
  glewInit();

  GLProgram program("shaders/vshader.gsl", "shaders/fshader.gsl");

  Texture texture("assets/rpg.png");
  SpriteAsset sprite_asset_grass(&program, &texture, 0, 0);
  SpriteAsset sprite_asset_tree(&program, &texture, 0, 1);
  SpriteAsset sprite_asset_avatar(&program, &texture, 1, 3);
  
  for(float x = -100.0; x < 500.0; x += 10.0) {
    for(float y = -100.0; y < 500.0; y += 10.0) {
      int n = rand() % 10;
      Sprite *s;
      if(n < 8) {
        s = new Sprite(&sprite_asset_grass); 
      }
      else { 
        s = new Sprite(&sprite_asset_tree);
      }

      s->offset_position(x, y);
      gs.sprites.push_back(s);
    }
  }

  gs.avatar = new Sprite(&sprite_asset_avatar);
  gs.sprites.push_back(gs.avatar);

  while(!glfwWindowShouldClose(window)) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(std::vector<Sprite*>::iterator it = gs.sprites.begin(); it != gs.sprites.end(); it++) {
      Sprite *sprite = *it;

      if(sprite->get_position().x > gs.camera.get_position().x && sprite->get_position().y > gs.camera.get_position().y) {
        sprite->m_asset->m_program->use();
        sprite->m_asset->m_program->set_uniform("transform", glm::translate(glm::mat4(), glm::vec3(sprite->get_position(), 1.0)));
        sprite->m_asset->m_program->set_uniform("camera", gs.camera.matrix());
        glBindVertexArray(sprite->m_asset->m_vao);
        sprite->m_asset->m_texture->bind_texture();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      }
    }

    handle_mouse(window);
    update_fps_counter(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  return 0;
}
