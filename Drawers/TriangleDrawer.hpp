#ifndef TriangleDrawer_H
#define TriangleDrawer_H

#include "PolygonDrawer.hpp"
/**
\brief Triangle painter
*/
class TriangleDrawer final: public PolygonDrawer
{
protected:
	/**
	\brief implementation of the method responsible for drawing
	\param pRT pointer to drawing interface
	\param first Radius (distance from center to corner)
	\param second unused
	\param third unused
	*/
	virtual void draw(ID2D1HwndRenderTarget* pRT, const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) override
	{
		PolygonDrawer::draw(pRT, first, 3,0);
	}
public:
	TriangleDrawer() = delete;
	TriangleDrawer(const TriangleDrawer&) = delete;
	TriangleDrawer(TriangleDrawer&&) = delete;
	/**
	\brief Constructor
	\param old Previous Drawer
	*/
	TriangleDrawer(Drawer&& old)
		:PolygonDrawer(std::move(old))
	{

	}
	virtual ~TriangleDrawer() = default;
};

#endif
