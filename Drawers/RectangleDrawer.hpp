#ifndef RectangleDrawer_H
#define RectangleDrawer_H

#include "TrapeziaDrawer.hpp"
/**
\brief Rectangle painter
*/
class RectangleDrawer : public TrapeziaDrawer
{
protected:
	/**
	\brief implementation of the method responsible for drawing
	\param pRT pointer to drawing interface
	\param first Rectangle height
	\param second Rectangle width
	\param third unused
	*/
	virtual void draw(ID2D1HwndRenderTarget* pRT, const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) override
	{
		TrapeziaDrawer::draw(pRT, second, second, first);
	}
public:
	RectangleDrawer() = delete;
	RectangleDrawer(const RectangleDrawer&) = delete;
	RectangleDrawer(RectangleDrawer&&) = delete;
	/**
	\brief Constructor
	\param old Previous Drawer
	*/
	RectangleDrawer(Drawer&& old)
		:TrapeziaDrawer(std::move(old))
	{

	}
	virtual ~RectangleDrawer() = default;
};

#endif
