#include "../Object/Headers/NPC.h"

NPC::NPC(float coordX, float coordY, bool isAlly, std::vector<std::pair<int, int>> coords)
{
	this->coordX = coordX;
	this->coordY = coordY;
	this->isAlly = isAlly;
	this->coordset = coords;
}
