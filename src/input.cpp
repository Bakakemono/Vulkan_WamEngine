#include <input..h>


InputManager::InputManager() {}

bool InputManager::GetButton(SDL_Keycode key)
{
	SDL_Scancode scanCode = SDL_GetScancodeFromKey(key);
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	return keyState[scanCode];
}

float InputManager::GetMouseWheelDelta()
{
	SDL_Event e;

	SDL_PollEvent(&e);
	mouseWheelDelta = e.wheel.x;

	return mouseWheelDelta;
}
