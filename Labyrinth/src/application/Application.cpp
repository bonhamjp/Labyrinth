#include "Application.h"

#include "score_saver/ScoreSaver.h"

#include <iostream>

namespace Labyrinth
{
	Application* Application::s_Instance = nullptr;

	Application* Application::Create()
	{
		Application* application = new Application();
		
		s_Instance = application;
		s_Instance->Initialize();

		return s_Instance;
	}

	void Application::Delete()
	{
		delete s_Instance;
	}

	Application::Application()
	{
		m_Running = false;
	}

	Application::~Application()
	{
		m_Window.reset();
		m_Renderer.reset();
		m_InputManager.reset();
		m_Clock.reset();
		m_Scene.reset();
		m_TextureManager.reset();
	}

	void Application::Initialize()
	{
		m_Window = std::make_unique<Window>();
		m_Renderer = std::make_unique<Renderer>(GetWindow());
		m_InputManager = std::make_unique<InputManager>();
		m_Clock = std::make_unique<Clock>();
		m_Scene = std::make_unique<Scene>();
		m_TextureManager = std::make_unique<TextureManager>();
	}

	void Application::Run()
	{
		m_Running = true;

		_MainLoop();
	}

	void Application::Win()
	{
		_SaveScore();

		m_Running = false;
	}

	void Application::Stop()
	{
		m_Running = false;
	}

	void Application::_MainLoop()
	{
		while (m_Running)
		{
			_SetTiming();
			
			m_InputManager->Poll();
			
			_Update();
			_Render();
		}
	}

	void Application::_SetTiming()
	{
		m_Clock->Update(SDL_GetTicks() / 1000.0f);
	}

	void Application::_Update()
	{
		m_Scene->Update();
	}

	void Application::_Render()
	{
		m_Renderer->PrepareRender();

		m_Scene->Render();
		m_Renderer->Render();
	}

	void Application::_SaveScore()
	{
		SaveScore(m_Scene->GetRunTime());
	}
}
