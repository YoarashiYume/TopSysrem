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
/**
\brief App class
*/
class App final
{
public:
	using factory_type = ID2D1Factory*;
	using render_target_type = ID2D1HwndRenderTarget*;
	
	using button_type = std::unique_ptr<SimpleButton>;
	using edit_type = std::unique_ptr<SimpleEdit>;
	using label_type = std::unique_ptr<SimpleStatic>;

	using drawer_type = std::unique_ptr<DrawerStorage>;
	/**
	\brief list of button (and buttons action)
	*/
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
	/**
	\brief list of text box/label ids
	'id' matches the order of the passed parameters to Driver::draw
	*/
	enum class InputDataList : std::uint32_t
	{
		FIRST = 0,
		SECOND,
		THIRD
	};
private:
	//application settings
	
	std::uint16_t width, ///< current window width
		height; ///< current window height
	const std::wstring appName{L"Test Task"}, ///< App title
		className{L"Top System Test"}; ///< app class name

	//direct2d
	factory_type pD2D1Factory; ///< direct2d factory
	render_target_type pRT; ///< direct2d drawing interface
	MSG msg; ///< window interaction information


	bool isCorrectInit{ true }; ///< variable indicating the correctness of the initialization

	HWND mainWindow; ///main window handler
	//control
	std::vector<button_type> buttonList; ///< list of button
	std::vector<edit_type> editList;	///< list of text boxs
	std::vector<label_type> staticList; ///< list of label

	//drawer
	drawer_type drawer; ///< drawer storage
	std::uint32_t fArg{ 0 }, sArg{ 0 }, tArg{0}; ///< argument value for drawer
public:
	/**
	\brief Constructor with base screen height and width values (1280x800)
	*/
	App();
	App(const App&) = delete;
	App(App &&) = delete;
	/**
	\brief Constructor with base screen height and width values (1280x800)
	\param windowWidth,windowHeight window dimensions
	*/
	App(const std::uint16_t windowWidth, const std::uint16_t windowHeight);
	~App();
	/**
	\brief  Method launches the graphical application
	\return exit code
	*/
	std::int32_t run();
private:
	// init functions
	/**
	\brief Method initializes the window
	*/
	void init_window();
	/**
	\brief Method initializes the control components
	*/
	void init_controls();
	/**
	\brief Method initializes the drawer storage
	*/
	void init_drawer();
	/**
	\brief Window registration method
	\param hwnd Window procedure handle
	\param uMsg message
	\param wParam,lParam additional information message
	\return DefWindowProc value
	*/
	static LRESULT CALLBACK application_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//processing method	
	/**
	\brief message handling method
	\param hwnd Window procedure handle
	\param uMsg message
	\param wParam,lParam additional information message
	\return DefWindowProc value
	*/
	LRESULT CALLBACK window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	/**
	\brief Method reset text from all text boxs and labels
	*/
	void clearData();
	/**
	\brief Method sets the visibility state for certain text fields and labels
	\param isShown new visibility state
	\param id id of elements
	*/
	void changeDatavisible(const bool isShown, const App::InputDataList id);
	/**
	\brief Method updates visibility after drawing (unused)
	*/
	void updateAllControl();

	//sub-funcion
	/**
	\brief Method reads data from active text fields
	*/
	bool readArguments();
	/**
	\brief Method sets the number of input elements and their name in accordance with the SquareDriwer parameters
	*/
	void switchToSquare();
	/**
	\brief Method sets the number of input elements and their name in accordance with the RectangleDriwer parameters
	*/
	void switchToRectangle();
	/**
	\brief Method sets the number of input elements and their name in accordance with the ParallelogramDriwer parameters
	*/
	void switchToParallelogram();
	/**
	\brief Method sets the number of input elements and their name in accordance with the TrapeziaDriwer parameters
	*/
	void switchToTrapezia();
	/**
	\brief Method sets the number of input elements and their name in accordance with the RhombusDriwer parameters
	*/
	void switchToRhombus();
	/**
	\brief Method sets the number of input elements and their name in accordance with the PolygonDriwer parameters
	*/
	void switchToPolygon();
	/**
	\brief Method sets the number of input elements and their name in accordance with the TriangleDriwer parameters
	*/
	void switchToTriangle();
	/**
	\brief Method sets the number of input elements and their name in accordance with the CircleDriwer parameters
	*/
	void switchToCircle();
	/**
	\brief Method sets the number of input elements and their name in accordance with the OvalDriwer parameters
	*/
	void switchToOval();

};

#endif