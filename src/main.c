/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
  if (!glfwInit()) {
    // LOG
    fprintf(stderr, "failed to init glfw\n");
    return 1;
  }

  // Request OpenGL 3.2 core profile
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create window
  GLFWwindow* window = glfwCreateWindow(1024, 576, "cozmo", NULL, NULL);

  if (!window) {
    // LOG
    fprintf(stderr, "failed to create window\n");
    return 1;
  }

  // Make OpenGL current
  glfwMakeContextCurrent(window);

  if (!gladLoadGL()) {
    // LOG
    fprintf(stderr, "failed to make gl current\n");
    return 1;
  }

  // Window loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
  }

  // Clean up GLFW
  glfwTerminate();
}
