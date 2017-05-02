#include "EntityContainer.hpp"

EntityContainer::EntityContainer(lua_State* L)
{
	this->player = new Player(L);

	this->nrOf = 0;
	this->cap = 10;
	this->enemys = new Enemy*[this->cap];

	this->enemys[this->nrOf++] = new Enemy(L);
}

EntityContainer::~EntityContainer()
{
	for (int i = 0; i < this->nrOf; i++)
	{
		delete this->enemys[i];
	}
	delete[]this->enemys;

	delete this->player;
}

void EntityContainer::update(lua_State* L, float dt)
{
	this->player->update(L, dt);

	for (int i = 0; i < this->nrOf; i++)
	{
		this->enemys[i]->update(L, dt);
	}
}

void EntityContainer::draw(RenderTarget &target, RenderStates states)const
{
	for (int i = 0; i < this->nrOf; i++)
	{
		target.draw(this->enemys[i]->getSprite(), states);
	}
	target.draw(this->player->getSprite(), states);
}