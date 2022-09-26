#ifndef Control_H
#define Control_H

#include <Windows.h>
#include <string>

//Base control window

class Control
{
public:
	using value_type = HWND;
private:
	uint8_t isShown = SW_SHOW;
protected:
	value_type window;
public:
	Control() = delete;
	Control(const Control&) = delete;
	Control(Control&&) = delete;

	Control(const HWND& parent, const std::wstring_view className, const std::wstring_view windowName, const DWORD simpleStyle, const DWORD winStyle,
		const std::uint16_t xPos, const std::uint16_t yPos, const std::uint16_t width, const std::uint16_t height,
		const std::uint32_t commandId ,const HINSTANCE hInstance = nullptr, const LPVOID lpParam = nullptr);

	virtual bool isInit() const final;

	virtual void changeVisiability() final;
	virtual void setVisiability(const bool isShown) final;

	bool isActive() const;

	const value_type& get() const;

	virtual ~Control();
};
#endif
