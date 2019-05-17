#ifndef MODEL_H
#define MODEL_H

#include <assimp/cimport.h>        // Plain-C interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/postprocess.h>    // Post processing flags

class model
{
public:
	bool ImportModel(const char* path);

private:

};

#endif
