#ifndef ZeroDrawer_H
#define ZeroDrawer_H

#include "Drawer.h"
/**
\brief ZeroDrawer
used for initialization and does not draw anything
*/
class ZeroDrawer final : public Drawer
{
protected:
	/**
	\brief implementation of the method responsible for drawing
	\param pRT pointer to drawing interface - unused
	\param first unused
	\param second unused
	\param third unused
	*/
	virtual void draw(ID2D1HwndRenderTarget* pRT, const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) override
	{

	}
public:
	ZeroDrawer() = delete;
	ZeroDrawer(const ZeroDrawer&) = delete;
	ZeroDrawer(ZeroDrawer&&) = default;
	/**
	\brief Constructor
	\param xDPI,yDPI  current dpi
	\param offsetX offset from control elements
	\param windowWidth,windowHeight window dimensions
	\param pRT pointer to drawing interface
	*/
	ZeroDrawer(const float xDPI, const float yDPI, const std::uint32_t offsetX, const std::uint32_t windowWidth, const std::uint32_t windowHeight, ID2D1HwndRenderTarget* pRT)
		:Drawer(xDPI,yDPI, offsetX,windowWidth,  windowHeight, pRT)
	{

	}
};

#endif
