#ifndef EDITOR_HPP
#define EDITOR_HPP

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

	int materialSelected;

public:
	Editor();
	~Editor();
	void update(RenderWindow &window, lua_State* L);
	void draw(RenderTarget &target, RenderStates states)const;

	void checkMaterials(RenderWindow &window);

	int getMaterialSelected();
};

#endif // !
