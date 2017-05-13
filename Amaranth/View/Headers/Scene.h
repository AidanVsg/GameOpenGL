#if !defined(_SCENE_H)
#define _SCENE_H
#include "../Object/Headers/Player.h"
#include "../View/Headers/Renderer.h"

class Scene {
public:
	Scene();
	void draw(Player p, Renderer r);
};

#endif  //_SCENE_H
