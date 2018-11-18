#include "InputClass.h"


InputClass::InputClass() {
}


InputClass::InputClass(const InputClass& other) {
}


InputClass::~InputClass() {
}


void InputClass::Initialize() {
	int i;

	// Initialize all the keys to being released and not pressed.
	for (i = 0; i < 256; i++)
	{
		mCurrentKey[i] = false;
		mLaskKey[i] = false;
	}

	return;
}


void InputClass::KeyDown(unsigned int input) {
	// If a key is pressed then save that state in the key array.
	mCurrentKey[input] = true;
	return;
}


void InputClass::KeyUp(unsigned int input) {
	// If a key is released then clear that state in the key array.
	mCurrentKey[input] = false;
	return;
}


bool InputClass::IsKeyDown(unsigned int key) {
	// Return what state the key is in (pressed/not pressed).
	return mCurrentKey[key];
}

KEY_STATE InputClass::GetKeyState(unsigned int key) {
	if (!mCurrentKey[key] && !mLaskKey[key]) {
		return KEY_STATE::NORMAL;
	} else if (mCurrentKey[key] && !mLaskKey[key]) {
		return KEY_STATE::DOWN;
	} else if (mCurrentKey[key] && mLaskKey[key]) {
		return KEY_STATE::PRESS;
	} else if (!mCurrentKey[key] && mLaskKey[key]) {
		return KEY_STATE::UP;
	} else {
		return KEY_STATE::NORMAL;
	}
}