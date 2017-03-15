#pragma once
class UserInput
{
private:
	bool keys[256];
public:
	UserInput();
	void processKeys();
};

