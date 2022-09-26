#ifndef SimpleStatic_H
#define SimpleStatic_H

#include "Control.h"
#include <numeric>

class SimpleStatic final : public Control
{
public:
	SimpleStatic() = delete;
	SimpleStatic(const SimpleStatic&) = delete;
	SimpleStatic(SimpleStatic&&) = delete;

	SimpleStatic(const HWND& parent, const std::wstring_view labelText, const std::uint16_t xPos, const std::uint16_t yPos, const std::uint16_t width, const std::uint16_t height)
		: Control(parent, L"Static", labelText, 0, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
			xPos, yPos, width, height, UINT32_MAX)
	{}
	bool setText(const std::wstring_view text) const
	{
		return SetWindowText(this->window, text.data());
	}

	virtual ~SimpleStatic() = default;
};
#endif
