#include "Drawer.h"

Drawer::Drawer(const float xDPI, const float yDPI, const std::uint32_t offsetX, const std::uint32_t windowWidth, const std::uint32_t windowHeight, ID2D1HwndRenderTarget* pRT)
	:dpiX(xDPI), dpiY(yDPI), xOffset(pixelToDPIX(static_cast<float>(offsetX))), 
	windowWidth(windowWidth), windowHeight(windowHeight)
{
	//Creates brush
	pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &this->brush);
}

float Drawer::pixelToDPIX(const float x) const
{
	return x * 96 / dpiX;
}

float Drawer::pixelToDPIY(const float y) const
{
	return y * 96 / dpiY;
}

Drawer::Drawer(Drawer&& other)
{
	if (this != &other)
	{
		this->dpiX = other.dpiX;
		this->dpiY = other.dpiY;
		this->xOffset = other.xOffset;
		this->windowWidth = other.windowWidth;
		this->windowHeight = other.windowHeight;
		if (this->brush)
			this->brush->Release();
		this->brush = other.brush;
		other.brush = nullptr;
	}
}

Drawer::~Drawer()
{
	if (brush)
		brush->Release();
}

void Drawer::drawFigure(HWND hwnd, ID2D1HwndRenderTarget* pRT,const std::uint32_t first, const std::uint32_t second, const std::uint32_t third)
{
	PAINTSTRUCT pt;
	BeginPaint(hwnd, &pt);
	//clears field and draws
	pRT->BeginDraw();
	pRT->Clear(D2D1::ColorF(D2D1::ColorF::White));
	this->draw(pRT,first, second, third);
	pRT->EndDraw();
	EndPaint(hwnd, &pt);
}