dofile("../Lua Scripts/Vector.lua")
dofile("../Lua Scripts/Player.lua")
dofile("../Lua Scripts/Enemy.lua")

EntityHandler = {player = Player:New(),
	enemyContainer = {},
	nrOfEnemys = 0}

function EntityHandler:New(e)
	e = e or {}
	self.__index = self
	setmetatable(e, self)
	return e
end

function EntityHandler:Start()
	self.player = Player:New()
	self.enemyContainer = {}
	self.nrOfEnemys = 0
end

function EntityHandler:Update(dt)
	self.player:Update(dt)

	for key, value in pairs(self.enemyContainer) do
		self.enemyContainer[key]:Update(self.player.pos, dt)
	end
end

function EntityHandler:setPlayerPos(x, y)
	self.player:setPlayerPos(x, y);
end

function EntityHandler:getPlayerPos()
	return self.player:getPlayerPos()
end

function EntityHandler:getEnemyPos(key)
	return self.enemyContainer[key]:getEnemyPos()
end

function EntityHandler:getPlayerLookDirection()
	return self.player:getPlayerLookDirection()
end

function EntityHandler:addEnemy(x, y)
	self.nrOfEnemys = self.nrOfEnemys + 1
	self.enemyContainer[self.nrOfEnemys] = Enemy:New({x = x, y = y})
	self.enemyContainer[self.nrOfEnemys]:setEnemyPos(x, y)
end

function EntityHandler:restart()
	self:Start()
end

function EntityHandler:getPlayerIsAttacking()
	return self.player:getPlayerIsAttacking()
end

function EntityHandler:killEnemy(i)
	self.enemyContainer[i + 1], self.enemyContainer[self.nrOfEnemys] = self.enemyContainer[self.nrOfEnemys], self.enemyContainer[i + 1]
	self.enemyContainer[self.nrOfEnemys] = nil
	self.nrOfEnemys = self.nrOfEnemys - 1

	self.player:increaseKills()
end

function EntityHandler:getPlayerDir()
	return self.player:getPlayerDir()
end

function EntityHandler:setPlayerDir(x, y)
	self.player:setPlayerDir(x, y)
end

function EntityHandler:setCanMove(Up, Down, Left, Right)
	self.player:setCanMove(Up, Down, Left, Right)
end

function EntityHandler:movePlayerFromC(x, y, dt)
	self.player:movePlayerFromC(x, y, dt)
end

function EntityHandler:getCanMove()
	return self.player:getCanMove()
end

function EntityHandler:getKills()
	return self.player:getKills()
end

function EntityHandler:decreaseHp()
	self.player:decreaseHp()
end

function EntityHandler:getHp()
	return self.player:getHp()
end

function EntityHandler:isOnWater(onWater)
	self.player:isOnWater(onWater)
end