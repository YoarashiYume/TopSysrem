#ifndef Drawer_H
#define Drawer_H

#include <d2d1.h>
#include <utility> //std::move

/**
\brief Base abstract class for drawers
*/
class Drawer
{
private:
	float dpiX, ///< current dpi for X axes
		dpiY;///< current dpi for Y axes
protected:
	/**
	\brief Method convert pixels to dpi
	\return return new X position
	*/
	float pixelToDPIX(const float x) const;
	/**
	\brief Method convert pixels to dpi
	\return return new Y position
	*/
	float pixelToDPIY(const float y) const;

	std::uint32_t xOffset,///< offset from control elements
		windowWidth, ///< current window width
		windowHeight; ///< current window height
	ID2D1SolidColorBrush* brush; ///< Black brush

	
	/**
	\brief abstract method responsible for drawing
	\param pRT pointer to drawing interface
	\param first first possible argument
	\param second second possible argument
	\param third third possible argument
	*/
	virtual void draw(ID2D1HwndRenderTarget* pRT,const std::uint32_t first, const std::uint32_t second, const std::uint32_t third) = 0;
public:
	Drawer() = delete;
	/**
	\brief Constructor
	\param xDPI,yDPI  current dpi
	\param offsetX offset from control elements
	\param windowWidth,windowHeight window dimensions
	\param pRT pointer to drawing interface
	*/
	Drawer(const float xDPI, const float yDPI, const std::uint32_t offsetX, const std::uint32_t windowWidth, const std::uint32_t windowHeight, ID2D1HwndRenderTarget* pRT);
	Drawer(const  Drawer&) = delete;
	Drawer(Drawer&&);
	virtual ~Drawer();
	/**
	\briefabstract method responsible for drawing
	\param hwnd handle to the element to draw
	\param pRT pointer to drawing interface
	\param first first possible argument
	\param second second possible argument
	\param third third possible argument
	*/
	void drawFigure(HWND hwnd, ID2D1HwndRenderTarget* pRT,const std::uint32_t first, const std::uint32_t second, const std::uint32_t third);
};

#endif
