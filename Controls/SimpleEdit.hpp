#ifndef SimpleEdit_H
#define SimpleEdit_H

#include "Control.h"


class SimpleEdit final :  public Control
{
public:
	SimpleEdit() = delete;
	SimpleEdit(const SimpleEdit&) = delete;
	SimpleEdit(SimpleEdit&&) = delete;

	SimpleEdit(const HWND& parent, const std::wstring_view editText, const std::uint16_t xPos, const std::uint16_t yPos, const std::uint16_t width, const std::uint16_t height)
		: Control(parent, L"EDIT", editText, WS_EX_CLIENTEDGE, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
			xPos, yPos, width, height, UINT32_MAX)
	{}

	std::wstring getText() const
	{
		std::wstring text{};
		text.resize(MAX_PATH);
		GetWindowText(this->Control::window, &text[0], MAX_PATH);
		text.erase(remove(text.begin(), text.end(), 0), text.end());
		return text;
	}
	bool setText(const std::wstring_view text) const
	{
		return SetWindowText(this->window, text.data());
	}

	~SimpleEdit() = default;
};
#endif
