#include <iostream>
#include <stdexcept>
#include <hello_triangle.h>

#ifdef WIN32
#include "SDL.h"
#endif


int main(int argc, char **argv) {
  HelloTriangleApplication app;

  try {
      app.init();
      app.mainLoop ();
      app.cleanup ();
    } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}