#include <iostream>
#include <stdexcept>
#include <WamEngine.h>



#ifdef WIN32
#include "SDL.h"
#endif


int main(int argc, char **argv) {
  WamEngine app;

  try {
	  app.run();
    } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}