//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : openglGame
//  @ File Name : World.h
//  @ Date : 14/03/2017
//  @ Author : 
//
//


#if !defined(_WORLD_H)
#define _WORLD_H

#include "Entity.h"

class World {
private:
    int numberOfEntities = 0;
	Entity* entities;
public:
	World();
	Entity getEntity(int x);
	void addEntity(Entity _entity);
};




#endif  //_WORLD_H