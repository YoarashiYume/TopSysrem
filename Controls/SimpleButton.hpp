#ifndef SimpleButton_H
#define SimpleButton_H

#include "Control.h"

class SimpleButton final : public Control
{
public:
	SimpleButton() = delete;
	SimpleButton(const SimpleButton&) = delete;
	SimpleButton(SimpleButton&&) = delete;

	SimpleButton(const HWND& parent, const std::uint32_t commandId, const std::wstring_view buttonText, const std::uint16_t xPos, const std::uint16_t yPos, const std::uint16_t width, const std::uint16_t height)
		: Control(parent, L"BUTTON", buttonText, 0, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			xPos, yPos, width, height, commandId)
	{}


	~SimpleButton() = default;
};
#endif
