#include "../Object/Headers/NPC.h"

NPC::NPC() : Entity(), isAlly(false)
{ }

NPC::NPC(glm::vec2 coords, glm::vec2 len, glm::vec2 vel, Texture tex,
	bool ally)
	: Entity(coords, len, vel, tex), isAlly(ally)
{ }
