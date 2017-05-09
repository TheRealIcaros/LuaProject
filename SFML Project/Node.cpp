#include "Node.hpp"

Node::Node()
{
	this->material = 0;

	if (!this->grass.loadFromFile("../Images/grass.png"))
	{
		cout << "Grass image not found!" << endl;
	}
	if (!this->wall.loadFromFile("../Images/wall.png"))
	{
		cout << "Wall image not found!" << endl;
	}
	if (!this->water.loadFromFile("../Images/water.png"))
	{
		cout << "Water image not found!" << endl;
	}

	this->sprite.setTexture(this->grass);
}

Node::~Node()
{

}

void Node::update()
{

}

void Node::draw(RenderTarget &target, RenderStates states)const
{
	target.draw(this->sprite, states);
}

void Node::setPosition(int x, int y)
{
	this->sprite.setPosition(x, y);
}

Sprite Node::getSprite()
{
	return this->sprite;
}

void Node::setMaterial(int material)
{
	this->material = material;

	if (this->material == 0)
	{
		this->sprite.setTexture(this->grass);
	}
	else if (this->material == 1)
	{
		this->sprite.setTexture(this->wall);
	}
	else if (this->material == 2)
	{
		this->sprite.setTexture(this->water);
	}
}