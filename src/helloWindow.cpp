#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main(){

  // Instantiate GLFW window
  // -----------------------
  glfwInit();

  // Tell GLFW that openGL 3.3 is the version we want to use
  // If a user does not have version 3.3, GLFW will fail to run
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Tell GLFW we want to use core profile
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

  // Create a window object
  // -----------------------------------
  GLFWwindow *window = glfwCreateWindow(800, 600, "hello window", NULL, NULL);
  if (window == NULL){
    std::cout << "Failed to create a GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  // Make the context of our window the main context on the current thread
  glfwMakeContextCurrent(window);

  // Add a resize callback to the window so if a user resizes the window,
  // the viewport is adjusted properly
  // Whenever the window changes in size, GLFW calls this function and fills in
  // the proper arguments for us to process
  // Tell GLFW we want to call this function on every window resize
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  // We can add other callbacks anytime after we've created the window
  // and before the game loop is initiated

  // GLAD: load all OpenGL function
  // Question: why does this have to come after the two above commands?
  //           It gives a symbol error if placed on the top of the main function
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // Tell OpenGL the size of the rendering window so it knows how we want to
  // display the data and coordinates wrt the window
//  glViewport(0, 0, 800, 600);
  // glViewport converts the 2D coordinate in [-1,1] to the specified range of
  // the screen's range. eg: (-0.5,0.5) is mapped to (200,450) in screen coordinates



  // Call the render loop which keeps on running until we tell GLFW to stop
  // --------------------------------------
  while (!glfwWindowShouldClose(window)){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // state-setting function
    glClear(GL_COLOR_BUFFER_BIT); // state-using function
    // Check for specific key presses and react accordingly every frame
    processInput(window);
    // Do other renderings here...


    // Check if any events are triggered (eg. keyboard input, mouse movement),
    // updates the window state and calls callback functions
    glfwPollEvents();
    // Swap the color buffer (a larger buffer that contains color values for
    // each pixel in GLFW's window) that has been used to draw in this iteration
    // and show it as output to the screen
    glfwSwapBuffers(window);


  }

  // Clean and delete all resources that were allocated and exit the application
  glfwTerminate();
  return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
    glfwSetWindowShouldClose(window, true);
  }
}