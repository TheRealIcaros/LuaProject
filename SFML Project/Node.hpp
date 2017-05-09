#ifndef NODE_HPP
#define NODE_HPP

#include "Include.h"

class Node : public Drawable
{
private:
	int material;

	Texture grass;
	Texture wall;
	Texture water;
	Sprite sprite;

public:
	Node();
	~Node();
	void update();
	void draw(RenderTarget &target, RenderStates states)const;

	void setPosition(int x, int y);
	Sprite getSprite();
	void setMaterial(int material);
};
#endif