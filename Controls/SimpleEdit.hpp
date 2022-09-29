#ifndef SimpleEdit_H
#define SimpleEdit_H

#include "Control.h"

/**
\brief Class of simple textbox element
*/

class SimpleEdit final :  public Control
{
public:
	SimpleEdit() = delete;
	SimpleEdit(const SimpleEdit&) = delete;
	SimpleEdit(SimpleEdit&&) = delete;

	/**
	\brief Constructor
	\param parent descripoor of the parent element
	\param editText window name/text on control
	\param xPos,yPos upper left corner position
	\param width, height - element dimensions
	*/
	SimpleEdit(const HWND& parent, const std::wstring_view editText, const std::uint16_t xPos, const std::uint16_t yPos, const std::uint16_t width, const std::uint16_t height)
		: Control(parent, L"EDIT", editText, WS_EX_CLIENTEDGE, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
			xPos, yPos, width, height, UINT32_MAX)
	{}
	/**
	\brief Method returns text data from the textbox
	\return Text from a textbox
	*/
	std::wstring getText() const
	{
		std::wstring text{};
		text.resize(MAX_PATH);
		GetWindowText(this->Control::window, &text[0], MAX_PATH);
		text.erase(remove(text.begin(), text.end(), 0), text.end());
		return text;
	}
	/**
	\brief Method set text data in the textbox
	\param New text for the element
	*/
	bool setText(const std::wstring_view text) const
	{
		return SetWindowText(this->window, text.data());
	}

	~SimpleEdit() = default;
};
#endif
