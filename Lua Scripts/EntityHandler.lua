dofile("../Lua Scripts/Vector.lua")
dofile("../Lua Scripts/Player.lua")
dofile("../Lua Scripts/Enemy.lua")

--EntityHandler = {player1 = Player:New(), enemyContainer = {}, nrOfEnemys = 0}

--function EntityHandler:New(e)
	--e = e or {}
	--self.__index = self
	--setmetatable(e, self)
	--return e
--end

function Start()
	player1 = Player:New()
	enemyContainer = {}
	nrOfEnemys = 0
	--enemy1 = Enemy:New()
	--enemy2 = Enemy:New()
end

function Update(dt)
	player1:Update(dt)

	for key, value in pairs(enemyContainer) do
		enemyContainer[key]:Update(player1.pos, dt)
	end

	--enemy1:Update(player1.pos, dt)
	--enemy2:Update(player1.pos, dt)
end

function getPlayerPos()
	return player1:getPlayerPos()
end

function getEnemyPos(key)
	return enemyContainer[key]:getEnemyPos()
end

function getPlayerLookDirection()
	return player1:getPlayerLookDirection()
end

function addEnemy(x, y)
	enemyContainer[nrOfEnemys + 1] = Enemy:New({x = x, y = y})
	nrOfEnemys = nrOfEnemys + 1
end
