#include "menu.hpp"
#include "settings.hpp"
#include "textarea.hpp"
#include "control.hpp"
#include "graphics.hpp"

Menu::Menu(ControlState *parent) : ControlState(parent), newState(0) {}

void Menu::start()
{
	Graphics::changeBackgroundColor(0.f, 0.f, 0.f);
	if (newState != 0)
	{
		delete newState;
		settings.save();
	}
	if (settings.host.length() == 0)
	{
		newState = new TextArea(this, settings.host, "Enter host name", 17*24);
		Control::changeState(newState);
	}
}