#include "EntityContainer.hpp"

EntityContainer::EntityContainer()
{

}

EntityContainer::EntityContainer(lua_State* L)
{
	this->player = new Player(L);

	//this->enemys = new Enemy*[this->cap];

	addEnemy(L);
}

EntityContainer::~EntityContainer()
{
	for (int i = 0; i < this->enemys2.size(); i++)
	{
		delete this->enemys2.at(i);
	}

	delete this->player;
}

void EntityContainer::update(lua_State* L, float dt)
{
	this->player->update(L, dt);

	for (int i = 0; i < this->enemys2.size(); i++)
	{
		this->enemys2.at(i)->update(L, dt, i + 1);

		//this->enemys[i]->update(L, dt, i + 1);
		playerColition(i);
	}

	//Collision
	
}

void EntityContainer::draw(RenderTarget &target, RenderStates states)const
{
	for (int i = 0; i < this->enemys2.size(); i++)
	{
		target.draw(this->enemys2.at(i)->getSprite(), states);
		//target.draw(this->enemys[i]->getSprite(), states);
	}
	target.draw(this->player->getSprite(), states);
}

void EntityContainer::addEnemy(lua_State* L, float x, float y)
{
	lua_getglobal(L, "addEnemy");
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	lua_pcall(L, 2, 0, 0);

	//this->enemys[this->nrOf++] = new Enemy(L, x, y);

	this->enemys2.push_back(new Enemy(L, x, y));
}

void EntityContainer::playerColition(int i)
{
	if (this->player->getSprite().getGlobalBounds().intersects(this->enemys2.at(i)->getSprite().getGlobalBounds()))
	{
		if (hpClock.getElapsedTime().asSeconds() > 1.0f)
		{
			hpClock.restart();
			this->player->damageHp();
			cout << this->player->getHp() << endl;
		}
	}
}

void EntityContainer::wallColition()
{

}
