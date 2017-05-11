#ifndef MAP_HPP
#define MAP_HPP

#include "Include.h"

class Map : public Drawable
{
private:
	Texture grassTexture;
	Texture wallTexture;
	Texture waterTexture;
	Texture spawnEnemyTexture;
	Texture spawnPlayerTexture;


	bool mapFound = false;

	vector<vector <Sprite*>> map;
	int sizeXY;
public:
	Map();
	~Map();
	void update(RenderWindow &window);
	void draw(RenderTarget &target, RenderStates states)const;

	void loadFromFile(lua_State* L, RenderWindow &window);
	void reloadSprites(lua_State* L);

	void reloadVectors();
	void clearVector();
};
#endif
