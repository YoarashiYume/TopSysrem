#ifndef CircleDrawer_H
#define CircleDrawer_H

#include "EllipseDrawer.hpp"

/**
\brief Circle painter
*/
class CircleDrawer final: public EllipseDrawer
{
protected:
	/**
	\brief implementation of the method responsible for drawing
	\param pRT pointer to drawing interface
	\param first Radius
	\param second unused
	\param third unused
	*/
	virtual void draw(ID2D1HwndRenderTarget* pRT, const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) override
	{
		EllipseDrawer::draw(pRT, first, first, 0);
	}
public:
	CircleDrawer() = delete;
	CircleDrawer(const CircleDrawer&) = delete;
	CircleDrawer(CircleDrawer&&) = delete;
	/**
	\brief Constructor
	\param old Previous Drawer
	*/
	CircleDrawer(Drawer&& old)
		:EllipseDrawer(std::move(old))
	{

	}
};

#endif
