#include "App.hpp"

App::App()
	:App (1280, 800)
{
}

App::App(const std::uint16_t windowWidth, const std::uint16_t windowHeight)
	:height(windowHeight), width(windowWidth)
{
	try
	{
		this->init_window();
		this->init_controls();
		this->init_drawer();
	}
	catch (const std::exception& ex)
	{
		isCorrectInit = false;
		MessageBoxA(nullptr, ex.what(), "Error", MB_ICONERROR | MB_OK);
	}
}

App::~App()
{
	pD2D1Factory->Release();
	pRT->Release();
}

std::int32_t App::run()
{
	if (!this->isCorrectInit)
		return -1;
	ShowWindow(this->mainWindow, SW_SHOWDEFAULT);
	UpdateWindow(this->mainWindow);
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return static_cast<std::int32_t> (msg.wParam);
}

void App::init_window()
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_MULTI_THREADED, &pD2D1Factory);
	if (!SUCCEEDED(hr))
		throw std::runtime_error("Cannot create factory");
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = this->className.c_str();
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = App::application_proc;


	if (!RegisterClassEx(&wc)) throw std::runtime_error("Cannot register main window");

	RECT windowRC{ 0,0,this->width,this->height };

	AdjustWindowRect(&windowRC, WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX , false);
	this->mainWindow = CreateWindowEx(
		0,
		this->className.c_str(),
		this->appName.c_str(),
		WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX ,
		0,
		0,
		this->width, windowRC.bottom, nullptr, nullptr, nullptr, this
	);
	if (!this->mainWindow)
		throw std::runtime_error("Cannot create main window");

}

void App::init_controls()
{
	std::uint16_t yOffset = 0;
	constexpr std::uint16_t offset = 20;


	// create static and Edit
	this->staticList.emplace_back(new SimpleStatic{ this->mainWindow,L"First parameter",10, yOffset, 200, 20 });
	yOffset += offset;
	this->editList.emplace_back(new SimpleEdit{ this->mainWindow,L"0",10, yOffset, 100, 20 });
	yOffset += offset;
	this->staticList.emplace_back(new SimpleStatic{ this->mainWindow,L"Second parameter",10, yOffset, 200, 20 });
	yOffset += offset;
	this->editList.emplace_back(new SimpleEdit{ this->mainWindow,L"0",10, yOffset, 100, 20 });
	yOffset += offset;
	this->staticList.emplace_back(new SimpleStatic{ this->mainWindow,L"Third parameter",10, yOffset, 200, 20 });
	yOffset += offset;
	this->editList.emplace_back(new SimpleEdit{ this->mainWindow,L"0",10, yOffset, 100, 20 });

	yOffset = 150;

	//Create button
	this->buttonList.emplace_back(new SimpleButton{ this->mainWindow,static_cast<std::uint32_t>(App::ButtonType::SQUARE),std::wstring{L"Set Square"},10,yOffset, 200,20 });
	yOffset += offset;
	this->buttonList.emplace_back(new SimpleButton{ this->mainWindow,static_cast<std::uint32_t>(App::ButtonType::RECTANGLE),std::wstring{L"Set Rectangle"},10,yOffset, 200,20 });
	yOffset += offset;
	this->buttonList.emplace_back(new SimpleButton{ this->mainWindow,static_cast<std::uint32_t>(App::ButtonType::PARALLELOGRAM),std::wstring{L"Set Parallelogram"},10,yOffset, 200,20 });
	yOffset += offset;
	this->buttonList.emplace_back(new SimpleButton{ this->mainWindow,static_cast<std::uint32_t>(App::ButtonType::TRAPEZIA),std::wstring{L"Set Trapezia"},10,yOffset, 200,20 });
	yOffset += offset;
	this->buttonList.emplace_back(new SimpleButton{ this->mainWindow,static_cast<std::uint32_t>(App::ButtonType::RHOMBUS),std::wstring{L"Set Rhombus"},10,yOffset, 200,20 });
	yOffset += offset;
	this->buttonList.emplace_back(new SimpleButton{ this->mainWindow,static_cast<std::uint32_t>(App::ButtonType::POLYGON),std::wstring{L"Set Polygon"},10,yOffset, 200,20 });
	yOffset += offset;
	this->buttonList.emplace_back(new SimpleButton{ this->mainWindow,static_cast<std::uint32_t>(App::ButtonType::TRIANGLE),std::wstring{L"Set Triangle"},10,yOffset, 200,20 });
	yOffset += offset;
	this->buttonList.emplace_back(new SimpleButton{ this->mainWindow,static_cast<std::uint32_t>(App::ButtonType::CIRCLE),std::wstring{L"Set Circle"},10,yOffset, 200,20 });
	yOffset += offset;
	this->buttonList.emplace_back(new SimpleButton{ this->mainWindow,static_cast<std::uint32_t>(App::ButtonType::OVAL),std::wstring{L"Set Oval"},10,yOffset, 200,20 });

	yOffset += 2*offset;
	this->buttonList.emplace_back(new SimpleButton{ this->mainWindow,static_cast<std::uint32_t>(App::ButtonType::DRAW),std::wstring{L"Draw"},10,yOffset, 200,20 });
	this->buttonList.back()->setVisiability(false);


	//check on error
	if (!std::ranges::all_of(buttonList,&Control::isInit) ||
		!std::ranges::all_of(staticList, &Control::isInit) ||
		!std::ranges::all_of(editList, &Control::isInit))
		throw std::runtime_error("Can`t control");
	//set font
	pD2D1Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(this->mainWindow, D2D1::SizeU(width, height)), &pRT);
	HFONT hFont = CreateFont(18, 0, 0, 0, FW_REGULAR, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Roboto");
	for (auto& el : buttonList)
		SendMessage(el->get(), WM_SETFONT, (WPARAM)hFont, true);
}
void App::init_drawer()
{
	float xTempDPI = 0;
	float yTempDPI = 0;
	pD2D1Factory->GetDesktopDpi(&xTempDPI, &yTempDPI);
	
	drawer.reset(new DrawerStorage{ xTempDPI ,yTempDPI, 210, this->width,this->height, this->pRT });
}
LRESULT App::application_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	App* pApp;
	if (uMsg == WM_NCCREATE)
	{
		pApp = static_cast<App*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pApp)))
			if (GetLastError() != 0)
				return false;
	}
	else
		pApp = reinterpret_cast<App*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (pApp)
	{
		pApp->mainWindow = hwnd;
		return pApp->window_proc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT App::window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		return 0;
	case WM_PAINT:
	{
		
		if (fArg != 0 || sArg != 0 || tArg != 0)
		{
			drawer->draw(this->mainWindow, pRT, fArg, sArg, tArg);
			fArg = sArg = tArg = 0;
			InvalidateRect(this->mainWindow, nullptr, false);
		}
		
		return 0;
	}
	case WM_LBUTTONDOWN:
		return 0;
	case WM_COMMAND:
		switch (static_cast<App::ButtonType>(LOWORD(wParam)))
		{		
		case App::ButtonType::SQUARE:
			this->switchToSquare();
			break;
		case App::ButtonType::RECTANGLE:
			this->switchToRectangle();
			break;
		case App::ButtonType::PARALLELOGRAM:
			this->switchToParallelogram();
			break;
		case App::ButtonType::TRAPEZIA:
			this->switchToTrapezia();
			break;
		case App::ButtonType::RHOMBUS:
			this->switchToRhombus();
			break;
		case App::ButtonType::POLYGON:
			this->switchToPolygon();
			break;
		case App::ButtonType::TRIANGLE:
			this->switchToTriangle();
			break;
		case App::ButtonType::CIRCLE:
			this->switchToCircle();
			break;
		case App::ButtonType::OVAL:
			this->switchToOval();
			break;
		case App::ButtonType::DRAW:
		{
			//read data and draw		
			if (this->readArguments())
				SendMessage(hwnd, WM_PAINT, (WPARAM)nullptr, (LPARAM)nullptr);
			else
			{
				fArg = sArg = tArg = 0;
				MessageBoxA(nullptr, "Incorrect data", "Error", MB_ICONERROR | MB_OK);
			}
			break;
		}
		default:
			return 0;
		}
		if (this->buttonList.size())
			this->buttonList.back()->setVisiability(true);
		UpdateWindow(this->mainWindow);
		return 0;

	default:
		break;
	
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void  App::clearData()
{
	for (auto i = 0u; i < staticList.size(); ++i)
	{
		staticList.at(i)->setText(L"");
		editList.at(i)->setText(L"");
	}
}
void App::changeDatavisible(const bool isShown, const App::InputDataList id)
{
	this->editList.at(static_cast<std::uint32_t>(id))->setVisiability(isShown);
	this->staticList.at(static_cast<std::uint32_t>(id))->setVisiability(isShown);
}

void App::updateAllControl()
{
	for (auto i = 0u; i < staticList.size(); ++i)
	{
		if (staticList.at(i)->isActive())
		{
			staticList.at(i)->setVisiability(true);
			editList.at(i)->setVisiability(true);
		}
	}
	for (auto& el : buttonList)
		el->setVisiability(true);
}

bool App::readArguments()
{
	auto wFirst = editList.at(static_cast<std::uint32_t>(App::InputDataList::FIRST))->getText();
	auto wSecond = editList.at(static_cast<std::uint32_t>(App::InputDataList::SECOND))->getText();
	auto wThird = editList.at(static_cast<std::uint32_t>(App::InputDataList::THIRD))->getText();
	fArg = sArg = tArg = 0;
	bool isCorrectRead = true;

	if (!std::ranges::all_of(wFirst, std::iswdigit) ||
		!std::ranges::all_of(wSecond, std::iswdigit) ||
		!std::ranges::all_of(wThird, std::iswdigit))
		isCorrectRead = false;
	else
	{
		//No zero value
		if (editList.at(static_cast<std::uint32_t>(App::InputDataList::FIRST))->isActive())
		{
			if (wFirst.size())
				fArg = std::stoi(wFirst);
			if (fArg == 0)
				isCorrectRead = false;
		}
		if (editList.at(static_cast<std::uint32_t>(App::InputDataList::SECOND))->isActive())
		{
			if (wSecond.size())
				sArg = std::stoi(wSecond);
			if (sArg == 0)
				isCorrectRead = false;
		}
		if (editList.at(static_cast<std::uint32_t>(App::InputDataList::THIRD))->isActive())
		{
			if (wThird.size())
				tArg = std::stoi(wThird);
			if (tArg == 0)
				isCorrectRead = false;
		}
	}
	return isCorrectRead;
}

void App::switchToSquare()
{
	changeDatavisible(true, App::InputDataList::FIRST);
	changeDatavisible(false, App::InputDataList::SECOND);
	changeDatavisible(false, App::InputDataList::THIRD);

	this->clearData();
	this->staticList.at(static_cast<std::uint32_t>(App::InputDataList::FIRST))->setText(L"Side length (px)");
	drawer->setDrawer(DrawerStorage::Figure::SQUARE);
}

void App::switchToRectangle()
{
	changeDatavisible(true, App::InputDataList::FIRST);
	changeDatavisible(true, App::InputDataList::SECOND);
	changeDatavisible(false, App::InputDataList::THIRD);

	this->clearData();
	this->staticList.at(static_cast<std::uint32_t>(App::InputDataList::FIRST))->setText(L"Rectangle height (px)");
	this->staticList.at(static_cast<std::uint32_t>(App::InputDataList::SECOND))->setText(L"Rectangle width (px)");
	drawer->setDrawer(DrawerStorage::Figure::RECTANGLE);
}

void App::switchToParallelogram()
{
	changeDatavisible(true, App::InputDataList::FIRST);
	changeDatavisible(true, App::InputDataList::SECOND);
	changeDatavisible(true, App::InputDataList::THIRD);

	this->clearData();
	this->staticList.at(static_cast<std::uint32_t>(App::InputDataList::FIRST))->setText(L"'Vertical' length (px)");
	this->staticList.at(static_cast<std::uint32_t>(App::InputDataList::SECOND))->setText(L"Bottom base length (px)");
	this->staticList.at(static_cast<std::uint32_t>(App::InputDataList::THIRD))->setText(L"Corner (°)");
	drawer->setDrawer(DrawerStorage::Figure::PARALLELOGRAM);
}

void App::switchToTrapezia()
{
	changeDatavisible(true, App::InputDataList::FIRST);
	changeDatavisible(true, App::InputDataList::SECOND);
	changeDatavisible(true, App::InputDataList::THIRD);

	this->clearData();
	this->staticList.at(static_cast<std::uint32_t>(App::InputDataList::FIRST))->setText(L"Top base length (px)");
	this->staticList.at(static_cast<std::uint32_t>(App::InputDataList::SECOND))->setText(L"Bottom base length (px)");
	this->staticList.at(static_cast<std::uint32_t>(App::InputDataList::THIRD))->setText(L"Height (px)");
	drawer->setDrawer(DrawerStorage::Figure::TRAPEZIA);
}

void App::switchToRhombus()
{
	changeDatavisible(true, App::InputDataList::FIRST);
	changeDatavisible(true, App::InputDataList::SECOND);
	changeDatavisible(false, App::InputDataList::THIRD);

	this->clearData();
	this->staticList.at(static_cast<std::uint32_t>(App::InputDataList::FIRST))->setText(L"Vertical diagonal (px)");
	this->staticList.at(static_cast<std::uint32_t>(App::InputDataList::SECOND))->setText(L"Horizontal diagonal (px)");
	drawer->setDrawer(DrawerStorage::Figure::RHOMBUS);
}

void App::switchToPolygon()
{
	changeDatavisible(true, App::InputDataList::FIRST);
	changeDatavisible(true, App::InputDataList::SECOND);
	changeDatavisible(false, App::InputDataList::THIRD);

	this->clearData();
	this->staticList.at(static_cast<std::uint32_t>(App::InputDataList::FIRST))->setText(L"Radius (px)");
	this->staticList.at(static_cast<std::uint32_t>(App::InputDataList::SECOND))->setText(L"Number of corners");
	drawer->setDrawer(DrawerStorage::Figure::POLYGON);
}

void App::switchToTriangle()
{
	changeDatavisible(true, App::InputDataList::FIRST);
	changeDatavisible(false, App::InputDataList::SECOND);
	changeDatavisible(false, App::InputDataList::THIRD);

	this->clearData();
	this->staticList.at(static_cast<std::uint32_t>(App::InputDataList::FIRST))->setText(L"Radius of the circumscribed (px)");
	drawer->setDrawer(DrawerStorage::Figure::TRIANGLE);
}

void App::switchToCircle()
{
	changeDatavisible(true, App::InputDataList::FIRST);
	changeDatavisible(false, App::InputDataList::SECOND);
	changeDatavisible(false, App::InputDataList::THIRD);

	this->clearData();
	this->staticList.at(static_cast<std::uint32_t>(App::InputDataList::FIRST))->setText(L"Radius");
	drawer->setDrawer(DrawerStorage::Figure::CIRCLE);
}

void App::switchToOval()
{
	changeDatavisible(true, App::InputDataList::FIRST);
	changeDatavisible(true, App::InputDataList::SECOND);
	changeDatavisible(false, App::InputDataList::THIRD);

	this->clearData();
	this->staticList.at(static_cast<std::uint32_t>(App::InputDataList::FIRST))->setText(L"Horizontal radius");
	this->staticList.at(static_cast<std::uint32_t>(App::InputDataList::SECOND))->setText(L"Vertical radius");

	drawer->setDrawer(DrawerStorage::Figure::OVAL);
}
