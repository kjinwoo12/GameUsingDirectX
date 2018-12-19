#pragma once

enum class KEY_STATE {
	DOWN=-2,
	PRESS=-1,
	NORMAL=0,
	UP=1,
};

class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void initialize();

	void keyDown(unsigned int);
	void keyUp(unsigned int);

	bool updateKeyState();
	bool isKeyDown(unsigned int);
	KEY_STATE getKeyState(unsigned int);

private:
	bool m_currentKey[256];
	bool m_lastKey[256];
};

