#include "Control.h"

Control::Control(const HWND& parent, const std::wstring_view className, const std::wstring_view windowName, const DWORD simpleStyle, const DWORD winStyle, const std::uint16_t xPos, const std::uint16_t yPos,
	const std::uint16_t width, const std::uint16_t height, const std::uint32_t commandId, const HINSTANCE hInstance, const LPVOID lpParam)
{
	this->window = CreateWindowEx(
		simpleStyle,
		className.data(),
		windowName.data(),
		winStyle,
		xPos, yPos, width, height,
		parent, reinterpret_cast<HMENU>(commandId), hInstance, lpParam
	);
}

bool Control::isInit() const
{
	return this->window;
}

void Control::changeVisiability()
{
	this->isShown = isShown == SW_HIDE ? SW_SHOW : SW_HIDE;
	ShowWindow(this->window, this->isShown);
}
void Control::setVisiability(const bool isShown)
{
	if (isShown)
		this->isShown = SW_SHOW;
	else
		this->isShown = SW_HIDE;
	ShowWindow(this->window, this->isShown);
}

bool Control::isActive() const
{
	return isShown == SW_SHOW;
}

const Control::value_type& Control::get() const
{
	return window;
}

Control::~Control()
{
	DestroyWindow(this->window);
}