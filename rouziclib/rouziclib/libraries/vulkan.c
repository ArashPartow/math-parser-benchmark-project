#ifdef RL_VULKAN

const char *get_vk_error_string(cl_int err)
{
	switch (err)
	{
		case 0:			return "VK_SUCCESS";
		case 1:			return "VK_NOT_READY";
		case 2:			return "VK_TIMEOUT";
		case 3:			return "VK_EVENT_SET";
		case 4:			return "VK_EVENT_RESET";
		case 5:			return "VK_INCOMPLETE";
		case -1:		return "VK_ERROR_OUT_OF_HOST_MEMORY";
		case -2:		return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
		case -3:		return "VK_ERROR_INITIALIZATION_FAILED";
		case -4:		return "VK_ERROR_DEVICE_LOST";
		case -5:		return "VK_ERROR_MEMORY_MAP_FAILED";
		case -6:		return "VK_ERROR_LAYER_NOT_PRESENT";
		case -7:		return "VK_ERROR_EXTENSION_NOT_PRESENT";
		case -8:		return "VK_ERROR_FEATURE_NOT_PRESENT";
		case -9:		return "VK_ERROR_INCOMPATIBLE_DRIVER";
		case -10:		return "VK_ERROR_TOO_MANY_OBJECTS";
		case -11:		return "VK_ERROR_FORMAT_NOT_SUPPORTED";
		case -12:		return "VK_ERROR_FRAGMENTED_POOL";
		case -1000069000:	return "VK_ERROR_OUT_OF_POOL_MEMORY";
		case -1000072003:	return "VK_ERROR_INVALID_EXTERNAL_HANDLE";
		case -1000000000:	return "VK_ERROR_SURFACE_LOST_KHR";
		case -1000000001:	return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
		case 1000001003:	return "VK_SUBOPTIMAL_KHR";
		case -1000001004:	return "VK_ERROR_OUT_OF_DATE_KHR";
		case -1000003001:	return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
		case -1000011001:	return "VK_ERROR_VALIDATION_FAILED_EXT";
		case -1000012000:	return "VK_ERROR_INVALID_SHADER_NV";
		case -1000158000:	return "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
		case -1000161000:	return "VK_ERROR_FRAGMENTATION_EXT";
		case -1000174001:	return "VK_ERROR_NOT_PERMITTED_EXT";
		case -1000244000:	return "VK_ERROR_INVALID_DEVICE_ADDRESS_EXT";
		case -1000255000:	return "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";

		default: return "Unknown Vulkan error";
	}
}

int vk_create_instance()
{
	int i, ext_count, add_ext_count, layer_count;
	VkResult ret;
	char **ext, *add_ext[] = { "" }, *layers[] = { "VK_LAYER_KHRONOS_validation", "VK_LAYER_LUNARG_standard_validation" };

	// Count the extensions
	if (SDL_Vulkan_GetInstanceExtensions(fb.window, &ext_count, NULL) == 0)		// get the extension count
	{
		fprintf_rl(stderr, "Couldn't get extension count in vk_create_instance(): %s\n", SDL_GetError());
		return -1;
	}

	add_ext_count = 0;//sizeof(add_ext)/sizeof(char *);

	// Get the extensions
	ext = calloc(ext_count+add_ext_count, sizeof(char *));

	if (SDL_Vulkan_GetInstanceExtensions(fb.window, &ext_count, ext) == 0)		// get the extensions
	{
		fprintf_rl(stderr, "Couldn't get the extensions in vk_create_instance(): %s\n", SDL_GetError());
		return -1;
	}

	// Put the additional extensions at the end of the full extension list
	for (i=0; i < add_ext_count; i++)
		ext[i+ext_count] = add_ext[i];

	// Application info
	const VkApplicationInfo appInfo = { .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO, .apiVersion = VK_API_VERSION_1_1 };

	// Create the instance
	VkInstanceCreateInfo create_info = { .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, .enabledLayerCount = sizeof(layers)/sizeof(char *), .ppEnabledLayerNames = layers, .enabledExtensionCount = ext_count+add_ext_count, .ppEnabledExtensionNames = ext, .pApplicationInfo = &appInfo };

	ret = vkCreateInstance(&create_info, NULL, &fb.vk.instance);
	VK_ERR_RET("vkCreateInstance (in vk_create_instance)", ret);

	free(ext);

	return ret;
}

int vk_pick_physical_device()
{
	VkResult ret;
	uint32_t dev_count;

	// Count devices
	ret = vkEnumeratePhysicalDevices(fb.vk.instance, &dev_count, NULL);
	VK_ERR_RET("vkEnumeratePhysicalDevices #1 (in vk_pick_physical_device)", ret);

	if (dev_count > 0)
	{
		VkPhysicalDevice *dev = calloc(dev_count, sizeof(VkPhysicalDevice));
		ret = vkEnumeratePhysicalDevices(fb.vk.instance, &dev_count, dev);
		VK_ERR_RET("vkEnumeratePhysicalDevices #2 (in vk_pick_physical_device)", ret);

		fb.vk.gpu = dev[0];		// pick the first one
		free(dev);
	}

	return ret;
}

int vk_init_queue()
{
	VkResult ret;
	int i, queue_fam_index = 0;
	uint32_t fam_count = 0, extension_count = 0;

	// Pick the queue family index
	vkGetPhysicalDeviceQueueFamilyProperties(fb.vk.gpu, &fam_count, NULL);

	if (fam_count > 0)
	{
		VkQueueFamilyProperties *fam_prop = calloc(fam_count, sizeof(VkQueueFamilyProperties));
		vkGetPhysicalDeviceQueueFamilyProperties(fb.vk.gpu, &fam_count, fam_prop);

		for (i=0; i < fam_count; i++)
			if (fam_prop[i].queueFlags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT))	// pick the queue family with the needed features
			{
				queue_fam_index = i;
				break;
			}

		free(fam_prop);
	}

	// Create device
	const char *ext[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	const VkDeviceQueueCreateInfo queueInfo = { .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, .queueFamilyIndex = queue_fam_index, .queueCount = 1, .pQueuePriorities = (const float[]) {1.f} };
	VkDeviceCreateInfo deviceInfo = { .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, .queueCreateInfoCount = 1, .pQueueCreateInfos = &queueInfo, .enabledExtensionCount = sizeof(ext)/sizeof(char *), .ppEnabledExtensionNames = ext };

	ret = vkCreateDevice(fb.vk.gpu, &deviceInfo, NULL, &fb.vk.device);
	VK_ERR_RET("vkCreateDevice (in vk_init_queue)", ret);

	// Get queue
	vkGetDeviceQueue(fb.vk.device, queue_fam_index, 0, &fb.vk.queue);

	// Create command pool
	const VkCommandPoolCreateInfo cmd_pool_info = { .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO, .queueFamilyIndex = queue_fam_index, .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT };

	ret = vkCreateCommandPool(fb.vk.device, &cmd_pool_info, NULL, &fb.vk.cmd_pool);
	VK_ERR_RET("vkCreateCommandPool (in vk_init_queue)", ret);
}

int vk_init()
{
	vk_create_instance();
	vk_pick_physical_device();
	vk_init_queue();
}

#endif
