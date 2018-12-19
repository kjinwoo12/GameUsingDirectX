#include "InputClass.h"


InputClass::InputClass() {
}


InputClass::InputClass(const InputClass& other) {
}


InputClass::~InputClass() {
}


void InputClass::initialize() {
	int i;

	// Initialize all the keys to being released and not pressed.
	for (i = 0; i < 256; i++)
	{
		m_currentKey[i] = false;
		m_lastKey[i] = false;
	}

	return;
}


void InputClass::keyDown(unsigned int input) {
	// If a key is pressed then save that state in the key array.
	m_currentKey[input] = true;
	return;
}


void InputClass::keyUp(unsigned int input) {
	// If a key is released then clear that state in the key array.
	m_currentKey[input] = false;
	return;
}


bool InputClass::updateKeyState() {
	try {
		for (int i = 0; i < 256; i++) {
			m_lastKey[i] = m_currentKey[i];
			m_currentKey[i] = false;
		}
	} catch(...) {
		return false;
	}
}


bool InputClass::isKeyDown(unsigned int key) {
	// Return what state the key is in (pressed/not pressed).
	return m_currentKey[key];
}

KEY_STATE InputClass::getKeyState(unsigned int key) {
	if (!m_currentKey[key] && !m_lastKey[key]) {
		return KEY_STATE::NORMAL;
	} else if (m_currentKey[key] && !m_lastKey[key]) {
		return KEY_STATE::DOWN;
	} else if (m_currentKey[key] && m_lastKey[key]) {
		return KEY_STATE::PRESS;
	} else if (!m_currentKey[key] && m_lastKey[key]) {
		return KEY_STATE::UP;
	} else {
		return KEY_STATE::NORMAL;
	}
}