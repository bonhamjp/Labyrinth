#include "application/Application.h"

int main(int argc, char** argv)
{
	Labyrinth::Application* application = Labyrinth::Application::Create();

	application->Run();

	Labyrinth::Application::Delete();

	return 0;
}
