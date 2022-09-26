#ifndef ZeroDrawer_H
#define ZeroDrawer_H

#include "Drawer.h"

class ZeroDrawer final : public Drawer
{
protected:
	virtual void draw(ID2D1HwndRenderTarget* pRT, const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) override
	{

	}
public:
	ZeroDrawer() = delete;
	ZeroDrawer(const ZeroDrawer&) = delete;
	ZeroDrawer(ZeroDrawer&&) = default;

	ZeroDrawer(const float xDPI, const float yDPI, const std::uint32_t offsetX, const std::uint32_t windowWidth, const std::uint32_t windowHeight, ID2D1HwndRenderTarget* pRT)
		:Drawer(xDPI,yDPI, offsetX,windowWidth,  windowHeight, pRT)
	{

	}
};

#endif
