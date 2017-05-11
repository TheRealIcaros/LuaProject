#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "Node.hpp"

#include "Include.h"

class Editor : public Drawable
{
private:
	Texture grassTexture;
	Sprite grass;
	Texture wallTexture;
	Sprite wall;
	Texture waterTexture;
	Sprite water;
	RectangleShape border;

	RectangleShape saveButton;
	RectangleShape loadButton;
	RectangleShape newButton;

	int materialSelected;

	lua_State* E;

	//vector<Enemy*>
	vector<vector <Sprite*>> map;

	int sizeXY;

public:
	Editor();
	~Editor();
	void update(RenderWindow &window);
	void draw(RenderTarget &target, RenderStates states)const;

	void checkMaterials(RenderWindow &window);
	void getMousePos(RenderWindow &window);

	int getMaterialSelected();

	void saveOnFile(lua_State* E, RenderWindow &window);
	void loadFromFile(lua_State* E, RenderWindow &window);

	void reloadSprites(lua_State* E);
	void reloadVectors();
	void clearVector();
	void newMap(lua_State* E, RenderWindow &window);
};

#endif // !
