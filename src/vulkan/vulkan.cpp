#include "xgk-renderers/src/vulkan/vulkan.h"

// using namespace XGK::VULKAN::WRAPPERS;



// #include <iostream>
// using std::cout;
// using std::endl;



// #define VK_NO_PROTOTYPES
// #include "vulkan/vulkan.h"



#if defined(__linux__)
	#define SHARED_LIBRARY_MODULE_TYPE void*
	// #define SHARED_LIBRARY_MODULE_INIT_VALUE nullptr
	// #define SHARED_LIBRARY_LOAD dlopen("libvulkan.so.1", RTLD_LAZY)
	// #define SHARED_LIBRARY_LOAD_FUNCTION dlsym
	// #define SHARED_LIBRARY_FREE dlclose
#elif defined(_WIN64)
	#define SHARED_LIBRARY_MODULE_TYPE HMODULE
	// #define SHARED_LIBRARY_MODULE_INIT_VALUE 0
	// #define SHARED_LIBRARY_LOAD LoadLibrary("vulkan-1.dll")
	// #define SHARED_LIBRARY_LOAD_FUNCTION GetProcAddress
	// #define SHARED_LIBRARY_FREE FreeLibrary
#endif



// vulkan api function declarations
#define DECL_PROC(name) PFN_##name name {}

DECL_PROC(vkGetInstanceProcAddr);

DECL_PROC(vkCreateInstance);
DECL_PROC(vkEnumerateInstanceLayerProperties);
DECL_PROC(vkEnumerateInstanceExtensionProperties);

DECL_PROC(vkDestroyInstance);

DECL_PROC(vkEnumeratePhysicalDevices);
DECL_PROC(vkEnumerateDeviceExtensionProperties);
DECL_PROC(vkGetPhysicalDeviceProperties);
DECL_PROC(vkGetPhysicalDeviceFeatures);
DECL_PROC(vkGetPhysicalDeviceQueueFamilyProperties);
DECL_PROC(vkGetPhysicalDeviceMemoryProperties);
DECL_PROC(vkGetPhysicalDeviceFormatProperties);

DECL_PROC(vkGetDeviceProcAddr);
DECL_PROC(vkCreateDevice);

DECL_PROC(vkCreateDebugReportCallbackEXT);
DECL_PROC(vkDestroyDebugReportCallbackEXT);

#if defined(VK_USE_PLATFORM_XLIB_KHR)
	DECL_PROC(vkCreateXlibSurfaceKHR);
#elif defined(VK_USE_PLATFORM_WIN32_KHR)
	DECL_PROC(vkCreateWin32SurfaceKHR);
#endif

DECL_PROC(vkGetPhysicalDeviceSurfaceSupportKHR);
DECL_PROC(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
DECL_PROC(vkGetPhysicalDeviceSurfaceFormatsKHR);
DECL_PROC(vkGetPhysicalDeviceSurfacePresentModesKHR);
DECL_PROC(vkDestroySurfaceKHR);

DECL_PROC(vkDeviceWaitIdle);
DECL_PROC(vkDestroyDevice);

DECL_PROC(vkGetDeviceQueue);
DECL_PROC(vkQueueSubmit);
DECL_PROC(vkQueuePresentKHR);
DECL_PROC(vkQueueWaitIdle);

DECL_PROC(vkCreateSwapchainKHR);
DECL_PROC(vkGetSwapchainImagesKHR);
DECL_PROC(vkAcquireNextImageKHR);
DECL_PROC(vkDestroySwapchainKHR);

DECL_PROC(vkCreateImage);
DECL_PROC(vkDestroyImage);

DECL_PROC(vkCreateImageView);
DECL_PROC(vkDestroyImageView);

DECL_PROC(vkCreateSampler);
DECL_PROC(vkDestroySampler);

DECL_PROC(vkCreateRenderPass);
DECL_PROC(vkDestroyRenderPass);

DECL_PROC(vkCreateFramebuffer);
DECL_PROC(vkDestroyFramebuffer);

DECL_PROC(vkBeginCommandBuffer);
DECL_PROC(vkCmdPipelineBarrier);
DECL_PROC(vkCmdClearColorImage);
DECL_PROC(vkCmdBeginRenderPass);
DECL_PROC(vkCmdBindPipeline);
DECL_PROC(vkCmdBindVertexBuffers);
DECL_PROC(vkCmdBindIndexBuffer);
DECL_PROC(vkCmdBindDescriptorSets);
DECL_PROC(vkCmdDraw);
DECL_PROC(vkCmdEndRenderPass);
DECL_PROC(vkCmdSetViewport);
DECL_PROC(vkCmdPushConstants);
DECL_PROC(vkCmdSetScissor);
DECL_PROC(vkCmdDrawIndexed);
DECL_PROC(vkCmdCopyBufferToImage);
DECL_PROC(vkEndCommandBuffer);
DECL_PROC(vkResetCommandBuffer);

DECL_PROC(vkCreateCommandPool);
DECL_PROC(vkResetCommandPool);
DECL_PROC(vkAllocateCommandBuffers);
DECL_PROC(vkFreeCommandBuffers);
DECL_PROC(vkDestroyCommandPool);

DECL_PROC(vkCreateSemaphore);
DECL_PROC(vkDestroySemaphore);

DECL_PROC(vkCreateFence);
DECL_PROC(vkWaitForFences);
DECL_PROC(vkResetFences);
DECL_PROC(vkDestroyFence);

DECL_PROC(vkCreateShaderModule);
DECL_PROC(vkDestroyShaderModule);

DECL_PROC(vkCreatePipelineLayout);
DECL_PROC(vkDestroyPipelineLayout);

DECL_PROC(vkCreateGraphicsPipelines);
DECL_PROC(vkDestroyPipeline);

DECL_PROC(vkCreateBuffer);
DECL_PROC(vkGetBufferMemoryRequirements);
DECL_PROC(vkGetImageMemoryRequirements);
DECL_PROC(vkDestroyBuffer);

DECL_PROC(vkAllocateMemory);
DECL_PROC(vkBindBufferMemory);
DECL_PROC(vkMapMemory);
DECL_PROC(vkFlushMappedMemoryRanges);
DECL_PROC(vkUnmapMemory);
DECL_PROC(vkFreeMemory);
DECL_PROC(vkBindImageMemory);

DECL_PROC(vkCreateDescriptorPool);
DECL_PROC(vkDestroyDescriptorPool);

DECL_PROC(vkCreateDescriptorSetLayout);
DECL_PROC(vkUpdateDescriptorSets);
DECL_PROC(vkAllocateDescriptorSets);
DECL_PROC(vkDestroyDescriptorSetLayout);

#undef DECL_PROC



namespace XGK::VULKAN::WRAPPERS
{
	// // SHARED_LIBRARY_MODULE_TYPE shared_library_module_handle { SHARED_LIBRARY_MODULE_INIT_VALUE };
	SHARED_LIBRARY_MODULE_TYPE shared_library_module_handle {};
	// // SHARED_LIBRARY_MODULE_TYPE shared_library_module_handle = SHARED_LIBRARY_MODULE_INIT_VALUE;



	// void loadGlobalFunctions (void)
	// {
	// 	vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr) SHARED_LIBRARY_LOAD_FUNCTION(shared_library_module_handle, "vkGetInstanceProcAddr");

	// 	#define GET_PROC_ADDR(name) name = (PFN_##name) vkGetInstanceProcAddr(nullptr, #name)

	// 	GET_PROC_ADDR(vkCreateInstance);
	// 	GET_PROC_ADDR(vkEnumerateInstanceLayerProperties);
	// 	GET_PROC_ADDR(vkEnumerateInstanceExtensionProperties);

	// 	#undef GET_PROC_ADDR
	// }

	// void loadSharedLibrary (void)
	// {
	// 	// if (shared_library_module_handle) {

	// 	//   // cout << "LIB " << shared_library_module_handle << endl;

	// 	//   // SHARED_LIBRARY_FREE(shared_library_module_handle);

	// 	//   cout << "DLCLOSE " << SHARED_LIBRARY_FREE(shared_library_module_handle) << endl;

	// 	//   // shared_library_module_handle = SHARED_LIBRARY_MODULE_INIT_VALUE;
	// 	// }

	// 	shared_library_module_handle = SHARED_LIBRARY_LOAD;

	// 	// cout << "LIB " << shared_library_module_handle << endl;
	// }

	// void freeSharedLibrary (void)
	// {
	// 	// SHARED_LIBRARY_FREE(shared_library_module_handle);

	// 	// cout << "DLCLOSE " << SHARED_LIBRARY_FREE(shared_library_module_handle) << endl;

	// 	shared_library_module_handle = SHARED_LIBRARY_MODULE_INIT_VALUE;
	// }

	// void loadInstanceFunctions (VkInstance instance)
	// {
	// 	#define GET_PROC_ADDR(name) name = (PFN_##name) vkGetInstanceProcAddr(instance, #name)

	// 	GET_PROC_ADDR(vkDestroyInstance);

	// 	GET_PROC_ADDR(vkEnumeratePhysicalDevices);
	// 	GET_PROC_ADDR(vkGetPhysicalDeviceProperties);
	// 	GET_PROC_ADDR(vkGetPhysicalDeviceFeatures);
	// 	GET_PROC_ADDR(vkGetPhysicalDeviceQueueFamilyProperties);
	// 	GET_PROC_ADDR(vkGetPhysicalDeviceMemoryProperties);
	// 	GET_PROC_ADDR(vkGetPhysicalDeviceFormatProperties);

	// 	GET_PROC_ADDR(vkGetDeviceProcAddr);
	// 	GET_PROC_ADDR(vkCreateDevice);

	// 	GET_PROC_ADDR(vkCreateDebugReportCallbackEXT);
	// 	GET_PROC_ADDR(vkDestroyDebugReportCallbackEXT);

	// 	#if defined(__linux__)
	// 		GET_PROC_ADDR(vkCreateXlibSurfaceKHR);
	// 	#elif defined(_WIN64)
	// 		GET_PROC_ADDR(vkCreateWin32SurfaceKHR);
	// 	#endif

	// 	GET_PROC_ADDR(vkGetPhysicalDeviceSurfaceSupportKHR);
	// 	GET_PROC_ADDR(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
	// 	GET_PROC_ADDR(vkGetPhysicalDeviceSurfaceFormatsKHR);
	// 	GET_PROC_ADDR(vkGetPhysicalDeviceSurfacePresentModesKHR);
	// 	GET_PROC_ADDR(vkDestroySurfaceKHR);

	// 	#undef GET_PROC_ADDR
	// }

	// void loadDeviceFunctions (VkDevice device)
	// {
	// 	#define GET_PROC_ADDR(name) name = (PFN_##name) vkGetDeviceProcAddr(device, #name)

	// 	GET_PROC_ADDR(vkDeviceWaitIdle);
	// 	GET_PROC_ADDR(vkDestroyDevice);

	// 	GET_PROC_ADDR(vkGetDeviceQueue);
	// 	GET_PROC_ADDR(vkQueueSubmit);
	// 	GET_PROC_ADDR(vkQueuePresentKHR);
	// 	GET_PROC_ADDR(vkQueueWaitIdle);

	// 	GET_PROC_ADDR(vkCreateSwapchainKHR);
	// 	GET_PROC_ADDR(vkGetSwapchainImagesKHR);
	// 	GET_PROC_ADDR(vkAcquireNextImageKHR);
	// 	GET_PROC_ADDR(vkDestroySwapchainKHR);

	// 	GET_PROC_ADDR(vkCreateImage);
	// 	GET_PROC_ADDR(vkDestroyImage);

	// 	GET_PROC_ADDR(vkCreateImageView);
	// 	GET_PROC_ADDR(vkDestroyImageView);

	// 	GET_PROC_ADDR(vkCreateSampler);
	// 	GET_PROC_ADDR(vkDestroySampler);

	// 	GET_PROC_ADDR(vkCreateRenderPass);
	// 	GET_PROC_ADDR(vkDestroyRenderPass);

	// 	GET_PROC_ADDR(vkCreateFramebuffer);
	// 	GET_PROC_ADDR(vkDestroyFramebuffer);

	// 	GET_PROC_ADDR(vkBeginCommandBuffer);
	// 	GET_PROC_ADDR(vkCmdPipelineBarrier);
	// 	GET_PROC_ADDR(vkCmdClearColorImage);
	// 	GET_PROC_ADDR(vkCmdBeginRenderPass);
	// 	GET_PROC_ADDR(vkCmdBindPipeline);
	// 	GET_PROC_ADDR(vkCmdBindVertexBuffers);
	// 	GET_PROC_ADDR(vkCmdBindIndexBuffer);
	// 	GET_PROC_ADDR(vkCmdBindDescriptorSets);
	// 	GET_PROC_ADDR(vkCmdDraw);
	// 	GET_PROC_ADDR(vkCmdEndRenderPass);
	// 	GET_PROC_ADDR(vkCmdSetViewport);
	// 	GET_PROC_ADDR(vkCmdPushConstants);
	// 	GET_PROC_ADDR(vkCmdSetScissor);
	// 	GET_PROC_ADDR(vkCmdDrawIndexed);
	// 	GET_PROC_ADDR(vkCmdCopyBufferToImage);
	// 	GET_PROC_ADDR(vkEndCommandBuffer);
	// 	GET_PROC_ADDR(vkResetCommandBuffer);

	// 	GET_PROC_ADDR(vkCreateCommandPool);
	// 	GET_PROC_ADDR(vkResetCommandPool);
	// 	GET_PROC_ADDR(vkAllocateCommandBuffers);
	// 	GET_PROC_ADDR(vkFreeCommandBuffers);
	// 	GET_PROC_ADDR(vkDestroyCommandPool);

	// 	GET_PROC_ADDR(vkCreateSemaphore);
	// 	GET_PROC_ADDR(vkDestroySemaphore);

	// 	GET_PROC_ADDR(vkCreateFence);
	// 	GET_PROC_ADDR(vkWaitForFences);
	// 	GET_PROC_ADDR(vkResetFences);
	// 	GET_PROC_ADDR(vkDestroyFence);

	// 	GET_PROC_ADDR(vkCreateShaderModule);
	// 	GET_PROC_ADDR(vkDestroyShaderModule);

	// 	GET_PROC_ADDR(vkCreatePipelineLayout);
	// 	GET_PROC_ADDR(vkDestroyPipelineLayout);

	// 	GET_PROC_ADDR(vkCreateGraphicsPipelines);
	// 	GET_PROC_ADDR(vkDestroyPipeline);

	// 	GET_PROC_ADDR(vkCreateBuffer);
	// 	GET_PROC_ADDR(vkGetBufferMemoryRequirements);
	// 	GET_PROC_ADDR(vkGetImageMemoryRequirements);
	// 	GET_PROC_ADDR(vkDestroyBuffer);

	// 	GET_PROC_ADDR(vkAllocateMemory);
	// 	GET_PROC_ADDR(vkBindBufferMemory);
	// 	GET_PROC_ADDR(vkMapMemory);
	// 	GET_PROC_ADDR(vkFlushMappedMemoryRanges);
	// 	GET_PROC_ADDR(vkUnmapMemory);
	// 	GET_PROC_ADDR(vkFreeMemory);
	// 	GET_PROC_ADDR(vkBindImageMemory);

	// 	GET_PROC_ADDR(vkCreateDescriptorPool);
	// 	GET_PROC_ADDR(vkDestroyDescriptorPool);

	// 	GET_PROC_ADDR(vkCreateDescriptorSetLayout);
	// 	GET_PROC_ADDR(vkUpdateDescriptorSets);
	// 	GET_PROC_ADDR(vkAllocateDescriptorSets);
	// 	GET_PROC_ADDR(vkDestroyDescriptorSetLayout);

	// 	#undef GET_PROC_ADDR
	// }



	// VkApplicationInfo AppI
	// (
	// 	uint32_t    apiVersion         = VK_API_VERSION_1_2,
	// 	const char* pApplicationName   = nullptr,
	// 	uint32_t    applicationVersion = 0,
	// 	const char* pEngineName        = nullptr,
	// 	uint32_t    engineVersion      = 0,
	// 	const void* pNext              = nullptr
	// )
	// {
	// 	VkApplicationInfo info =
	// 	{
	// 		VK_STRUCTURE_TYPE_APPLICATION_INFO,
	// 		pNext,
	// 		pApplicationName,
	// 		applicationVersion,
	// 		pEngineName,
	// 		engineVersion,
	// 		apiVersion,
	// 	};

	// 	return info;
	// }



	#ifdef DEBUG
		#define DEBUG_REPORT_ARGS \
			\
			VkDebugReportFlagsEXT      flags,\
			VkDebugReportObjectTypeEXT objectType,\
			uint64_t                   object,\
			size_t                     location,\
			int32_t                    messageCode,\
			const char*                pLayerPrefix,\
			const char*                pMessage,\
			void*                      pUserData

		VkBool32 reportError(DEBUG_REPORT_ARGS)
		{
			printf("VALIDATION LAYER ERROR: %s\n", pMessage);

			return VK_FALSE;
		}

		VkBool32 reportInfo(DEBUG_REPORT_ARGS)
		{
			printf("VALIDATION LAYER INFORMATION: %s\n", pMessage);

			return VK_FALSE;
		}

		VkBool32 reportWarn(DEBUG_REPORT_ARGS)
		{
			printf("VALIDATION LAYER WARNING: %s\n", pMessage);

			return VK_FALSE;
		}

		VkBool32 reportPerf(DEBUG_REPORT_ARGS)
		{
			printf("VALIDATION LAYER PERFORMANCE WARNING: %s\n", pMessage);

			return VK_FALSE;
		}

		VkBool32 reportDebug(DEBUG_REPORT_ARGS)
		{
			printf("VALIDATION LAYER DEBUG: %s\n", pMessage);

			return VK_FALSE;
		}

		#undef DEBUG_REPORT_ARGS
	#endif



// 	struct Instance
// 	{
// 		VkInstance        handle                = VK_NULL_HANDLE;
// 		uint32_t          physical_device_count = 0;
// 		VkPhysicalDevice* physical_devices      = nullptr;

// 		std::vector<VkSurfaceKHR> surfaces;

// 		#ifdef DEBUG
// 			XGK_VULKAN_MACRO_DECLARE_DEBUG_REPORT_CALLBACKS
// 		#endif



// 			VkDebugReportCallbackEXT DebugReportCallbackEXT
// 			(
// 				PFN_vkDebugReportCallbackEXT pfnCallback = nullptr,
// 				VkDebugReportFlagsEXT        flags       = 0,
// 				void*                        pUserData   = nullptr,
// 				const void*                  pNext       = nullptr,
// 				const VkAllocationCallbacks* pAllocator  = nullptr
// 			)
// 			{
// 				VkDebugReportCallbackCreateInfoEXT info =
// 				{
// 					VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT,
// 					pNext,
// 					flags,
// 					pfnCallback,
// 					pUserData,
// 				};

// 				VkDebugReportCallbackEXT report_callback = VK_NULL_HANDLE;

// 				vkCreateDebugReportCallbackEXT(handle, &info, pAllocator, &report_callback);

// 				return report_callback;
// 			}

// 			void enumDevs (void)
// 			{
// 				vkEnumeratePhysicalDevices(handle, &physical_device_count, nullptr);

// 				physical_devices = new VkPhysicalDevice[physical_device_count];

// 				vkEnumeratePhysicalDevices(handle, &physical_device_count, physical_devices);
// 			}

// 			void create
// 			(
// 				const                        VkApplicationInfo* pApplicationInfo = nullptr,
// 				uint32_t                     enabledLayerCount                   = 0,
// 				const char* const*           ppEnabledLayerNames                 = nullptr,
// 				uint32_t                     enabledExtensionCount               = 0,
// 				const char* const*           ppEnabledExtensionNames             = nullptr,
// 				VkInstanceCreateFlags        flags                               = 0,
// 				const void*                  pNext                               = nullptr,
// 				const VkAllocationCallbacks* pAllocator                          = nullptr
// 			)
// 			{
// 				VkInstanceCreateInfo info =
// 				{
// 					VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
// 					pNext,
// 					flags,
// 					pApplicationInfo,
// 					enabledLayerCount,
// 					ppEnabledLayerNames,
// 					enabledExtensionCount,
// 					ppEnabledExtensionNames,
// 				};

// 				loadSharedLibrary();

// 				loadGlobalFunctions();

// 				vkCreateInstance(&info, pAllocator, &handle);

// 				loadInstanceFunctions(handle);

// 				#ifdef DEBUG
// 					XGK_VULKAN_MACRO_CREATE_DEBUG_REPORT_CALLBACKS(handle)
// 				#endif

// 				enumDevs();
// 			}

// 			VkSurfaceKHR SurfaceKHR
// 			(
// 				#if defined(__linux__)
// 					Display*                     dpy        = nullptr,
// 					Window                       window     = 0,
// 					VkXlibSurfaceCreateFlagsKHR  flags      = 0,
// 				#elif defined(_WIN64)
// 					HINSTANCE                    hinstance  = 0,
// 					HWND                         hwnd       = 0,
// 					VkWin32SurfaceCreateFlagsKHR flags      = 0,
// 				#endif

// 				const void*                    pNext      = nullptr,
// 				const VkAllocationCallbacks*   pAllocator = nullptr
// 			)
// 			{
// 				#if defined(__linux__)
// 					VkXlibSurfaceCreateInfoKHR info =
// 					{
// 						VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
// 						pNext,
// 						flags,
// 						dpy,
// 						window,
// 					};
// 				#elif defined(_WIN64)
// 					VkWin32SurfaceCreateInfoKHR info =
// 					{
// 						VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
// 						pNext,
// 						flags,
// 						hinstance,
// 						hwnd,
// 					};
// 				#endif

// 				VkSurfaceKHR surface = VK_NULL_HANDLE;

// 				#if defined(__linux__)
// 					vkCreateXlibSurfaceKHR(handle, &info, pAllocator, &surface);
// 				#elif defined(_WIN64)
// 					vkCreateWin32SurfaceKHR(handle, &info, pAllocator, &surface);
// 				#endif

// 				surfaces.push_back(surface);

// 				return surface;
// 			}

// 			void destroy (void)
// 			{
// 				delete[] physical_devices;

// 				for (uint64_t i = 0; i < surfaces.size(); ++i)
// 				{
// 					vkDestroySurfaceKHR(handle, surfaces[i], nullptr);
// 				}

// 				surfaces.resize(0);

// 				#ifdef DEBUG
// 					XGK_VULKAN_MACRO_DESTROY_DEBUG_REPORT_CALLBACKS(handle);
// 				#endif

// 				vkDestroyInstance(handle, nullptr);

// 				freeSharedLibrary();
// 			}
// 	};



// 	VkDeviceQueueCreateInfo DevQueueCI
// 	(
// 		uint32_t                 queueFamilyIndex = 0,
// 		uint32_t                 queueCount       = 0,
// 		const float*             pQueuePriorities = nullptr,
// 		VkDeviceQueueCreateFlags flags            = 0,
// 		const void*              pNext            = nullptr
// 	)
// 	{
// 		VkDeviceQueueCreateInfo info =
// 		{
// 			VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
// 			pNext,
// 			flags,
// 			queueFamilyIndex,
// 			queueCount,
// 			pQueuePriorities,
// 		};

// 		return info;
// 	}



// 	VkPipelineInputAssemblyStateCreateInfo PplInputAsm
// 	(
// 		VkPrimitiveTopology                     topology               = VK_PRIMITIVE_TOPOLOGY_POINT_LIST,
// 		VkBool32                                primitiveRestartEnable = VK_FALSE,
// 		VkPipelineInputAssemblyStateCreateFlags flags                  = 0,
// 		const void*                             pNext                  = nullptr
// 	)
// 	{
// 		VkPipelineInputAssemblyStateCreateInfo info =
// 		{
// 			VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
// 			pNext,
// 			flags,
// 			topology,
// 			primitiveRestartEnable,
// 		};

// 		return info;
// 	}



// 	VkPipelineTessellationStateCreateInfo PplTess
// 	(
// 		uint32_t                               patchControlPoints = 0,
// 		VkPipelineTessellationStateCreateFlags flags              = 0,
// 		const void*                            pNext              = nullptr
// 	)
// 	{
// 		VkPipelineTessellationStateCreateInfo info =
// 		{
// 			VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO,
// 			pNext,
// 			flags,
// 			patchControlPoints,
// 		};

// 		return info;
// 	}



// 	VkPipelineViewportStateCreateInfo PplView
// 	(
// 		uint32_t                           viewportCount = 0,
// 		const VkViewport*                  pViewports    = nullptr,
// 		uint32_t                           scissorCount  = 0,
// 		const VkRect2D*                    pScissors     = nullptr,
// 		VkPipelineViewportStateCreateFlags flags         = 0,
// 		const void*                        pNext         = nullptr
// 	)
// 	{
// 		VkPipelineViewportStateCreateInfo info =
// 		{
// 			VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
// 			pNext,
// 			flags,
// 			viewportCount,
// 			pViewports,
// 			scissorCount,
// 			pScissors,
// 		};

// 		return info;
// 	}



// 	VkPipelineMultisampleStateCreateInfo PplSample
// 	(
// 		VkSampleCountFlagBits                 rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT,
// 		VkBool32                              sampleShadingEnable   = VK_FALSE,
// 		float                                 minSampleShading      = 0.0f,
// 		const VkSampleMask*                   pSampleMask           = nullptr,
// 		VkBool32                              alphaToCoverageEnable = VK_FALSE,
// 		VkBool32                              alphaToOneEnable      = VK_FALSE,
// 		VkPipelineMultisampleStateCreateFlags flags                 = 0,
// 		const void*                           pNext                 = nullptr
// 	)
// 	{
// 		VkPipelineMultisampleStateCreateInfo info =
// 		{
// 			VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
// 			pNext,
// 			flags,
// 			rasterizationSamples,
// 			sampleShadingEnable,
// 			minSampleShading,
// 			pSampleMask,
// 			alphaToCoverageEnable,
// 			alphaToOneEnable,
// 		};

// 		return info;
// 	}



// 	VkPipelineRasterizationStateCreateInfo PplRast
// 	(
// 		VkBool32                                depthClampEnable        = VK_FALSE,
// 		VkBool32                                rasterizerDiscardEnable = VK_FALSE,
// 		VkPolygonMode                           polygonMode             = VK_POLYGON_MODE_FILL,
// 		VkCullModeFlags                         cullMode                = VK_CULL_MODE_NONE,
// 		VkFrontFace                             frontFace               = VK_FRONT_FACE_COUNTER_CLOCKWISE,
// 		VkBool32                                depthBiasEnable         = VK_FALSE,
// 		float                                   depthBiasConstantFactor = 0.0f,
// 		float                                   depthBiasClamp          = 0.0f,
// 		float                                   depthBiasSlopeFactor    = 0.0f,
// 		float                                   lineWidth               = 1.0f,
// 		VkPipelineRasterizationStateCreateFlags flags                   = 0,
// 		const void*                             pNext                   = nullptr
// 	)
// 	{
// 		VkPipelineRasterizationStateCreateInfo info =
// 		{
// 			VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
// 			pNext,
// 			flags,
// 			depthClampEnable,
// 			rasterizerDiscardEnable,
// 			polygonMode,
// 			cullMode,
// 			frontFace,
// 			depthBiasEnable,
// 			depthBiasConstantFactor,
// 			depthBiasClamp,
// 			depthBiasSlopeFactor,
// 			lineWidth,
// 		};

// 		return info;
// 	}



// 	VkPipelineDepthStencilStateCreateInfo PplDepthStenc
// 	(
// 		VkBool32                               depthTestEnable       = VK_FALSE,
// 		VkBool32                               depthWriteEnable      = VK_FALSE,
// 		VkCompareOp                            depthCompareOp        = VK_COMPARE_OP_NEVER,
// 		VkBool32                               depthBoundsTestEnable = VK_FALSE,
// 		VkBool32                               stencilTestEnable     = VK_FALSE,
// 		VkStencilOpState                       front                 = {},
// 		VkStencilOpState                       back                  = {},
// 		float                                  minDepthBounds        = 0.0f,
// 		float                                  maxDepthBounds        = 0.0f,
// 		VkPipelineDepthStencilStateCreateFlags flags                 = 0,
// 		const void*                            pNext                 = nullptr
// 	)
// 	{
// 		VkPipelineDepthStencilStateCreateInfo info =
// 		{
// 			VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
// 			pNext,
// 			flags,
// 			depthTestEnable,
// 			depthWriteEnable,
// 			depthCompareOp,
// 			depthBoundsTestEnable,
// 			stencilTestEnable,
// 			front,
// 			back,
// 			minDepthBounds,
// 			maxDepthBounds,
// 		};

// 		return info;
// 	}



// 	VkPipelineColorBlendStateCreateInfo PplBlend
// 	(
// 		VkBool32                                   logicOpEnable    = VK_FALSE,
// 		VkLogicOp                                  logicOp          = VK_LOGIC_OP_CLEAR,
// 		uint32_t                                   attachmentCount  = 0,
// 		const VkPipelineColorBlendAttachmentState* pAttachments     = nullptr,
// 		float                                      blendConstants_0 = 0.0f,
// 		float                                      blendConstants_1 = 0.0f,
// 		float                                      blendConstants_2 = 0.0f,
// 		float                                      blendConstants_3 = 0.0f,
// 		VkPipelineColorBlendStateCreateFlags       flags            = 0,
// 		const void*                                pNext            = nullptr
// 	)
// 	{
// 		VkPipelineColorBlendStateCreateInfo info =
// 		{
// 			VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
// 			pNext,
// 			flags,
// 			logicOpEnable,
// 			logicOp,
// 			attachmentCount,
// 			pAttachments,
// 			blendConstants_0,
// 			blendConstants_1,
// 			blendConstants_2,
// 			blendConstants_3,
// 		};

// 		return info;
// 	}



// 	VkPipelineDynamicStateCreateInfo PplDyn
// 	(
// 		uint32_t                          dynamicStateCount = 0,
// 		const VkDynamicState*             pDynamicStates    = nullptr,
// 		VkPipelineDynamicStateCreateFlags flags             = 0,
// 		const void*                       pNext             = nullptr
// 	)
// 	{
// 		VkPipelineDynamicStateCreateInfo info =
// 		{
// 			VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
// 			pNext,
// 			flags,
// 			dynamicStateCount,
// 			pDynamicStates,
// 		};

// 		return info;
// 	}



// 	VkPipelineShaderStageCreateInfo PplShader
// 	(
// 		VkShaderStageFlagBits            stage               = VK_SHADER_STAGE_VERTEX_BIT,
// 		VkShaderModule                   module              = VK_NULL_HANDLE,
// 		const char*                      pName               = "main",
// 		const VkSpecializationInfo*      pSpecializationInfo = nullptr,
// 		VkPipelineShaderStageCreateFlags flags               = 0,
// 		const void*                      pNext               = nullptr
// 	)
// 	{
// 		VkPipelineShaderStageCreateInfo info =
// 		{
// 			VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
// 			pNext,
// 			flags,
// 			stage,
// 			module,
// 			pName,
// 			pSpecializationInfo,
// 		};

// 		return info;
// 	}



// 	VkPipelineVertexInputStateCreateInfo PplVertex
// 	(
// 		uint32_t                                 vertexBindingDescriptionCount   = 0,
// 		const VkVertexInputBindingDescription*   pVertexBindingDescriptions      = nullptr,
// 		uint32_t                                 vertexAttributeDescriptionCount = 0,
// 		const VkVertexInputAttributeDescription* pVertexAttributeDescriptions    = nullptr,
// 		VkPipelineVertexInputStateCreateFlags    flags                           = 0,
// 		const void*                              pNext                           = nullptr
// 	)
// 	{
// 		VkPipelineVertexInputStateCreateInfo info =
// 		{
// 			VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
// 			pNext,
// 			flags,
// 			vertexBindingDescriptionCount,
// 			pVertexBindingDescriptions,
// 			vertexAttributeDescriptionCount,
// 			pVertexAttributeDescriptions,
// 		};

// 		return info;
// 	}



// 	VkWriteDescriptorSet WriteDescrSet
// 	(
// 		VkDescriptorSet               dstSet           = VK_NULL_HANDLE,
// 		uint32_t                      dstBinding       = 0,
// 		uint32_t                      dstArrayElement  = 0,
// 		uint32_t                      descriptorCount  = 0,
// 		VkDescriptorType              descriptorType   = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
// 		const VkDescriptorImageInfo*  pImageInfo       = nullptr,
// 		const VkDescriptorBufferInfo* pBufferInfo      = nullptr,
// 		const VkBufferView*           pTexelBufferView = nullptr,
// 		const void*                   pNext            = nullptr
// 	)
// 	{
// 		VkWriteDescriptorSet info =
// 		{
// 			VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
// 			pNext,
// 			dstSet,
// 			dstBinding,
// 			dstArrayElement,
// 			descriptorCount,
// 			descriptorType,
// 			pImageInfo,
// 			pBufferInfo,
// 			pTexelBufferView,
// 		};

// 		return info;
// 	}



// 	VkCommandBufferBeginInfo CmdBufferBeginI
// 	(
// 		const VkCommandBufferInheritanceInfo* pInheritanceInfo = nullptr,
// 		VkCommandBufferUsageFlags             flags            = 0,
// 		const void*                           pNext            = nullptr
// 	)
// 	{
// 		VkCommandBufferBeginInfo info =
// 		{
// 			VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
// 			pNext,
// 			flags,
// 			pInheritanceInfo,
// 		};

// 		return info;
// 	}



// 	VkRenderPassBeginInfo RenderPassBeginI
// 	(
// 		VkRenderPass        renderPass      = VK_NULL_HANDLE,
// 		VkFramebuffer       framebuffer     = VK_NULL_HANDLE,
// 		VkRect2D            renderArea      = {},
// 		uint32_t            clearValueCount = 0,
// 		const VkClearValue* pClearValues    = nullptr,
// 		const void*         pNext           = nullptr
// 	)
// 	{
// 		VkRenderPassBeginInfo info =
// 		{
// 			VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
// 			pNext,
// 			renderPass,
// 			framebuffer,
// 			renderArea,
// 			clearValueCount,
// 			pClearValues,
// 		};

// 		return info;
// 	}



// 	VkSubmitInfo SubmitI
// 	(
// 		uint32_t                    waitSemaphoreCount   = 0,
// 		const VkSemaphore*          pWaitSemaphores      = nullptr,
// 		const VkPipelineStageFlags* pWaitDstStageMask    = nullptr,
// 		uint32_t                    commandBufferCount   = 0,
// 		const VkCommandBuffer*      pCommandBuffers      = nullptr,
// 		uint32_t                    signalSemaphoreCount = 0,
// 		const VkSemaphore*          pSignalSemaphores    = nullptr,
// 		const void*                 pNext                = nullptr
// 	)
// 	{
// 		VkSubmitInfo info =
// 		{
// 			VK_STRUCTURE_TYPE_SUBMIT_INFO,
// 			pNext,
// 			waitSemaphoreCount,
// 			pWaitSemaphores,
// 			pWaitDstStageMask,
// 			commandBufferCount,
// 			pCommandBuffers,
// 			signalSemaphoreCount,
// 			pSignalSemaphores,
// 		};

// 		return info;
// 	}



// 	VkPresentInfoKHR PresentI
// 	(
// 		uint32_t              waitSemaphoreCount = 0,
// 		const VkSemaphore*    pWaitSemaphores    = nullptr,
// 		uint32_t              swapchainCount     = 0,
// 		const VkSwapchainKHR* pSwapchains        = nullptr,
// 		const uint32_t*       pImageIndices      = nullptr,
// 		VkResult*             pResults           = nullptr,
// 		const void*           pNext              = nullptr
// 	)
// 	{
// 		VkPresentInfoKHR info =
// 		{
// 			VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
// 			pNext,
// 			waitSemaphoreCount,
// 			pWaitSemaphores,
// 			swapchainCount,
// 			pSwapchains,
// 			pImageIndices,
// 			pResults,
// 		};

// 		return info;
// 	}



// 	struct Device
// 	{
// 		VkDevice                         handle                      = VK_NULL_HANDLE;
// 		uint32_t                         queue_family_prop_count     = 0;
// 		VkQueueFamilyProperties*         queue_family_props          = nullptr;
// 		uint32_t                         surface_format_count        = 0;
// 		VkSurfaceFormatKHR*              surface_formats             = nullptr;
// 		VkPhysicalDeviceMemoryProperties mem_props                   = {};
// 		VkSurfaceCapabilitiesKHR         surface_capabilities        = {};
// 		uint32_t                         graphics_queue_family_index = -1;
// 		uint64_t                         graphics_queue_count        = 0;
// 		uint32_t                         present_queue_family_index  = -1;
// 		uint64_t                         present_queue_count         = 0;

// 		std::vector<VkRenderPass> render_passes;
// 		std::vector<VkSwapchainKHR> swapchains;
// 		std::vector<VkImageView> image_views;
// 		std::vector<VkImage> images;
// 		std::vector<VkDeviceMemory> memories;
// 		std::vector<VkFramebuffer> framebuffers;
// 		std::vector<VkFence> fences;
// 		std::vector<VkSemaphore> semaphores;
// 		std::vector<VkBuffer> buffers;
// 		std::vector<VkDescriptorSetLayout> descr_set_layouts;
// 		std::vector<VkPipelineLayout> ppl_layouts;
// 		std::vector<VkDescriptorPool> descr_pools;
// 		std::vector<VkShaderModule> shader_modules;
// 		std::vector<VkPipeline> pipelines;
// 		std::vector<VkCommandPool> cmd_pools;



// 		void getProps (VkPhysicalDevice physical_device, VkSurfaceKHR surface)
// 		{
// 			vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_prop_count, nullptr);
// 			queue_family_props = new VkQueueFamilyProperties[queue_family_prop_count];
// 			vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_prop_count, queue_family_props);

// 			vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, surface, &surface_format_count, nullptr);
// 			surface_formats = new VkSurfaceFormatKHR[surface_format_count];
// 			vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, surface, &surface_format_count, surface_formats);

// 			vkGetPhysicalDeviceMemoryProperties(physical_device, &mem_props);

// 			// for (uint64_t i = 0; i < mem_props.memoryTypeCount; ++i) {

// 			//   VkMemoryType type = mem_props.memoryTypes[i];

// 			//   std::cout << "heap index: " << type.heapIndex << std::endl;

// 			//   if (type.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT || 0) {

// 			//     std::cout << "  device local" << std::endl;
// 			//   }

// 			//   if (type.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT || 0) {

// 			//     std::cout << "  host visible" << std::endl;
// 			//   }

// 			//   if (type.propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT || 0) {

// 			//     std::cout << "  host coherent" << std::endl;
// 			//   }

// 			//   if (type.propertyFlags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT || 0) {

// 			//     std::cout << "  host cached" << std::endl;
// 			//   }

// 			//   if ((type.propertyFlags & VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT || 0)) {

// 			//     std::cout << "  lazily allocated" << std::endl;
// 			//   }

// 			//   if (type.propertyFlags & VK_MEMORY_PROPERTY_PROTECTED_BIT || 0) {

// 			//     std::cout << "  protected" << std::endl;
// 			//   }

// 			//   if (type.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD || 0) {

// 			//     std::cout << "  device coherent AMD" << std::endl;
// 			//   }

// 			//   if (type.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD || 0) {

// 			//     std::cout << "  device uncached AMD" << std::endl;
// 			//   }

// 			//   std::cout << std::endl << std::endl;
// 			// }

// 			// std::cout << std::endl << std::endl;

// 			// for (uint64_t i = 0; i < mem_props.memoryHeapCount; ++i) {

// 			//   VkMemoryHeap heap = mem_props.memoryHeaps[i];

// 			//   std::cout << "heap size: " << heap.size << std::endl;

// 			//   if (heap.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT || 0) {

// 			//     std::cout << "  device local" << std::endl;
// 			//   }

// 			//   if (heap.flags & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT || 0) {

// 			//     std::cout << "  multi instance" << std::endl;
// 			//   }

// 			//   if (heap.flags & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT_KHR || 0) {

// 			//     std::cout << "  multi instance KHR" << std::endl;
// 			//   }

// 			//   std::cout << std::endl << std::endl;
// 			// }

// 			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device, surface, &surface_capabilities);

// 			// std::cout << surface_capabilities.minImageCount << std::endl;
// 			// std::cout << surface_capabilities.maxImageCount << std::endl;
// 			// std::cout << surface_capabilities.currentExtent.width << " " << surface_capabilities.currentExtent.height << std::endl;
// 			// std::cout << surface_capabilities.minImageExtent.width << " " << surface_capabilities.minImageExtent.height << std::endl;
// 			// std::cout << surface_capabilities.maxImageExtent.width << " " << surface_capabilities.maxImageExtent.height << std::endl;


// 			// std::cout << "queue family properties count: " << queue_family_prop_count << std::endl;
// 			// std::cout << std::endl << std::endl;

// 			for (uint64_t i = 0; i < queue_family_prop_count; ++i)
// 			{
// 				VkBool32 surface_support = VK_FALSE;

// 				vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, i, surface, &surface_support);

// 				if (queue_family_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT || 0)
// 				{
// 					graphics_queue_family_index = i;
// 					graphics_queue_count = queue_family_props[i].queueCount;
// 				}

// 				if (surface_support)
// 				{
// 					present_queue_family_index = i;
// 					present_queue_count = queue_family_props[i].queueCount;
// 				}

// 				// std::cout << "queue family index: " << i << std::endl;
// 				// std::cout << std::endl;
// 				// std::cout << "graphics: " << (queue_family_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT || 0) << std::endl;
// 				// std::cout << "compute: " << (queue_family_props[i].queueFlags & VK_QUEUE_COMPUTE_BIT || 0) << std::endl;
// 				// std::cout << "transfer: " << (queue_family_props[i].queueFlags & VK_QUEUE_TRANSFER_BIT || 0) << std::endl;
// 				// std::cout << "sparse binding: " << (queue_family_props[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT || 0) << std::endl;
// 				// std::cout << "protected: " << (queue_family_props[i].queueFlags & VK_QUEUE_PROTECTED_BIT || 0) << std::endl;
// 				// std::cout << "all: " << (queue_family_props[i].queueFlags & VK_QUEUE_FLAG_BITS_MAX_ENUM || 0) << std::endl;
// 				// std::cout << std::endl;
// 				// std::cout << "queue count: " << queue_family_props[i].queueCount << std::endl;
// 				// std::cout << "timestamp valid bits: " << queue_family_props[i].timestampValidBits << std::endl;
// 				// // std::cout << queue_family_props[i].minImageTransferGranularity << std::endl;
// 				// std::cout << "presentation support: " << surface_support << std::endl;
// 				// std::cout << std::endl << std::endl;
// 			}

// 			// throw "";
// 		}

// 		void create
// 		(
// 			VkPhysicalDevice                physical_device,
// 			uint32_t                        queueCreateInfoCount    = 0,
// 			const VkDeviceQueueCreateInfo*  pQueueCreateInfos       = nullptr,
// 			uint32_t                        enabledLayerCount       = 0,
// 			const char* const*              ppEnabledLayerNames     = nullptr,
// 			uint32_t                        enabledExtensionCount   = 0,
// 			const char* const*              ppEnabledExtensionNames = nullptr,
// 			const VkPhysicalDeviceFeatures* pEnabledFeatures        = nullptr,
// 			VkDeviceCreateFlags             flags                   = 0,
// 			const void*                     pNext                   = nullptr,
// 			const VkAllocationCallbacks*    pAllocator              = nullptr
// 		)
// 		{
// 			VkDeviceCreateInfo info =
// 			{
// 				VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
// 				pNext,
// 				flags,
// 				queueCreateInfoCount,
// 				pQueueCreateInfos,
// 				enabledLayerCount,
// 				ppEnabledLayerNames,
// 				enabledExtensionCount,
// 				ppEnabledExtensionNames,
// 				pEnabledFeatures,
// 			};

// 			vkCreateDevice(physical_device, &info, pAllocator, &handle);

// 			loadDeviceFunctions(handle);
// 		}

// 		VkQueue Queue (uint32_t queueFamilyIndex, uint32_t queueIndex)
// 		{
// 			VkQueue queue = VK_NULL_HANDLE;

// 			vkGetDeviceQueue(handle, queueFamilyIndex, queueIndex, &queue);

// 			return queue;
// 		}

// 		VkRenderPass RenderPass
// 		(
// 			uint32_t                       attachmentCount = 0,
// 			const VkAttachmentDescription* pAttachments    = nullptr,
// 			uint32_t                       subpassCount    = 0,
// 			const VkSubpassDescription*    pSubpasses      = nullptr,
// 			uint32_t                       dependencyCount = 0,
// 			const VkSubpassDependency*     pDependencies   = nullptr,
// 			VkRenderPassCreateFlags        flags           = 0,
// 			const void*                    pNext           = nullptr,
// 			const VkAllocationCallbacks*   pAllocator      = nullptr
// 		)
// 		{
// 			VkRenderPassCreateInfo info =
// 			{
// 				VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
// 				pNext,
// 				flags,
// 				attachmentCount,
// 				pAttachments,
// 				subpassCount,
// 				pSubpasses,
// 				dependencyCount,
// 				pDependencies,
// 			};

// 			VkRenderPass render_pass = VK_NULL_HANDLE;

// 			vkCreateRenderPass(handle, &info, pAllocator, &render_pass);

// 			render_passes.push_back(render_pass);

// 			return render_pass;
// 		}

// 		VkSwapchainKHR SwapchainKHR
// 		(
// 			VkSurfaceKHR                  surface               = VK_NULL_HANDLE,
// 			uint32_t                      minImageCount         = 0,
// 			VkFormat                      imageFormat           = VK_FORMAT_B8G8R8A8_UNORM,
// 			VkColorSpaceKHR               imageColorSpace       = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
// 			uint32_t                      imageExtent_width     = 0,
// 			uint32_t                      imageExtent_height    = 0,
// 			uint32_t                      imageArrayLayers      = 0,
// 			VkImageUsageFlags             imageUsage            = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
// 			VkSharingMode                 imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE,
// 			uint32_t                      queueFamilyIndexCount = 0,
// 			const uint32_t*               pQueueFamilyIndices   = nullptr,
// 			VkSurfaceTransformFlagBitsKHR preTransform          = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
// 			VkCompositeAlphaFlagBitsKHR   compositeAlpha        = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
// 			VkPresentModeKHR              presentMode           = VK_PRESENT_MODE_FIFO_KHR,
// 			VkBool32                      clipped               = VK_FALSE,
// 			VkSwapchainKHR                oldSwapchain          = VK_NULL_HANDLE,
// 			VkSwapchainCreateFlagsKHR     flags                 = 0,
// 			const void*                   pNext                 = nullptr,
// 			const VkAllocationCallbacks*  pAllocator            = nullptr
// 		)
// 		{
// 			VkSwapchainCreateInfoKHR info =
// 			{
// 				VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
// 				pNext,
// 				flags,
// 				surface,
// 				minImageCount,
// 				imageFormat,
// 				imageColorSpace,

// 				{
// 					imageExtent_width,
// 					imageExtent_height,
// 				},

// 				imageArrayLayers,
// 				imageUsage,
// 				imageSharingMode,
// 				queueFamilyIndexCount,
// 				pQueueFamilyIndices,
// 				preTransform,
// 				compositeAlpha,
// 				presentMode,
// 				clipped,
// 				oldSwapchain,
// 			};

// 			VkSwapchainKHR swapchain = VK_NULL_HANDLE;

// 			vkCreateSwapchainKHR(handle, &info, pAllocator, &swapchain);

// 			swapchains.push_back(swapchain);

// 			return swapchain;
// 		}

// 		std::vector<VkImage> getSwapchainImages (VkSwapchainKHR swapchain)
// 		{
// 			uint32_t count = 0;

// 			vkGetSwapchainImagesKHR(handle, swapchain, &count, nullptr);
// 			std::vector<VkImage> images(count);
// 			vkGetSwapchainImagesKHR(handle, swapchain, &count, images.data());

// 			return images;
// 		}

// 		VkImage Image
// 		(
// 			VkImageType                  imageType             = VK_IMAGE_TYPE_2D,
// 			VkFormat                     format                = VK_FORMAT_B8G8R8A8_UNORM,
// 			uint32_t                     extent_width          = 0,
// 			uint32_t                     extent_height         = 0,
// 			uint32_t                     extent_depth          = 0,
// 			uint32_t                     mipLevels             = 0,
// 			uint32_t                     arrayLayers           = 0,
// 			VkSampleCountFlagBits        samples               = VK_SAMPLE_COUNT_1_BIT,
// 			VkImageTiling                tiling                = VK_IMAGE_TILING_OPTIMAL,
// 			VkImageUsageFlags            usage                 = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
// 			VkSharingMode                sharingMode           = VK_SHARING_MODE_EXCLUSIVE,
// 			uint32_t                     queueFamilyIndexCount = 0,
// 			const uint32_t*              pQueueFamilyIndices   = nullptr,
// 			VkImageLayout                initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED,
// 			VkImageCreateFlags           flags                 = 0,
// 			const void*                  pNext                 = nullptr,
// 			const VkAllocationCallbacks* pAllocator            = nullptr
// 		)
// 		{
// 			VkImageCreateInfo info =
// 			{
// 				VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
// 				pNext,
// 				flags,
// 				imageType,
// 				format,

// 				{
// 					extent_width,
// 					extent_height,
// 					extent_depth,
// 				},

// 				mipLevels,
// 				arrayLayers,
// 				samples,
// 				tiling,
// 				usage,
// 				sharingMode,
// 				queueFamilyIndexCount,
// 				pQueueFamilyIndices,
// 				initialLayout,
// 			};

// 			VkImage image = VK_NULL_HANDLE;

// 			vkCreateImage(handle, &info, pAllocator, &image);

// 			images.push_back(image);

// 			return image;
// 		}

// 		VkImageView ImageView
// 		(
// 			VkImage                      image                           = VK_NULL_HANDLE,
// 			VkImageViewType              viewType                        = VK_IMAGE_VIEW_TYPE_2D,
// 			VkFormat                     format                          = VK_FORMAT_B8G8R8A8_UNORM,
// 			VkComponentSwizzle           compenents_r                    = VK_COMPONENT_SWIZZLE_IDENTITY,
// 			VkComponentSwizzle           compenents_g                    = VK_COMPONENT_SWIZZLE_IDENTITY,
// 			VkComponentSwizzle           compenents_b                    = VK_COMPONENT_SWIZZLE_IDENTITY,
// 			VkComponentSwizzle           compenents_a                    = VK_COMPONENT_SWIZZLE_IDENTITY,
// 			VkImageAspectFlags           subresourceRange_aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
// 			uint32_t                     subresourceRange_baseMipLevel   = 0,
// 			uint32_t                     subresourceRange_levelCount     = 0,
// 			uint32_t                     subresourceRange_baseArrayLayer = 0,
// 			uint32_t                     subresourceRange_layerCount     = 0,
// 			VkImageViewCreateFlags       flags                           = 0,
// 			const void*                  pNext                           = nullptr,
// 			const VkAllocationCallbacks* pAllocator                      = nullptr
// 		)
// 		{
// 			VkImageViewCreateInfo info =
// 			{
// 				VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
// 				pNext,
// 				flags,
// 				image,
// 				viewType,
// 				format,

// 				{
// 					compenents_r,
// 					compenents_g,
// 					compenents_b,
// 					compenents_a,
// 				},

// 				{
// 					subresourceRange_aspectMask,
// 					subresourceRange_baseMipLevel,
// 					subresourceRange_levelCount,
// 					subresourceRange_baseArrayLayer,
// 					subresourceRange_layerCount,
// 				}
// 			};

// 			VkImageView image_view = VK_NULL_HANDLE;

// 			vkCreateImageView(handle, &info, pAllocator, &image_view);

// 			image_views.push_back(image_view);

// 			return image_view;
// 		}

// 		VkMemoryRequirements MemReqs (VkImage image)
// 		{
// 			VkMemoryRequirements reqs;

// 			vkGetImageMemoryRequirements(handle, image, &reqs);

// 			return reqs;
// 		}

// 		VkMemoryRequirements MemReqs (VkBuffer buffer)
// 		{
// 			VkMemoryRequirements reqs;

// 			vkGetBufferMemoryRequirements(handle, buffer, &reqs);

// 			return reqs;
// 		}

// 		uint32_t getMemTypeIndex (VkMemoryRequirements* mem_reqs, VkMemoryPropertyFlags flags)
// 		{
// 			uint32_t mem_type_count = mem_props.memoryTypeCount;

// 			for (uint32_t i = 0; i < mem_type_count; ++i)
// 			{
// 				uint32_t match = (mem_reqs->memoryTypeBits & (1 << i)) && (mem_props.memoryTypes[i].propertyFlags & flags);

// 				if (match)
// 				{
// 					return i;
// 				}
// 			}

// 			return -1;
// 		}

// 		VkDeviceMemory Mem
// 		(
// 			VkDeviceSize                 allocationSize  = 0,
// 			uint32_t                     memoryTypeIndex = 0,
// 			const void*                  pNext           = nullptr,
// 			const VkAllocationCallbacks* pAllocator      = nullptr
// 		)
// 		{
// 			VkMemoryAllocateInfo info =
// 			{
// 				VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
// 				pNext,
// 				allocationSize,
// 				memoryTypeIndex,
// 			};

// 			VkDeviceMemory mem = VK_NULL_HANDLE;

// 			vkAllocateMemory(handle, &info, pAllocator, &mem);

// 			memories.push_back(mem);

// 			return mem;
// 		}

// 		void bindMem (VkImage image, VkDeviceMemory mem, VkDeviceSize offset = 0)
// 		{
// 			vkBindImageMemory(handle, image, mem, offset);
// 		}

// 		void bindMem (VkBuffer buffer, VkDeviceMemory mem, VkDeviceSize offset = 0)
// 		{
// 			vkBindBufferMemory(handle, buffer, mem, offset);
// 		}

// 		void* mapMem (VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags)
// 		{
// 			void* mem_addr = nullptr;

// 			vkMapMemory(handle, memory, offset, size, flags, &mem_addr);

// 			return mem_addr;
// 		}

// 		VkFramebuffer Framebuffer
// 		(
// 			VkRenderPass                 renderPass      = VK_NULL_HANDLE,
// 			uint32_t                     attachmentCount = 0,
// 			const VkImageView*           pAttachments    = nullptr,
// 			uint32_t                     width           = 0,
// 			uint32_t                     height          = 0,
// 			uint32_t                     layers          = 0,
// 			VkFramebufferCreateFlags     flags           = 0,
// 			const void*                  pNext           = nullptr,
// 			const VkAllocationCallbacks* pAllocator      = nullptr
// 		)
// 		{
// 			VkFramebufferCreateInfo info =
// 			{
// 				VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
// 				pNext,
// 				flags,
// 				renderPass,
// 				attachmentCount,
// 				pAttachments,
// 				width,
// 				height,
// 				layers,
// 			};

// 			VkFramebuffer framebuffer = VK_NULL_HANDLE;

// 			vkCreateFramebuffer(handle, &info, pAllocator, &framebuffer);

// 			framebuffers.push_back(framebuffer);

// 			return framebuffer;
// 		}

// 		VkFence Fence
// 		(
// 			VkFenceCreateFlags           flags      = 0,
// 			const void*                  pNext      = nullptr,
// 			const VkAllocationCallbacks* pAllocator = nullptr
// 		)
// 		{
// 			VkFenceCreateInfo info =
// 			{
// 				VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
// 				pNext,
// 				flags,
// 			};

// 			VkFence fence = VK_NULL_HANDLE;

// 			vkCreateFence(handle, &info, pAllocator, &fence);

// 			fences.push_back(fence);

// 			return fence;
// 		}

// 		VkSemaphore Semaphore
// 		(
// 			VkSemaphoreCreateFlags       flags      = 0,
// 			const void*                  pNext      = nullptr,
// 			const VkAllocationCallbacks* pAllocator = nullptr
// 		)
// 		{
// 			VkSemaphoreCreateInfo info =
// 			{
// 				VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
// 				pNext,
// 				flags,
// 			};

// 			VkSemaphore semaphore = VK_NULL_HANDLE;

// 			vkCreateSemaphore(handle, &info, pAllocator, &semaphore);

// 			semaphores.push_back(semaphore);

// 			return semaphore;
// 		}

// 		VkBuffer Buffer
// 		(
// 			VkDeviceSize                 size                  = 0,
// 			VkBufferUsageFlags           usage                 = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
// 			VkSharingMode                sharingMode           = VK_SHARING_MODE_EXCLUSIVE,
// 			uint32_t                     queueFamilyIndexCount = 0,
// 			const uint32_t*              pQueueFamilyIndices   = 0,
// 			VkBufferCreateFlags          flags                 = 0,
// 			const void*                  pNext                 = nullptr,
// 			const VkAllocationCallbacks* pAllocator            = nullptr
// 		)
// 		{
// 			VkBufferCreateInfo info =
// 			{
// 				VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
// 				pNext,
// 				flags,
// 				size,
// 				usage,
// 				sharingMode,
// 				queueFamilyIndexCount,
// 				pQueueFamilyIndices,
// 			};

// 			VkBuffer buffer = VK_NULL_HANDLE;

// 			vkCreateBuffer(handle, &info, pAllocator, &buffer);

// 			buffers.push_back(buffer);

// 			return buffer;
// 		}

// 		VkDescriptorSetLayout DescrSetLayout
// 		(
// 			uint32_t                            bindingCount = 0,
// 			const VkDescriptorSetLayoutBinding* pBindings    = nullptr,
// 			VkDescriptorSetLayoutCreateFlags    flags        = 0,
// 			const void*                         pNext        = nullptr,
// 			const VkAllocationCallbacks*        pAllocator   = nullptr
// 		)
// 		{
// 			VkDescriptorSetLayoutCreateInfo info =
// 			{
// 				VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
// 				pNext,
// 				flags,
// 				bindingCount,
// 				pBindings,
// 			};

// 			VkDescriptorSetLayout layout = VK_NULL_HANDLE;

// 			vkCreateDescriptorSetLayout(handle, &info, pAllocator, &layout);

// 			descr_set_layouts.push_back(layout);

// 			return layout;
// 		}

// 		VkDescriptorPool DescrPool
// 		(
// 			uint32_t                     maxSets       = 0,
// 			uint32_t                     poolSizeCount = 0,
// 			const VkDescriptorPoolSize*  pPoolSizes    = nullptr,
// 			VkDescriptorPoolCreateFlags  flags         = 0,
// 			const void*                  pNext         = nullptr,
// 			const VkAllocationCallbacks* pAllocator    = nullptr
// 		)
// 		{
// 			VkDescriptorPoolCreateInfo info =
// 			{
// 				VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
// 				pNext,
// 				flags,
// 				maxSets,
// 				poolSizeCount,
// 				pPoolSizes,
// 			};

// 			VkDescriptorPool pool = VK_NULL_HANDLE;

// 			vkCreateDescriptorPool(handle, &info, pAllocator, &pool);
// 			// cout << vkCreateDescriptorPool(handle, &info, pAllocator, &pool) << endl;

// 			descr_pools.push_back(pool);

// 			return pool;
// 		}

// 		std::vector<VkDescriptorSet> DescrSet
// 		(
// 			VkDescriptorPool             descriptorPool        = VK_NULL_HANDLE,
// 			uint32_t                     descriptorSetCount    = 0,
// 			const VkDescriptorSetLayout* pSetdescr_set_layouts = nullptr,
// 			const void*                  pNext                 = nullptr
// 		)
// 		{
// 			VkDescriptorSetAllocateInfo info =
// 			{
// 				VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
// 				pNext,
// 				descriptorPool,
// 				descriptorSetCount,
// 				pSetdescr_set_layouts,
// 			};

// 			std::vector<VkDescriptorSet> sets(descriptorSetCount);

// 			vkAllocateDescriptorSets(handle, &info, sets.data());
// 			// cout << vkAllocateDescriptorSets(handle, &info, sets.data()) << endl;

// 			return sets;
// 		}

// 		void updateDescrSets
// 		(
// 			uint32_t descriptorWriteCount,
// 			const VkWriteDescriptorSet* pDescriptorWrites,
// 			uint32_t descriptorCopyCount,
// 			const VkCopyDescriptorSet* pDescriptorCopies
// 		)
// 		{
// 			vkUpdateDescriptorSets(handle, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
// 		}

// 		VkShaderModule Shader
// 		(
// 			size_t                       codeSize   = 0,
// 			const uint32_t*              pCode      = nullptr,
// 			VkShaderModuleCreateFlags    flags      = 0,
// 			const void*                  pNext      = nullptr,
// 			const VkAllocationCallbacks* pAllocator = nullptr
// 		)
// 		{
// 			VkShaderModuleCreateInfo info =
// 			{
// 				VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
// 				pNext,
// 				flags,
// 				codeSize,
// 				pCode,
// 			};

// 			VkShaderModule module = VK_NULL_HANDLE;

// 			vkCreateShaderModule(handle, &info, pAllocator, &module);

// 			shader_modules.push_back(module);

// 			return module;
// 		}

// 		VkPipelineLayout PplLayout
// 		(
// 			uint32_t                     setLayoutCount         = 0,
// 			const VkDescriptorSetLayout* pSetdescr_set_layouts  = nullptr,
// 			uint32_t                     pushConstantRangeCount = 0,
// 			const VkPushConstantRange*   pPushConstantRanges    = nullptr,
// 			VkPipelineLayoutCreateFlags  flags                  = 0,
// 			const void*                  pNext                  = nullptr,
// 			const VkAllocationCallbacks* pAllocator             = nullptr
// 		)
// 		{
// 			VkPipelineLayoutCreateInfo info =
// 			{
// 				VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
// 				pNext,
// 				flags,
// 				setLayoutCount,
// 				pSetdescr_set_layouts,
// 				pushConstantRangeCount,
// 				pPushConstantRanges,
// 			};

// 			VkPipelineLayout layout = VK_NULL_HANDLE;

// 			vkCreatePipelineLayout(handle, &info, pAllocator, &layout);

// 			ppl_layouts.push_back(layout);

// 			return layout;
// 		}

// 		VkPipeline PplG
// 		(
// 			uint32_t                                      stageCount          = 0,
// 			const VkPipelineShaderStageCreateInfo*        pStages             = nullptr,
// 			const VkPipelineVertexInputStateCreateInfo*   pVertexInputState   = nullptr,
// 			const VkPipelineInputAssemblyStateCreateInfo* pInputAssemblyState = nullptr,
// 			const VkPipelineTessellationStateCreateInfo*  pTessellationState  = nullptr,
// 			const VkPipelineViewportStateCreateInfo*      pViewportState      = nullptr,
// 			const VkPipelineRasterizationStateCreateInfo* pRasterizationState = nullptr,
// 			const VkPipelineMultisampleStateCreateInfo*   pMultisampleState   = nullptr,
// 			const VkPipelineDepthStencilStateCreateInfo*  pDepthStencilState  = nullptr,
// 			const VkPipelineColorBlendStateCreateInfo*    pColorBlendState    = nullptr,
// 			const VkPipelineDynamicStateCreateInfo*       pDynamicState       = nullptr,
// 			VkPipelineLayout                              layout              = VK_NULL_HANDLE,
// 			VkRenderPass                                  renderPass          = VK_NULL_HANDLE,
// 			uint32_t                                      subpass             = 0,
// 			VkPipeline                                    basePipelineHandle  = VK_NULL_HANDLE,
// 			int32_t                                       basePipelineIndex   = 0,
// 			VkPipelineCreateFlags                         flags               = 0,
// 			const void*                                   pNext               = nullptr,
// 			VkPipelineCache                               pipelineCache       = VK_NULL_HANDLE,
// 			const VkAllocationCallbacks*                  pAllocator          = nullptr
// 		)
// 		{
// 			VkGraphicsPipelineCreateInfo info =
// 			{
// 				VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
// 				pNext,
// 				flags,
// 				stageCount,
// 				pStages,
// 				pVertexInputState,
// 				pInputAssemblyState,
// 				pTessellationState,
// 				pViewportState,
// 				pRasterizationState,
// 				pMultisampleState,
// 				pDepthStencilState,
// 				pColorBlendState,
// 				pDynamicState,
// 				layout,
// 				renderPass,
// 				subpass,
// 				basePipelineHandle,
// 				basePipelineIndex,
// 			};

// 			VkPipeline pipeline = VK_NULL_HANDLE;

// 			vkCreateGraphicsPipelines(handle, pipelineCache, 1, &info, pAllocator, &pipeline);

// 			pipelines.push_back(pipeline);

// 			return pipeline;
// 		}

// 		VkCommandPool CmdPool
// 		(
// 			uint32_t                     queueFamilyIndex = 0,
// 			VkCommandPoolCreateFlags     flags            = 0,
// 			const void*                  pNext            = nullptr,
// 			const VkAllocationCallbacks* pAllocator       = nullptr
// 		)
// 		{
// 			VkCommandPoolCreateInfo info =
// 			{
// 				VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
// 				pNext,
// 				flags,
// 				queueFamilyIndex,
// 			};

// 			VkCommandPool pool = VK_NULL_HANDLE;

// 			vkCreateCommandPool(handle, &info, pAllocator, &pool);

// 			cmd_pools.push_back(pool);

// 			return pool;
// 		}

// 		std::vector<VkCommandBuffer> CmdBuffer
// 		(
// 			VkCommandPool        commandPool        = VK_NULL_HANDLE,
// 			VkCommandBufferLevel level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
// 			uint32_t             commandBufferCount = 0,
// 			const void*          pNext              = nullptr
// 		)
// 		{
// 			VkCommandBufferAllocateInfo info =
// 			{
// 				VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
// 				pNext,
// 				commandPool,
// 				level,
// 				commandBufferCount,
// 			};

// 			std::vector<VkCommandBuffer> buffers(commandBufferCount);

// 			vkAllocateCommandBuffers(handle, &info, buffers.data());

// 			return buffers;
// 		}

// 		void destroy (void)
// 		{
// 			delete[] surface_formats;
// 			delete[] queue_family_props;

// 			for (uint64_t i = 0; i < render_passes.size(); ++i)
// 			{
// 				vkDestroyRenderPass(handle, render_passes[i], nullptr);
// 			}

// 			render_passes.resize(0);

// 			for (uint64_t i = 0; i < swapchains.size(); ++i)
// 			{
// 				vkDestroySwapchainKHR(handle, swapchains[i], nullptr);
// 			}

// 			swapchains.resize(0);

// 			for (uint64_t i = 0; i < image_views.size(); ++i)
// 			{
// 				vkDestroyImageView(handle, image_views[i], nullptr);
// 			}

// 			image_views.resize(0);

// 			for (uint64_t i = 0; i < images.size(); ++i)
// 			{
// 				vkDestroyImage(handle, images[i], nullptr);
// 			}

// 			images.resize(0);

// 			for (uint64_t i = 0; i < memories.size(); ++i)
// 			{
// 				vkFreeMemory(handle, memories[i], nullptr);
// 			}

// 			memories.resize(0);

// 			for (uint64_t i = 0; i < framebuffers.size(); ++i)
// 			{
// 				vkDestroyFramebuffer(handle, framebuffers[i], nullptr);
// 			}

// 			framebuffers.resize(0);

// 			for (uint64_t i = 0; i < fences.size(); ++i)
// 			{
// 				vkDestroyFence(handle, fences[i], nullptr);
// 			}

// 			fences.resize(0);

// 			for (uint64_t i = 0; i < semaphores.size(); ++i)
// 			{
// 				vkDestroySemaphore(handle, semaphores[i], nullptr);
// 			}

// 			semaphores.resize(0);

// 			for (uint64_t i = 0; i < buffers.size(); ++i)
// 			{
// 				vkDestroyBuffer(handle, buffers[i], nullptr);
// 			}

// 			buffers.resize(0);

// 			for (uint64_t i = 0; i < descr_set_layouts.size(); ++i)
// 			{
// 				vkDestroyDescriptorSetLayout(handle, descr_set_layouts[i], nullptr);
// 			}

// 			descr_set_layouts.resize(0);

// 			for (uint64_t i = 0; i < ppl_layouts.size(); ++i)
// 			{
// 				vkDestroyPipelineLayout(handle, ppl_layouts[i], nullptr);
// 			}

// 			ppl_layouts.resize(0);

// 			for (uint64_t i = 0; i < descr_pools.size(); ++i)
// 			{
// 				vkDestroyDescriptorPool(handle, descr_pools[i], nullptr);
// 			}

// 			descr_pools.resize(0);

// 			for (uint64_t i = 0; i < shader_modules.size(); ++i)
// 			{
// 				vkDestroyShaderModule(handle, shader_modules[i], nullptr);
// 			}

// 			shader_modules.resize(0);

// 			for (uint64_t i = 0; i < pipelines.size(); ++i)
// 			{
// 				vkDestroyPipeline(handle, pipelines[i], nullptr);
// 			}

// 			pipelines.resize(0);

// 			for (uint64_t i = 0; i < cmd_pools.size(); ++i)
// 			{
// 				vkDestroyCommandPool(handle, cmd_pools[i], nullptr);
// 			}

// 			cmd_pools.resize(0);

// 			vkDestroyDevice(handle, nullptr);
// 		}
// 	};
}



// #undef SHARED_LIBRARY_FREE
// #undef SHARED_LIBRARY_LOAD
// #undef SHARED_LIBRARY_MODULE_INIT_VALUE
#undef SHARED_LIBRARY_MODULE_TYPE




namespace XGK
{
	namespace VULKAN
	{
		RendererBase::RendererBase (API::Renderer* _wrapper)
		{
			wrapper = _wrapper;
		}



		Renderer::Renderer (API::Renderer* _wrapper) : RendererBase(_wrapper)
		{
			glfwInit();

			glfwDefaultWindowHints();
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

			window = glfwCreateWindow(wrapper->width, wrapper->height, "", nullptr, nullptr);

			glfwMakeContextCurrent(window);



			curr_image = 0;

			const char* inst_exts []
			#ifdef DEBUG
				#if defined(__linux__)
					{ "VK_KHR_surface", "VK_KHR_xlib_surface", VK_EXT_DEBUG_REPORT_EXTENSION_NAME };
				#elif defined(_WIN64)
					{ "VK_KHR_surface", "VK_KHR_win32_surface", VK_EXT_DEBUG_REPORT_EXTENSION_NAME };
				#endif
			#else
				#if defined(__linux__)
					{ "VK_KHR_surface", "VK_KHR_xlib_surface" };
				#elif defined(_WIN64)
					{ "VK_KHR_surface", "VK_KHR_win32_surface" };
				#endif
			#endif

			VkApplicationInfo app_i { AppI() };

			#ifdef DEBUG
				const char* inst_layers [] { "VK_LAYER_KHRONOS_validation" };

				inst.create(&app_i, 1, inst_layers, 3, inst_exts);
			#else
				inst.create(&app_i, 0, nullptr, 2, inst_exts);
			#endif

			// cout << inst.physical_devices << endl;

			VkPhysicalDevice physical_device { inst.physical_devices[0] };
			// VkPhysicalDeviceProperties pProperties = {};
			// vkGetPhysicalDeviceProperties(physical_device, &pProperties);
			// cout << inst.physical_device_count << endl;
			// cout << pProperties.apiVersion << endl;
			// cout << pProperties.driverVersion << endl;
			// cout << pProperties.vendorID << endl;
			// cout << pProperties.deviceID << endl;
			// cout << pProperties.deviceType << endl;
			// cout

			surf =
			#if defined(__linux__)
				inst.SurfaceKHR(glfwGetX11Display(), glfwGetX11Window(window));
			#elif defined(_WIN64)
				inst.SurfaceKHR(GetModuleHandle(nullptr), glfwGetWin32Window(window));
			#endif

			const char* dev_exts [] { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

			device.getProps(physical_device, surf);

			static const float queue_priorities { 1.0f };

			std::vector<VkDeviceQueueCreateInfo> queue_ci { DevQueueCI(device.graphics_queue_family_index, 1, &queue_priorities) };

			if (device.graphics_queue_family_index != device.present_queue_family_index)
			{
				queue_ci.push_back(DevQueueCI(device.present_queue_family_index, 1, &queue_priorities));
			}

			// cout << "G " << device.graphics_queue_family_index << endl;
			// cout << "P " <<  device.present_queue_family_index << endl;

			device.create(physical_device, device.graphics_queue_family_index != device.present_queue_family_index ? 2 : 1, queue_ci.data(), 0, nullptr, 1, dev_exts);

			graphics_queue = device.Queue(device.graphics_queue_family_index, 0);
			present_queue = device.Queue(device.present_queue_family_index, 0);



			// render pass

			// objects accessed by render pass
			VkAttachmentDescription render_pass_attach []
			{
				// color
				{
					0,
					VK_FORMAT_B8G8R8A8_UNORM,
					VK_SAMPLE_COUNT_1_BIT,
					// VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_DONT_CARE,
					VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE,
					VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE,
					VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
				},


				// depth
				{
					0,
					VK_FORMAT_D32_SFLOAT,
					VK_SAMPLE_COUNT_1_BIT,
					VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_DONT_CARE,
					VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE,
					VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
				},

				// // color_resolve
				// {
				//   0,
				//   VK_FORMAT_B8G8R8A8_UNORM,
				//   VK_SAMPLE_COUNT_1_BIT,
				//   VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_STORE,
				//   VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE,
				//   VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
				// },
			};

			// object accessed by subpass
			VkAttachmentReference color_attach_ref { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
			VkAttachmentReference depth_attach_ref { 1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL };
			// VkAttachmentReference color_attach_resolve_ref = { 2, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };

			VkSubpassDescription subpass_desc
			{
				0, VK_PIPELINE_BIND_POINT_GRAPHICS,
				0, nullptr,
				// 1, &color_attach_ref, &color_attach_resolve_ref, &depth_attach_ref
				1, &color_attach_ref, nullptr, &depth_attach_ref
			};

			VkSubpassDependency subpass_dep
			{
				VK_SUBPASS_EXTERNAL, 0,
				VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
				0, VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT
			};

			render_pass =
				device.RenderPass
				(
					// 3, render_pass_attach,
					2, render_pass_attach,
					1, &subpass_desc,
					1, &subpass_dep
				);



			const uint32_t qfi [] { device.graphics_queue_family_index, device.present_queue_family_index };

			swapchain = device.SwapchainKHR
			(
				surf,
				8,
				VK_FORMAT_B8G8R8A8_UNORM,
				VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
				800, 600,
				1,
				VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
				// VK_SHARING_MODE_EXCLUSIVE,
				// 0, nullptr,
				VK_SHARING_MODE_CONCURRENT,
				2, qfi,
				VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
				VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
				VK_PRESENT_MODE_IMMEDIATE_KHR,
				// VK_PRESENT_MODE_FIFO_KHR,
				// VK_PRESENT_MODE_FIFO_RELAXED_KHR,
				VK_TRUE
			);

			std::vector<VkImage> swapchain_images { device.getSwapchainImages(swapchain) };

			swapchain_image_count = swapchain_images.size();

			std::vector<VkImageView> swapchain_image_views(swapchain_image_count);
			std::vector<VkImage> render_images(swapchain_image_count);
			VkMemoryRequirements render_image_mem_reqs {};
			uint64_t render_image_dev_local_mem_index {};
			std::vector<VkDeviceMemory> render_image_mems(swapchain_image_count);
			std::vector<VkImageView> render_image_views(swapchain_image_count);
			framebuffers.resize(swapchain_image_count);
			submission_completed_fences.resize(swapchain_image_count);
			submission_completed_semaphores.resize(swapchain_image_count);
			image_available_semaphores.resize(swapchain_image_count);

			std::vector<VkImage> depth_images(swapchain_image_count);
			std::vector<VkImageView> depth_image_views(swapchain_image_count);
			VkMemoryRequirements depth_image_mem_reqs {};
			uint64_t depth_image_dev_local_mem_index {};
			std::vector<VkDeviceMemory> depth_image_mems(swapchain_image_count);

			for (uint64_t i = 0; i < swapchain_image_count; ++i)
			{
				swapchain_image_views[i] = device.ImageView
				(
					swapchain_images[i],
					VK_IMAGE_VIEW_TYPE_2D,
					VK_FORMAT_B8G8R8A8_UNORM,
					VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
					VK_IMAGE_ASPECT_COLOR_BIT,
					0, 1,
					0, 1
				);

				render_images[i] = device.Image
				(
					VK_IMAGE_TYPE_2D,
					VK_FORMAT_B8G8R8A8_UNORM,
					800, 600, 1,
					1,
					1,
					VK_SAMPLE_COUNT_1_BIT,
					VK_IMAGE_TILING_OPTIMAL,
					VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
					VK_SHARING_MODE_EXCLUSIVE,
					0, nullptr,
					VK_IMAGE_LAYOUT_UNDEFINED
				);

				if (!i)
				{
					render_image_mem_reqs = device.MemReqs(render_images[i]);

					render_image_dev_local_mem_index = device.getMemTypeIndex(&render_image_mem_reqs, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
				}

				render_image_mems[i] = device.Mem(render_image_mem_reqs.size, render_image_dev_local_mem_index);

				device.bindMem(render_images[i], render_image_mems[i]);

				render_image_views[i] = device.ImageView
				(
					render_images[i],
					VK_IMAGE_VIEW_TYPE_2D,
					VK_FORMAT_B8G8R8A8_UNORM,
					VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
					VK_IMAGE_ASPECT_COLOR_BIT,
					0, 1,
					0, 1
				);



				depth_images[i] = device.Image
				(
					VK_IMAGE_TYPE_2D,
					VK_FORMAT_D32_SFLOAT,
					800, 600, 1,
					1,
					1,
					VK_SAMPLE_COUNT_1_BIT,
					VK_IMAGE_TILING_OPTIMAL,
					VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
					VK_SHARING_MODE_EXCLUSIVE,
					0, nullptr,
					VK_IMAGE_LAYOUT_UNDEFINED
				);

				if (!i)
				{
					depth_image_mem_reqs = device.MemReqs(depth_images[i]);

					depth_image_dev_local_mem_index = device.getMemTypeIndex(&depth_image_mem_reqs, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
				}

				depth_image_mems[i] = device.Mem(depth_image_mem_reqs.size, depth_image_dev_local_mem_index);

				device.bindMem(depth_images[i], depth_image_mems[i]);

				depth_image_views[i] = device.ImageView
				(
					depth_images[i],
					VK_IMAGE_VIEW_TYPE_2D,
					VK_FORMAT_D32_SFLOAT,
					VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
					VK_IMAGE_ASPECT_DEPTH_BIT,
					0, 1,
					0, 1
				);



				// VkImageView framebuffer_attach[] = { render_image_views[i], depth_image_views[i], swapchain_image_views[i] };
				// VkImageView framebuffer_attach[] = { render_image_views[i], depth_image_views[i], swapchain_image_views[i] };
				VkImageView framebuffer_attach [] { swapchain_image_views[i], depth_image_views[i] };

				framebuffers[i] = device.Framebuffer
				(
					render_pass,
					// 3, framebuffer_attach,
					2, framebuffer_attach,
					800, 600,
					1
				);

				submission_completed_fences[i] = device.Fence(VK_FENCE_CREATE_SIGNALED_BIT);

				VkSemaphoreTypeCreateInfo semaphore_type_ci
				{
					VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
					nullptr,
					VK_SEMAPHORE_TYPE_BINARY,
					0
				};

				submission_completed_semaphores[i] = device.Semaphore(0, &semaphore_type_ci);
				image_available_semaphores[i] = device.Semaphore(0, &semaphore_type_ci);
			}



			// command buffers

			VkCommandPool cmd_pool { device.CmdPool(device.graphics_queue_family_index, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT) };

			cmd_buffers = device.CmdBuffer(cmd_pool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, swapchain_image_count);



			// VkCommandBufferBeginInfo command_buffer_bi = CmdBufferBeginI(nullptr, VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT);

			clear_value[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
			clear_value[1].depthStencil = { 1.0f, 0 };

			submit_i.resize(swapchain_image_count);
			present_i.resize(swapchain_image_count);
			image_indices.resize(swapchain_image_count);
			render_pass_bi.resize(swapchain_image_count);

			static const VkPipelineStageFlags wait_stages { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

			for (uint64_t i = 0; i < swapchain_image_count; ++i)
			{
				submit_i[i] =
					SubmitI
					(
						1, &image_available_semaphores[i], &wait_stages,
						1, &cmd_buffers[i],
						1, &submission_completed_semaphores[i]
					);

				present_i[i] =
					PresentI
					(
						1, &submission_completed_semaphores[i],
						1, &swapchain,
						nullptr
					);

				render_pass_bi[i] = RenderPassBeginI(render_pass, framebuffers[i], { 0, 0, 800, 600 }, 2, clear_value);
			}
		}

		void Renderer::endLoop (void)
		{
			// glfwSwapBuffers(window);
		}

		void Renderer::destroy (void)
		{
			vkDeviceWaitIdle(device.handle);

			device.destroy();

			inst.destroy();

			glfwDestroyWindow(window);

			glfwTerminate();
		}



		// RendererOffscreen::RendererOffscreen (API::Renderer* _wrapper) : RendererBase(_wrapper)
		// {
		// 	glfwHideWindow(window);

		// 	glfwSwapInterval(1);



		// 	// Framebuffer object for offscreen rendering
		// 	{
		// 		glCreateFramebuffers(1, &framebuffer);
		// 		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
		// 		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		// 		glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);

		// 		glCreateRenderbuffers(1, &framebuffer_renderbuffer_color);
		// 		glBindRenderbuffer(GL_RENDERBUFFER, framebuffer_renderbuffer_color);
		// 		glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, wrapper->width, wrapper->height);
		// 		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		// 		glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, framebuffer_renderbuffer_color);

		// 		// Depth attachment
		// 		// TODO: make depth buffer optional.
		// 		{
		// 			glEnable(GL_DEPTH_TEST);
		// 			glDepthFunc(GL_LEQUAL);

		// 			glCreateRenderbuffers(1, &framebuffer_renderbuffer_depth);
		// 			glBindRenderbuffer(GL_RENDERBUFFER, framebuffer_renderbuffer_depth);
		// 			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, wrapper->width, wrapper->height);
		// 			glBindRenderbuffer(GL_RENDERBUFFER, 0);

		// 			glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, framebuffer_renderbuffer_depth);
		// 		}

		// 		// glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		// 	}



		// 	// Pixel pack buffer
		// 	{
		// 		glCreateBuffers(1, &pixel_pack_buffer);

		// 		glBindBuffer(GL_PIXEL_PACK_BUFFER, pixel_pack_buffer);
		// 		// TODO: cache wrapper->width * wrapper->height * 4
		// 		glBufferData(GL_PIXEL_PACK_BUFFER, wrapper->width * wrapper->height * 4, nullptr, GL_DYNAMIC_READ);

		// 		// Redundant call. GL_COLOR_ATTACHMENT0 is a default framebuffer read buffer.
		// 		glReadBuffer(GL_COLOR_ATTACHMENT0);
		// 		glReadPixels(0, 0, wrapper->width, wrapper->height, GL_RGBA, GL_UNSIGNED_BYTE, 0);

		// 		pixel_data = glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
		// 	}
		// }

		// void RendererOffscreen::endLoop (void)
		// {
		// 	// glBindBuffer(GL_PIXEL_PACK_BUFFER, pixel_pack_buffer);
		// 	glBufferData(GL_PIXEL_PACK_BUFFER, wrapper->width * wrapper->height * 4, nullptr, GL_DYNAMIC_READ);
		// 	// glReadBuffer(GL_COLOR_ATTACHMENT0);
		// 	glReadPixels(0, 0, wrapper->width, wrapper->height, GL_RGBA, GL_UNSIGNED_BYTE, 0);

		// 	pixel_data = glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);

		// 	// if (pixel_data)
		// 	// {
		// 	// 	glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
		// 	// }

		// 	// glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		// 	// glDrawBuffer(GL_BACK);
		// 	// glReadBuffer(GL_FRONT);
		// }



		// void Uniform::uniformMatrix4fv (Uniform* uniform)
		// {
		// 	glUniformMatrix4fv(uniform->location, 1, false, (float*) uniform->wrapper->object_addr);
		// }

		// Uniform::Uniform (RendererBase* _renderer, API::Uniform* _wrapper)
		// {
		// 	renderer = _renderer;
		// 	wrapper = _wrapper;
		// }



		// UniformBlock::UniformBlock (RendererBase* _renderer, API::UniformBlock* _wrapper)
		// {
		// 	renderer = _renderer;
		// 	wrapper = _wrapper;



		// 	for (API::Uniform* uniform_wrapper : wrapper->uniforms)
		// 	{
		// 		Uniform* uniform { new Uniform { renderer, uniform_wrapper } };

		// 		buffer_length += uniform_wrapper->size;

		// 		uniforms.push_back(uniform);
		// 	}



		// 	glGenBuffers(1, &buffer);
		// 	glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		// 	glBindBufferBase(GL_UNIFORM_BUFFER, wrapper->binding, buffer);
		// 	glBufferData(GL_UNIFORM_BUFFER, buffer_length, nullptr, GL_DYNAMIC_DRAW);



		// 	// Initially update uniforms.
		// 	use();
		// }

		// void UniformBlock::use (void)
		// {
		// 	glBindBuffer(GL_UNIFORM_BUFFER, buffer);

		// 	// for (size_t i {}; i < uniforms.size(); ++i)
		// 	// {
		// 	// 	Uniform* uniform = uniforms[i];

		// 	// 	glBufferSubData(GL_UNIFORM_BUFFER, uniform->wrapper->block_index, uniform->wrapper->size, uniform->wrapper->object_addr);
		// 	// }

		// 	for (Uniform* uniform : uniforms)
		// 	{
		// 		glBufferSubData(GL_UNIFORM_BUFFER, uniform->wrapper->block_index, uniform->wrapper->size, uniform->wrapper->object_addr);
		// 	}
		// }



		Material* Material::used_instance {};

		const VkPrimitiveTopology Material::TOPOLOGY [3]
		{
			VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
			VK_PRIMITIVE_TOPOLOGY_POINT_LIST,
			VK_PRIMITIVE_TOPOLOGY_LINE_LIST,
		};

		Material::Material (RendererBase* _renderer, API::Material* _wrapper)
		{
			renderer = _renderer;
			wrapper = _wrapper;



			topology = Material::TOPOLOGY[static_cast<size_t>(wrapper->topology)];



			VkPipelineInputAssemblyStateCreateInfo default_ppl_input_asm { PplInputAsm(topology, VK_FALSE) };

			VkPipelineTessellationStateCreateInfo default_ppl_tess { PplTess(0, 0) };

			// flip vulkan viewport
			VkViewport viewport { 0.0f, 0.0f, static_cast<float>(renderer->wrapper->width), static_cast<float>(renderer->wrapper->height), 0.0f, 1.0f };
			// VkViewport viewport = { 0.0f, 600.0f, 800.0f, -600.0f, 0.0f, 1.0f };
			VkRect2D scissor { { 0, 0 }, { renderer->wrapper->width, renderer->wrapper->height } };

			VkPipelineViewportStateCreateInfo default_ppl_view { PplView(1, &viewport, 1, &scissor) };

			VkPipelineMultisampleStateCreateInfo default_ppl_sample { PplSample(VK_SAMPLE_COUNT_1_BIT, VK_FALSE, 0.0f, nullptr, VK_FALSE, VK_FALSE) };
			// VkPipelineMultisampleStateCreateInfo default_ppl_sample { PplSample(VK_SAMPLE_COUNT_1_BIT, VK_FALSE, 0.0f, nullptr, VK_FALSE, VK_FALSE) };

			VkPipelineRasterizationStateCreateInfo default_ppl_rast { PplRast(VK_FALSE, VK_FALSE, VK_POLYGON_MODE_FILL, VK_CULL_MODE_NONE, VK_FRONT_FACE_COUNTER_CLOCKWISE, VK_FALSE, 0.0f, 0.0f, 0.0f, 1.0f) };

			VkStencilOpState default_ppl_stenc { VK_STENCIL_OP_KEEP, VK_STENCIL_OP_KEEP, VK_STENCIL_OP_KEEP, VK_COMPARE_OP_ALWAYS, 0, 0, 0 };

			VkStencilOpState front
			{
				.failOp = VK_STENCIL_OP_KEEP,
				.passOp = VK_STENCIL_OP_KEEP,
				.compareOp = VK_COMPARE_OP_ALWAYS,
			};

			VkStencilOpState back
			{
				.failOp = VK_STENCIL_OP_KEEP,
				.passOp = VK_STENCIL_OP_KEEP,
				.compareOp = VK_COMPARE_OP_ALWAYS,
			};

			VkPipelineDepthStencilStateCreateInfo default_ppl_depth_stenc { PplDepthStenc(VK_TRUE, VK_TRUE, VK_COMPARE_OP_LESS_OR_EQUAL, VK_FALSE, VK_FALSE, default_ppl_stenc, default_ppl_stenc, 0.0f, 1.0f) };

			// VkPipelineDepthStencilStateCreateInfo default_ppl_depth_stenc { PplDepthStenc(VK_FALSE, VK_FALSE, VK_COMPARE_OP_LESS, VK_FALSE, VK_FALSE, { 0 }, { 0 }, 0.0f, 1.0f) };

			VkPipelineColorBlendAttachmentState blend_attach
			{
				VK_FALSE,
				VK_BLEND_FACTOR_ZERO, VK_BLEND_FACTOR_ZERO, VK_BLEND_OP_ADD,
				VK_BLEND_FACTOR_ZERO, VK_BLEND_FACTOR_ZERO, VK_BLEND_OP_ADD,
				VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
			};

			VkPipelineColorBlendStateCreateInfo default_ppl_blend
			{
				PplBlend
				(
					VK_FALSE,
					VK_LOGIC_OP_CLEAR,
					1, &blend_attach,
					0.0f, 0.0f, 0.0f, 0.0f
				)
			};

			VkPipelineDynamicStateCreateInfo default_ppl_dyn { PplDyn(0, nullptr) };



			VkPipelineShaderStageCreateInfo ppl_stages []
			{
				PplShader(VK_SHADER_STAGE_VERTEX_BIT, renderer->device.Shader(sizeof(wrapper->spirv_code_vertex), wrapper->spirv_code_vertex)),
				PplShader(VK_SHADER_STAGE_FRAGMENT_BIT, renderer->device.Shader(sizeof(wrapper->spirv_code_fragment), wrapper->spirv_code_fragment))
			};

			VkVertexInputBindingDescription vertex_binding { 0, 12, VK_VERTEX_INPUT_RATE_VERTEX };
			VkVertexInputAttributeDescription vertex_attr { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0 };

			VkPipelineVertexInputStateCreateInfo ppl_vertex { PplVertex(1, &vertex_binding, 1, &vertex_attr) };

			VkPipelineLayout ppl_layout = renderer->device.PplLayout(1, &descr_set_layout);

			ppl =
				renderer->device.PplG
				(
					2, ppl_stages,
					&ppl_vertex,
					&default_ppl_input_asm,
					&default_ppl_tess,
					&default_ppl_view,
					&default_ppl_rast,
					&default_ppl_sample,
					&default_ppl_depth_stenc,
					&default_ppl_blend,
					&default_ppl_dyn,
					ppl_layout,
					renderer->render_pass, 0
				);



			// for (API::UniformBlock* uniform_block_wrapper : wrapper->uniform_blocks)
			// {
			// 	UniformBlock* uniform_block { new UniformBlock { renderer, uniform_block_wrapper } };

			// 	glUniformBlockBinding
			// 	(
			// 		program,
			// 		glGetUniformBlockIndex(program, (const GLchar*) uniform_block_wrapper->name.c_str()),
			// 		uniform_block_wrapper->binding
			// 	);

			// 	uniform_blocks.push_back(uniform_block);
			// }



			// Initially update uniforms.
			use();
		}

		void Material::use (void)
		{
			// Material::used_instance = this;

			// glUseProgram(program);

			// // for (size_t i {}; i < uniforms.size(); ++i)
			// // {
			// // 	Uniform* uniform = uniforms[i];

			// // 	uniform->update(uniform);
			// // }

			// for (Uniform* uniform : uniforms)
			// {
			// 	uniform->update(uniform);
			// }
		}



		// Object::Object (RendererBase* _renderer, API::Object* _wrapper)
		// {
		// 	renderer = _renderer;
		// 	wrapper = _wrapper;
		// }

		// void Object::draw (void) const
		// {
		// 	glDrawArrays
		// 	(
		// 		// Material::used_instance->topology,
		// 		GL_TRIANGLES,
		// 		wrapper->scene_vertex_data_offset,
		// 		wrapper->scene_vertex_data_length
		// 	);
		// }



		// Scene::Scene (RendererBase* _renderer, API::Scene* _wrapper)
		// {
		// 	renderer = _renderer;
		// 	wrapper = _wrapper;
		// }
	}
}