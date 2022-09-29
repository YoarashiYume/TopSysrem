#ifndef SquareDrawer_H
#define SquareDrawer_H

#include "RectangleDrawer.hpp"
/**
\brief Square painter
*/
class SquareDrawer final: public RectangleDrawer
{
protected:
	/**
	\brief implementation of the method responsible for drawing
	\param pRT pointer to drawing interface
	\param first Side length
	\param second unused
	\param third unused
	*/
	virtual void draw(ID2D1HwndRenderTarget* pRT, const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) override
	{
		RectangleDrawer::draw(pRT, first, first, 0);
	}
public:
	SquareDrawer() = delete;
	SquareDrawer(const SquareDrawer&) = delete;
	SquareDrawer(RectangleDrawer&&) = delete;
	/**
	\brief Constructor
	\param old Previous Drawer
	*/
	SquareDrawer(Drawer&& old)
		:RectangleDrawer(std::move(old))
	{

	}
	virtual ~SquareDrawer() = default;
};

#endif
