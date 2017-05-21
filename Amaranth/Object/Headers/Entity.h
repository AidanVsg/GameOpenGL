#if !defined(_ENTITY_H)
#define _ENTITY_H

#include "../View/Headers/Texture.h"
#include <vector>
#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"
#include "../glm/glm/gtc/type_ptr.hpp"
#include <iostream>
#include "../../glew/include/GL/glew.h"


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
	Entity(glm::vec2 coords, glm::vec2 len, glm::vec2 vel, GLuint texID);

	typedef glm::vec2 GridCoordinates;

	GET(glm::vec2, coordinate, Coordinate)
		GET(glm::vec2, length, Length)
		GET(std::vector<GridCoordinates>, grids, Grids)
		GET(bool, nU, N_up)
		GET(bool, nD, N_down)
		GET(bool, nL, N_left)
		GET(bool, nR, N_right)
		GET(GLuint, textureID, TextureID)

		SET(glm::vec2, coordinate, Coordinate)
		SET(glm::vec2, length, Length)
		SET(std::vector<GridCoordinates>, grids, Grids)
		SET(bool, nU, N_up)
		SET(bool, nD, N_down)
		SET(bool, nL, N_left)
		SET(bool, nR, N_right)
		SET(GLuint, textureID, TextureID)

		//friend Entity operator+(const Entity &e1, const Entity &e2);

protected:
	float dt;
	float healthPoints;
	bool nU, nD, nR, nL;
	glm::vec2 coordinate, length, velocity;
	GLuint textureID;
	std::vector<GridCoordinates> grids;
};

//Entity operator+(const Entity &e1, const Entity &e2)
//{
//	Entity eN;
//
//	float x, y, xL, yL;
//
//
//	if (e1.GetCoordinate().x == e2.GetCoordinate().x)
//	{
//		if (e1.GetLength().x == e2.GetLength().x)
//		{
//			x = e1.GetCoordinate().x;
//			xL = e1.GetLength().x;
//		}
//		else if (e1.GetLength().x < e2.GetLength().x)
//		{
//			x = e1.GetCoordinate().x;
//			xL = e2.GetLength().x;
//		}
//		else
//		{
//			x = e1.GetCoordinate().x;
//			xL = e1.GetLength().x;
//		}
//	}
//	else if (e1.GetCoordinate().x < e2.GetCoordinate().x)
//	{
//		x = e1.GetCoordinate().x;
//		xL = e1.GetLength().x + e2.GetLength().x;
//	}
//	else
//	{
//		x = e2.GetCoordinate().x;
//		xL = e2.GetLength().x + e1.GetLength().x;
//	}
//
//	if (e1.GetCoordinate().y == e2.GetCoordinate().y)
//	{
//		if (e1.GetLength().y == e2.GetLength().y)
//		{
//			y = e1.GetCoordinate().y;
//			yL = e1.GetLength().y;
//		}
//		else if (e1.GetLength().y < e2.GetLength().y)
//		{
//			y = e1.GetCoordinate().y;
//			yL = e2.GetLength().y;
//		}
//		else
//		{
//			y = e1.GetCoordinate().y;
//			yL = e1.GetLength().y;
//		}
//
//	}
//	else if (e1.GetCoordinate().y < e2.GetCoordinate().y)
//	{
//		y = e1.GetCoordinate().y;
//		yL = e1.GetLength().x + e2.GetLength().y;
//	}
//	else
//	{
//		y = e2.GetCoordinate().y;
//		yL = e2.GetLength().y + e1.GetLength().y;
//	}
//
//	eN.SetCoordinate(glm::vec2(x, y));
//	eN.SetLength(glm::vec2(xL, yL));
//
//	return eN;
//}


#endif  //_ENTITY_H
