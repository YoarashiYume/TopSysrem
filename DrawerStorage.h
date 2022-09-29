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
/**
\brief drawers storage
*/
class DrawerStorage final
{
public:
	using value_type = std::unique_ptr<Drawer>;
	/**
	\brief list of driwers type
	*/
	enum class Figure : std::uint32_t
	{
		SQUARE = 0,///< SquareDrawer
		RECTANGLE,///< RectangleDrawer
		PARALLELOGRAM,///< ParallelogramDrawer
		TRAPEZIA,///< TrapeziaDrawer
		RHOMBUS,///< RhombusDrawer
		POLYGON,///< PolygonDrawer
		TRIANGLE,///< TriangleDrawer
		CIRCLE,///< CircleDrawer
		OVAL///< EllipseDrawer
	};
private:
	value_type drawer; ///< current driver
public:
	DrawerStorage() = delete;
	/**
	\brief Constructor
	\param xDPI,yDPI  current dpi
	\param offsetX offset from control elements
	\param windowWidth,windowHeight window dimensions
	\param pRT pointer to drawing interface
	*/
	DrawerStorage(const float xDPI, const float yDPI, const std::uint32_t offsetX, const std::uint32_t windowWidth, const std::uint32_t windowHeight, ID2D1HwndRenderTarget* pRT);
	DrawerStorage(const  DrawerStorage&) = delete;
	DrawerStorage(DrawerStorage&&) = delete;
	/**
	\brief Method changes the current driver
	\param Figure required driwer 'id'
	*/
	void setDrawer(const Figure);
	/**
	\brief Method calls Driwer::draw
	\param pRT pointer to drawing interface
	\param first first possible argument
	\param second second possible argument
	\param third third possible argument
	*/
	void draw(HWND hwnd, ID2D1HwndRenderTarget* pRT, const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) const;
};

#endif