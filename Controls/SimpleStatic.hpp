#ifndef SimpleStatic_H
#define SimpleStatic_H

#include "Control.h"

/**
\brief Class of simple label element
*/

class SimpleStatic final : public Control
{
public:
	SimpleStatic() = delete;
	SimpleStatic(const SimpleStatic&) = delete;
	SimpleStatic(SimpleStatic&&) = delete;
	/**
	\brief Constructor
	\param parent descripoor of the parent element
	\param labelText window name/text on control
	\param xPos,yPos upper left corner position
	\param width, height - element dimensions
	*/
	SimpleStatic(const HWND& parent, const std::wstring_view labelText, const std::uint16_t xPos, const std::uint16_t yPos, const std::uint16_t width, const std::uint16_t height)
		: Control(parent, L"Static", labelText, 0, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
			xPos, yPos, width, height, UINT32_MAX)
	{}
	/**
	\brief Method set text data in the textbox
	\param New text for the element
	*/
	bool setText(const std::wstring_view text) const
	{
		return SetWindowText(this->window, text.data());
	}

	virtual ~SimpleStatic() = default;
};
#endif
