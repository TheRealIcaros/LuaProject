dofile("../Lua Scripts/Vector.lua")
dofile("../Lua Scripts/Player.lua")
dofile("../Lua Scripts/Enemy.lua")

EntityHandler = {player1 = Player:New(),
	enemyContainer = {},
	nrOfEnemys = 0}

function EntityHandler:New(e)
	e = e or {}
	self.__index = self
	setmetatable(e, self)
	return e
end

function EntityHandler:Start()
	self.player1 = Player:New()
	self.enemyContainer = {}
	self.nrOfEnemys = 0
end

function EntityHandler:Update(dt)
	self.player1:Update(dt)

	for key, value in pairs(self.enemyContainer) do
		self.enemyContainer[key]:Update(self.player1.pos, dt)
	end
end

function EntityHandler:getPlayerPos()
	return self.player1:getPlayerPos()
end

function EntityHandler:getEnemyPos(key)
	return self.enemyContainer[key]:getEnemyPos()
end

function EntityHandler:getPlayerLookDirection()
	return self.player1:getPlayerLookDirection()
end

function EntityHandler:addEnemy(x, y)
	self.enemyContainer[self.nrOfEnemys + 1] = Enemy:New({x = x, y = y})
	self.nrOfEnemys = self.nrOfEnemys + 1
end

function EntityHandler:restart()
	self:Start()
end