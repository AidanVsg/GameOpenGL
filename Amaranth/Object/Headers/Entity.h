#if !defined(_ENTITY_H)
#define _ENTITY_H

#include "../View/Headers/Texture.h"
#include <vector>
#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"
#include "../glm/glm/gtc/type_ptr.hpp"
#include <iostream>


#define GET(Type, MemberName, FaceName) \
          Type Get##FaceName() const { \
             return MemberName; \
          }
#define SET(Type, MemberName, FaceName) \
            void Set##FaceName(const Type &value) { \
                MemberName = value; \
            }

class Entity {
public:
	//CONSTRUCTORS
	Entity();
	Entity(glm::vec2 coords, glm::vec2 len, glm::vec2 vel, Texture tex);

	typedef glm::vec2 GridCoordinates;

	GET(glm::vec2, coordinate, Coordinate)
	GET(glm::vec2, length, Length)
	GET(std::vector<GridCoordinates>, grids, Grids)
	SET(float, widthAR, WidthAR)
	SET(float, heightAR, HeightAR)
	SET(std::vector<GridCoordinates>, grids, Grids)


		//SETTERS
		//inline void setAR(float wAR, float hAR);
		//inline void setTexture(Texture texture);
		//inline void setCoordX(float x);
		//inline void setCoordY(float y);
		//inline void setHitPoints(float hp);
		//inline void setCoords(std::vector<std::pair<int, int>> coords);
		//GETTERS
		//inline Texture getTexture();
		//inline float getW_AR();
		//inline float getH_AR();
		//inline float getCoordX();
		//inline float getCoordY();
		//inline float getHitPoints();
		//inline std::vector<std::pair<int, int>> getCoords();
protected:
	float widthAR, heightAR, healthPoints;
	glm::vec2 coordinate, length, velocity;
	Texture texture;
	std::vector<GridCoordinates> grids;
};


#endif  //_ENTITY_H
