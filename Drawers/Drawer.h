#ifndef Drawer_H
#define Drawer_H

#include <d2d1.h>
#include <cstdint>
#include <utility> //std::move

class Drawer
{
private:
	float dpiX, dpiY;
protected:
	float pixelToDPIX(const float x) const;
	float pixelToDPIY(const float y) const;

	std::uint32_t xOffset,
		windowWidth, windowHeight;
	ID2D1SolidColorBrush* brush;

	virtual void draw(ID2D1HwndRenderTarget* pRT,const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) = 0;
public:
	Drawer() = delete;
	Drawer(const float xDPI, const float yDPI, const std::uint32_t offsetX, const std::uint32_t windowWidth, const std::uint32_t windowHeight, ID2D1HwndRenderTarget* pRT);
	Drawer(const  Drawer&) = delete;
	Drawer(Drawer&&);
	virtual ~Drawer();

	void drawFigure(HWND hwnd, ID2D1HwndRenderTarget* pRT,const std::uint32_t first, const std::uint32_t second, const std::uint32_t third);
};

#endif