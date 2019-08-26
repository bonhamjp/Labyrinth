#pragma once

#include "window/Window.h"
#include "renderer/Renderer.h"
#include "input_manager/InputManager.h"
#include "clock/Clock.h"
#include "scene/Scene.h"
#include "texture/TextureManager.h"

#include <memory>

#include <SDL.h>
#undef main

namespace Labyrinth
{
	class Application
	{
	public:
		static Application* Create();
		static void Delete();

		inline static Application& Get() { return *s_Instance; }
		inline static Window& MainWindow() { return Application::Get().GetWindow(); };
		inline static Renderer& MainRenderer() { return Application::Get().GetRenderer(); }
		inline static InputManager& MainInputManager() { return Application::Get().GetInputManager(); }
		inline static Clock& MainClock() { return Application::Get().GetClock(); }
		inline static Scene& MainScene() { return Application::Get().GetScene(); }
		inline static TextureManager& MainTextureManager() { return Application::Get().GetTextureManager(); };

		Application();
		~Application();

		void Initialize();

		void Run();
		void Win();
		void Stop();

		Window& GetWindow() { return *m_Window; };
		Renderer& GetRenderer() { return *m_Renderer; };
		InputManager& GetInputManager() { return *m_InputManager; };
		Clock& GetClock() { return *m_Clock; };
		Scene& GetScene() { return *m_Scene; };
		TextureManager& GetTextureManager() { return *m_TextureManager; };

	private:
		static Application* s_Instance;

		bool m_Running;

		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<InputManager> m_InputManager;
		std::unique_ptr<Clock> m_Clock;
		std::unique_ptr<Scene> m_Scene;
		std::unique_ptr<TextureManager> m_TextureManager;

		void _MainLoop();

		void _SetTiming();
		void _Update();
		void _Render();

		void _SaveScore();
	};
}
