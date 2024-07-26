#include "Application.h"
#include <SDL2/SDL.h>


namespace CGL::Core
{
	CGL_DEFINE_LOG_CATEGORY(CoreApp);

	Application::Application()
		: m_isRunning(true)
		, m_window(nullptr)
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			std::string err(SDL_GetError());
			CGL_LOG(CoreApp, Error, "Failed to initialize SDL: {}", err);
		}
		else
		{
			CGL_LOG(CoreApp, Trace, "Core aplication created");
		}

	}

	void Application::Run()
	{
		CGL_LOG(CoreApp, Trace, "Running application");

		OnInit();

		SDL_Event e;
		while (m_isRunning)
		{
			// Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				// User requests quit
				if (e.type == SDL_QUIT)
				{
					m_isRunning = false;
				}
				else if (e.type == SDL_WINDOWEVENT)
				{
					switch (e.window.event)
					{
					case SDL_WINDOWEVENT_RESIZED:
						OnResize(e.window.data1, e.window.data2);
						break;
					}
				}
			}

			OnUpdate();

			// Call begin and end frame before calling render itself
			m_renderer->BeginFrame();
			OnRender();
			m_renderer->EndFrame();
		}

		OnShutdown();
	}

	bool Application::OnInit()
	{
		// Create SDL window
		u32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;

#if defined(CGL_RHI_OPENGL)
		flags |= SDL_WINDOW_OPENGL;
#elif defined(CGL_RHI_VULKAN)
		flags |= SDL_WINDOW_VULKAN;
#endif

		m_window = SDL_CreateWindow("CGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, flags);
		if (!m_window)
		{
			std::string err(SDL_GetError());
			CGL_LOG(CoreApp, Error, "Failed to create SDL window: {}", err);
			return false;
		}

#if defined(CGL_RHI_OPENGL)
		Graphics::RHIType rhi = Graphics::RHIType::OpenGL;
#elif defined (CGL_RHI_DX11)
		Graphics::RHIType rhi = Graphics::RHIType::DirectX11;
#elif defined(CGL_RHI_DX12)
		Graphics::RHIType rhi = Graphics::RHIType::DirectX12;
#elif defined(CGL_RHI_METAL)
		Graphics::RHIType rhi = Graphics::RHIType::Metal;
#elif defined(CGL_RHI_VULKAN)
		Graphics::RHIType rhi = Graphics::RHIType::Vulkan;
#endif

		// Create renderer
		m_renderer = std::make_unique<Graphics::Renderer>(m_window, rhi);
		if (!m_renderer)
		{
			CGL_LOG(CoreApp, Error, "Failed to create renderer");
			return false;
		}

		CGL_LOG(CoreApp, Debug, "Core application initialized");
		return true;
	}

	void Application::OnShutdown()
	{
		m_renderer.reset();

		SDL_DestroyWindow(m_window);
		SDL_Quit();

		CGL_LOG(CoreApp, Debug, "Core application shutdown");
	}

	void Application::OnResize(u32 width, u32 height)
	{
		if (m_renderer)
		{
			m_renderer->Resize(width, height);
		}
	}
}
