#include <model.h>

bool model::ImportModel(const char* path)
{
	// Import the model with example of post Processing
	const aiScene* scene = aiImportFile(
		path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
	);

	if(!scene)
	{
		throw std::runtime_error(aiGetErrorString());
		return false;
	}
	return false;

}
