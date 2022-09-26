#include "DrawerStorage.h"

DrawerStorage::DrawerStorage(const float xDPI, const float yDPI, const std::uint32_t offsetX,
	const std::uint32_t windowWidth, const std::uint32_t windowHeight, ID2D1HwndRenderTarget* pRT)
{
	drawer.reset(new ZeroDrawer{ xDPI ,yDPI, offsetX, windowWidth,windowHeight, pRT });
}

void DrawerStorage::setDrawer(const Figure figure)
{
	Drawer* oldData = drawer.release();
	switch (figure)
	{
	case DrawerStorage::Figure::SQUARE:
		drawer.reset(new SquareDrawer{ std::move(*oldData) });
		break;
	case DrawerStorage::Figure::RECTANGLE:
		drawer.reset(new RectangleDrawer{ std::move(*oldData) });
		break;
	case DrawerStorage::Figure::PARALLELOGRAM:
		drawer.reset(new ParallelogramDrawer{ std::move(*oldData) });
		break;
	case DrawerStorage::Figure::TRAPEZIA:
		drawer.reset(new TrapeziaDrawer{ std::move(*oldData) });
		break;
	case DrawerStorage::Figure::RHOMBUS:
		drawer.reset(new RhombusDrawer{ std::move(*oldData) });
		break;
	case DrawerStorage::Figure::POLYGON:
		drawer.reset(new PolygonDrawer{ std::move(*oldData) });
		break;
	case DrawerStorage::Figure::TRIANGLE:
		drawer.reset(new TriangleDrawer{ std::move(*oldData) });
		break;
	case DrawerStorage::Figure::CIRCLE:
		drawer.reset(new CircleDrawer{ std::move(*oldData) });
		break;
	case DrawerStorage::Figure::OVAL:
		drawer.reset(new EllipseDrawer{ std::move(*oldData) });
		break;
	default:
		drawer.reset(oldData);
		return;
	}
	delete oldData;
}

void DrawerStorage::draw(HWND hwnd, ID2D1HwndRenderTarget* pRT, const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) const
{
	drawer->drawFigure(hwnd, pRT, first, second, third);
}
