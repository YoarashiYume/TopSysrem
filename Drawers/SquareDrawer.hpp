#ifndef SquareDrawer_H
#define SquareDrawer_H

#include "RectangleDrawer.hpp"

class SquareDrawer final: public RectangleDrawer
{
protected:
	virtual void draw(ID2D1HwndRenderTarget* pRT, const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) override
	{
		RectangleDrawer::draw(pRT, first, first, 0);
	}
public:
	SquareDrawer() = delete;
	SquareDrawer(const SquareDrawer&) = delete;
	SquareDrawer(RectangleDrawer&&) = delete;
	SquareDrawer(Drawer&& old)
		:RectangleDrawer(std::move(old))
	{

	}
	virtual ~SquareDrawer() = default;
};

#endif
