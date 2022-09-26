#ifndef RectangleDrawer_H
#define RectangleDrawer_H

#include "TrapeziaDrawer.hpp"

class RectangleDrawer : public TrapeziaDrawer
{
protected:
	virtual void draw(ID2D1HwndRenderTarget* pRT, const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) override
	{
		TrapeziaDrawer::draw(pRT, second, second, first);
	}
public:
	RectangleDrawer() = delete;
	RectangleDrawer(const RectangleDrawer&) = delete;
	RectangleDrawer(RectangleDrawer&&) = delete;
	RectangleDrawer(Drawer&& old)
		:TrapeziaDrawer(std::move(old))
	{

	}
	virtual ~RectangleDrawer() = default;
};

#endif
