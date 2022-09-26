#ifndef EllipseDrawer_H
#define EllipseDrawer_H

#include "Drawer.h"

class EllipseDrawer : public Drawer
{
protected:
	virtual void draw(ID2D1HwndRenderTarget* pRT, const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) override
	{
		D2D1_ELLIPSE elipse{ {}, pixelToDPIX(static_cast<float>(first)),
			pixelToDPIY(static_cast<float>(second)) };
		elipse.point = D2D1_POINT_2F{ pixelToDPIX(static_cast<float>(this->windowWidth)/2)+ xOffset / 2
		,pixelToDPIY(static_cast<float>(windowHeight) / 2) };
		
		pRT->DrawEllipse(elipse, brush,2);
	}
public:
	EllipseDrawer() = delete;
	EllipseDrawer(const EllipseDrawer&) = delete;
	EllipseDrawer(EllipseDrawer&&) = delete;
	EllipseDrawer(Drawer&& old)
		:Drawer(std::move(old))
	{

	}
	virtual ~EllipseDrawer() = default;
};

#endif
