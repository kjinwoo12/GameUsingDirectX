#pragma once

enum class KEY_STATE {
	DOWN=1,
	PRESS,
	UP,
	NORMAL,	
};

class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool UpdateKeyState();
	bool IsKeyDown(unsigned int);
	KEY_STATE GetKeyState(unsigned int);

private:
	bool mCurrentKey[256];
	bool mLastKey[256];
};

