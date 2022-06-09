#ifdef RL_VULKAN

#ifdef RL_SDL
#include <SDL_vulkan.h>
#endif

#include <vulkan/vulkan.h>

typedef struct
{
	VkInstance instance;
	VkSurfaceKHR surface;
	VkPhysicalDevice gpu;
	VkDevice device;
	VkQueue queue;
	VkCommandPool cmd_pool;
} vk_info_t;
#endif
