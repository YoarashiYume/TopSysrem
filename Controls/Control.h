#ifndef Control_H
#define Control_H

#include <Windows.h>
#include <string>

/**
\brief creates and holds control descripor
*/

class Control
{
public:
	using value_type = HWND;
private:
	uint8_t isShown = SW_SHOW; ///< elements current visibility
protected:
	value_type window;
public:
	Control() = delete;
	Control(const Control&) = delete;
	Control(Control&&) = delete;
	/**
	\brief Constructor
	\param parent descripoor of the parent element
	\param className registred class name (BUTTON, STATIC, ect.)
	\param windowName window name/text on control
	\param simpleStyle,winStyle element styles
	\param xPos,yPos upper left corner position
	\param width, height - element dimensions
	\param commandId - menu handle or child window ID
	\param hInstance - application instance handle
	\param lpParam - pointer to window creation data
	*/
	Control(const HWND& parent, const std::wstring_view className, const std::wstring_view windowName, const DWORD simpleStyle, const DWORD winStyle,
		const std::uint16_t xPos, const std::uint16_t yPos, const std::uint16_t width, const std::uint16_t height,
		const std::uint32_t commandId ,const HINSTANCE hInstance = nullptr, const LPVOID lpParam = nullptr);
	/**
	\brief Method checks if the element was created successfully
	\return true if was created successfully, otherwise false
	*/
	virtual bool isInit() const final;
	/**
	\brief Method switches the display mode to the opposite of the current one
	*/
	virtual void changeVisiability() final;
	/**
	\brief Method sets display mode
	\param isShown true if element should display, otherwise false
	*/
	virtual void setVisiability(const bool isShown) final;
	/**
	\brief Method return current visibility state
	\return 'isShown' value
	*/
	bool isActive() const;
	/**
	\brief Method return current descriptor
	\return 'window' value
	*/
	const value_type& get() const;

	virtual ~Control();
};
#endif
