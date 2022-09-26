#ifndef DrawerStorage_H
#define DrawerStorage_H

#include "Drawers/ZeroDrawer.hpp"
#include "Drawers/CircleDrawer.hpp"
#include "Drawers/SquareDrawer.hpp"
#include "Drawers/TrapeziaDrawer.hpp"
#include "Drawers/TriangleDrawer.hpp"
#include "Drawers/RhombusDrawer.hpp"
#include "Drawers/ParallelogramDrawer.hpp"

#include <memory>

class DrawerStorage final
{
public:
	using value_type = std::unique_ptr<Drawer>;
	enum class Figure : std::uint32_t
	{
		SQUARE = 0,
		RECTANGLE,
		PARALLELOGRAM,
		TRAPEZIA,
		RHOMBUS,
		POLYGON,
		TRIANGLE,
		CIRCLE,
		OVAL
	};
private:
	value_type drawer;
public:
	DrawerStorage() = delete;
	DrawerStorage(const float xDPI, const float yDPI, const std::uint32_t offsetX, const std::uint32_t windowWidth, const std::uint32_t windowHeight, ID2D1HwndRenderTarget* pRT);
	DrawerStorage(const  DrawerStorage&) = delete;
	DrawerStorage(DrawerStorage&&) = delete;

	void setDrawer(const Figure);
	void draw(HWND hwnd, ID2D1HwndRenderTarget* pRT, const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) const;
};

#endif