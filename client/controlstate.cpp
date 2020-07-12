#include "controlstate.hpp"
#include "control.hpp"

void ControlState::quit()
{
	Control::changeState(parent);
}