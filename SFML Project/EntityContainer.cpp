#include "EntityContainer.hpp"

EntityContainer::EntityContainer()
{

}

EntityContainer::EntityContainer(lua_State* L)
{
	this->player = Player();
	//this->enemys = vector<Enemy>();

	//this->enemys = new Enemy*[this->cap];

	//addEnemy(L);
}

EntityContainer::~EntityContainer()
{
	for (int i = 0; i < this->enemys.size(); i++)
	{
		delete this->enemys[i];
	}
	this->enemys.clear();
}

EntityContainer::EntityContainer(const EntityContainer &originalObject)
{
	
}

void EntityContainer::operator=(const EntityContainer &originalObject)
{

}

void EntityContainer::update(lua_State* L, float dt)
{
	this->player.update(L, dt);
	
	for (int i = 0; i < this->enemys.size(); i++)
	{
		this->enemys[i]->update(L, dt, i + 1);

		enemyAttackPlayerColition(i);

		if (this->player.getIsSwinging())
		{
			this->playerAttackEnemyColition(L, i);
		}
	}	
}

void EntityContainer::draw(RenderTarget &target, RenderStates states)const
{
	for (int i = 0; i < this->enemys.size(); i++)
	{
		target.draw(*this->enemys[i], states);
	}

	target.draw(this->player, states);
}

void EntityContainer::addEnemy(lua_State* L, float x, float y)
{
	cout << x << ", " << y << endl;
	lua_getglobal(L, "addEnemy");
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	lua_pcall(L, 2, 0, 0);

	//this->enemys[this->nrof++] = new Enemy(L, x, y);

	this->enemys.push_back(new Enemy(L, x, y));
}

void EntityContainer::enemyAttackPlayerColition(int i)
{
	if (this->player.getHitbox().getGlobalBounds().intersects(this->enemys[i]->getSprite().getGlobalBounds()))
	{
		if (hpClock.getElapsedTime().asSeconds() > 1.0f)
		{
			hpClock.restart();
			this->player.damageHp();
			cout << this->player.getHp() << endl;
		}
	}
}

void EntityContainer::playerAttackEnemyColition(lua_State* L, int i)
{
	if (this->player.getSprite().getGlobalBounds().intersects(this->enemys[i]->getSprite().getGlobalBounds()))
	{
		cout << "Player Hit Enemy" << endl;

		Enemy *temp;

		temp = this->enemys.at(i);
		this->enemys.at(i) = this->enemys.back();
		this->enemys.back() = temp;
		delete this->enemys.back();
		this->enemys.pop_back();

		lua_getglobal(L, "killEnemy");
		lua_pushinteger(L, i);
		lua_pcall(L, 1, 0, 0);
	}
}

void EntityContainer::wallColition()
{

}

void EntityContainer::restart(lua_State* L)
{
	for (int i = 0; i < this->enemys.size(); i++)
	{
		delete this->enemys[i];
	}
	this->enemys.clear();

	lua_getglobal(L, "restart");
	lua_pcall(L, 0, 0, 0);
}

void EntityContainer::setPlayerSpawnPos(lua_State* L, Vector2i pos)
{
	this->player.setPlayerPosInLua(L, pos);
}