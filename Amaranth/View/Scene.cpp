#include "../View/Headers/Scene.h"
#include "../Object/Headers/Player.h"
#include "../View/Headers/Renderer.h"

Scene::Scene()
{

}

void Scene::draw(Player p, Renderer r)
{

	p.checkJumpState();
	p.processKeys();								//process keyboard		


	r.display(p);					// Draw The Scene
}

