#ifndef CircleDrawer_H
#define CircleDrawer_H

#include "EllipseDrawer.hpp"

class CircleDrawer final: public EllipseDrawer
{
protected:
	virtual void draw(ID2D1HwndRenderTarget* pRT, const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) override
	{
		EllipseDrawer::draw(pRT, first, first, 0);
	}
public:
	CircleDrawer() = delete;
	CircleDrawer(const CircleDrawer&) = delete;
	CircleDrawer(CircleDrawer&&) = delete;
	CircleDrawer(Drawer&& old)
		:EllipseDrawer(std::move(old))
	{

	}
};

#endif
