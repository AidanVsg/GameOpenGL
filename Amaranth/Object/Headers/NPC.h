#if !defined(_NPC_H)
#define _NPC_H

#include "../Object/Headers/Entity.h"

class NPC : public Entity {
private:
	bool isAlly;
public:
	NPC();
};

#endif  //_NPC_H
