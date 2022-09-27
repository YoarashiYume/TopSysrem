#ifndef APP_H
#define APP_H
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib,"d2d1")
#pragma warning(disable: 4996)


#include <Windows.h>
#include <d2d1.h>

#include <stdexcept>

#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <cwctype>

#include "Controls/SimpleEdit.hpp"
#include "Controls/SimpleStatic.hpp"
#include "Controls/SimpleButton.hpp"

#include "DrawerStorage.h"

class App final
{
public:
	using factory_type = ID2D1Factory*;
	using render_target_type = ID2D1HwndRenderTarget*;
	
	using button_type = std::unique_ptr<SimpleButton>;
	using edit_type = std::unique_ptr<SimpleEdit>;
	using label_type = std::unique_ptr<SimpleStatic>;

	using drawer_type = std::unique_ptr<DrawerStorage>;

	enum class ButtonType : std::uint32_t
	{
		SQUARE = 0,
		RECTANGLE,
		PARALLELOGRAM,
		TRAPEZIA,

		RHOMBUS,
		POLYGON,

		TRIANGLE,

		CIRCLE,
		OVAL,

		DRAW
	};
	enum class InputDataList : std::uint32_t
	{
		FIRST = 0,
		SECOND,
		THIRD
	};
private:
	//application settings
	std::uint16_t width,
		height;
	const std::wstring appName{L"Test Task"},
		className{L"Top System Test"};

	//direct2d
	factory_type pD2D1Factory;
	render_target_type pRT;
	MSG msg;


	bool isCorrectInit{ true };

	HWND mainWindow;
	//control
	std::vector<button_type> buttonList;
	std::vector<edit_type> editList;
	std::vector<label_type> staticList;

	//drawer
	drawer_type drawer;
	std::uint32_t fArg{ 0 }, sArg{ 0 }, tArg{0};
public:
	App();
	App(const App&) = delete;
	App(App &&) = delete;

	App(const std::uint16_t windowWidth, const std::uint16_t windowHeight);
	~App();

	std::int32_t run();
private:
	// init functions
	void init_window();
	void init_controls();
	void init_drawer();

	static LRESULT CALLBACK application_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//processing function	
	LRESULT CALLBACK window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void clearData();
	void changeDatavisible(const bool isShown, const App::InputDataList id);
	void updateAllControl();

	//sub-funcion
	bool readArguments();
	void switchToSquare();
	void switchToRectangle();
	void switchToParallelogram();
	void switchToTrapezia();
	void switchToRhombus();
	void switchToPolygon();
	void switchToTriangle();
	void switchToCircle();
	void switchToOval();

};

#endif