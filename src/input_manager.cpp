#include <iostream>

#include "input_manager.h"

namespace leng {
    
void InputManager::pressKey(unsigned int keyID) {
	keyState[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID) {
	keyState[keyID] = false;
}

void InputManager::update() {
    // Loop through _keyMap using a for each loop(C+11), and copy it over to _previousKeyMap.
    for (auto& it : keyState)
	{
	    prevKeyState[it.first] = it.second;
	}
}

bool InputManager::isKeyDown(unsigned int keyID) {
    auto it = keyState.find(keyID);
    if (it != keyState.end()) {
	return it->second;
    }
    else {
	return false;
    }
}

bool InputManager::isKeyPressed(unsigned int keyID) {
    // Check if it is pressed this frame, and wasn't pressed last frame
    if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
	return true;
    }
    return false;
}

bool InputManager::wasKeyDown(unsigned int keyID) {
    auto it = prevKeyState.find(keyID);
    if (it != prevKeyState.end()) {
	return it->second;
    }
    else {
	return false;
    }
}

void InputManager::setMouseCoords(float x, float y) {
    mouseCoords.x = x;
    mouseCoords.y = y;
}

} // namespace leng
