#include <iostream>
#include <stdexcept>
#include <hello_myTriangle.h>



#ifdef WIN32
#include "SDL.h"
#endif


int main(int argc, char **argv) {
  GreatView app;

  try {
	  app.run();
    } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}