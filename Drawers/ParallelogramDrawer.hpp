#ifndef ParallelogramDrawerr_H
#define ParallelogramDrawer_H

#include "Drawer.h"

#include <cmath>

/**
\brief Parallelogram painter
*/
class ParallelogramDrawer : public Drawer
{

protected:
	/**
	\brief implementation of the method for drawing
	\param pRT pointer to drawing interface
	\param first 'Vertical' length
	\param second Bottom base length
	\param third Corner
	*/
	virtual void draw(ID2D1HwndRenderTarget* pRT, const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) override
	{
		constexpr double PI = 3.14159265358979323846;
		auto xCenter = pixelToDPIX(static_cast<float>(this->windowWidth) / 2) + xOffset / 2;
		auto yCenter = pixelToDPIY(static_cast<float>(windowHeight) / 2);
		if (third > 90)
		{
			MessageBoxA(nullptr, "Incorrect corner data", "Error", MB_ICONERROR | MB_OK);
			return;
		}
		auto h = pixelToDPIY(static_cast<float>(first * std::sin(third * PI /180.f )));
		auto offset = pixelToDPIX(static_cast<float>(std::sqrt(std::pow(first, 2) - std::pow(h, 2))));
		auto bottomCenter = pixelToDPIX(static_cast<float>(second / 2));
		auto heightCenter = pixelToDPIY(static_cast<float>(h / 2));
		//build Parallelogra
		pRT->DrawLine({ xCenter - bottomCenter,yCenter + heightCenter }, { xCenter - bottomCenter + offset,yCenter - heightCenter }, brush, 2);
		pRT->DrawLine({ xCenter - bottomCenter + offset,yCenter - heightCenter }, { xCenter + bottomCenter + offset,yCenter - heightCenter }, brush, 2);
		pRT->DrawLine({ xCenter + bottomCenter + offset,yCenter - heightCenter }, { xCenter + bottomCenter ,yCenter + heightCenter }, brush, 2);
		pRT->DrawLine({ xCenter + bottomCenter ,yCenter + heightCenter }, { xCenter - bottomCenter,yCenter + heightCenter }, brush, 2);
	

	}
public:
	ParallelogramDrawer() = delete;
	ParallelogramDrawer(const ParallelogramDrawer&) = delete;
	ParallelogramDrawer(ParallelogramDrawer&&) = delete;
	ParallelogramDrawer(Drawer&& old)
	/**
	\brief Constructor
	\param old Previous Drawer
	*/
		:Drawer(std::move(old))
	{

	}
	virtual ~ParallelogramDrawer() = default;
};

#endif
