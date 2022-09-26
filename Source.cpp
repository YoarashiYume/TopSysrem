#include "App.hpp"


int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR czCmdLine, int nCmdShow)
{
	App app;
	return app.run();
}