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
	SHARED_LIBRARY_MODULE_TYPE shared_library_module_handle {};



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
}



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
				PplShader(VK_SHADER_STAGE_VERTEX_BIT, renderer->device.Shader(sizeof(wrapper->spirv_code_vertex), wrapper->spirv_code_vertex.data())),
				PplShader(VK_SHADER_STAGE_FRAGMENT_BIT, renderer->device.Shader(sizeof(wrapper->spirv_code_fragment), wrapper->spirv_code_fragment.data()))
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
