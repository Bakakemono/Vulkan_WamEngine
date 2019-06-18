#ifndef PIPELINE_H
#define PIPELINE_H

#include <vulkan/vulkan.h>

class PipelineManager
{
public:
	VkPipeline skyBoxPipeline;
	VkPipeline modelPipeline;
};

#endif
