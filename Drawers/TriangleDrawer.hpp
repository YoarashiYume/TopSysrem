#ifndef TriangleDrawer_H
#define TriangleDrawer_H

#include "PolygonDrawer.hpp"

class TriangleDrawer final: public PolygonDrawer
{
protected:
	virtual void draw(ID2D1HwndRenderTarget* pRT, const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) override
	{
		PolygonDrawer::draw(pRT, first, 3,0);
	}
public:
	TriangleDrawer() = delete;
	TriangleDrawer(const TriangleDrawer&) = delete;
	TriangleDrawer(TriangleDrawer&&) = delete;
	TriangleDrawer(Drawer&& old)
		:PolygonDrawer(std::move(old))
	{

	}
	virtual ~TriangleDrawer() = default;
};

#endif
