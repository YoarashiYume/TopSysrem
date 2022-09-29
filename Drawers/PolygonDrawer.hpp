#ifndef PolygonDrawer_H
#define PolygonDrawer_H

#include "Drawer.h"

#include <cmath>
/**
\brief Polygon painter
*/
class PolygonDrawer : public Drawer
{
protected:
	/**
	\brief implementation of the method responsible for drawing
	\param pRT pointer to drawing interface
	\param first Radius (distance from center to corner)
	\param second Number of corners
	\param third unused
	*/
	virtual void draw(ID2D1HwndRenderTarget* pRT, const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) override
	{
		constexpr double PI = 3.14159265358979323846;
		auto xCenter = pixelToDPIX(static_cast<float>(this->windowWidth) / 2) + xOffset / 2;
		auto yCenter = pixelToDPIY(static_cast<float>(windowHeight) / 2);
		if (second > 360 || second < 3)
		{
			MessageBoxA(nullptr, "Incorrect count of corner data", "Error", MB_ICONERROR | MB_OK);
			return;
		}
		float tetta = static_cast<float>((360.f / second) * PI / 180.f);
		
		float x = xCenter;
		float y = yCenter - first;

		//build Polygon
		for (auto i = 0u; i < second; ++i)
		{
			//newX = angle * sin(alpha)
			//newY = angle * cos(alpha)
			float newX = xCenter - first * std::sin((i + 1) * tetta);
			float newY = yCenter - first * std::cos((i + 1) * tetta);
			pRT->DrawLine({ x,y }, { newX,newY }, brush, 2);
			x = newX;
			y = newY;
		}

	}
public:
	PolygonDrawer() = delete;
	PolygonDrawer(const PolygonDrawer&) = delete;
	PolygonDrawer(PolygonDrawer&&) = delete;
	/**
	\brief Constructor
	\param old Previous Drawer
	*/
	PolygonDrawer(Drawer&& old)
		:Drawer(std::move(old))
	{

	}
	virtual ~PolygonDrawer() = default;
};

#endif
