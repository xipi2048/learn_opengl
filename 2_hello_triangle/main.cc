#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

bool init();
void close();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

GLFWwindow* window;

int main()
{

}