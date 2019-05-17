#ifndef INPUT_H
#define INPUT_H


#include <SDL.h>

class InputManager
{
public:
	explicit InputManager();

	bool GetButton(SDL_Keycode key);

	float GetMouseWheelDelta();

private:
	float mouseWheelDelta = 0;
};
#endif