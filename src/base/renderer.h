#ifndef __XGK_RENDERERS_BASE__
#define __XGK_RENDERERS_BASE__



// size_t
#include <cstddef>

#include "xgk-api/src/renderer/renderer.h"



namespace XGK
{
	namespace RENDERERS
	{
		enum class RendererType : size_t
		{
			VULKAN,
			OPENGL,
		};



		struct Renderer
		{
			API::Renderer* wrapper {};

			void* pixel_data {};

			RendererType type {};

			virtual void endLoop (void) = 0;
			virtual void destroy (void) = 0;
		};
	}
}



#endif
