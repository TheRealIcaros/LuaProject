dofile("../Lua Scripts/Vector.lua")
dofile("../Lua Scripts/Player.lua")
dofile("../Lua Scripts/Enemy.lua")

function Start()
	player1 = Player:New()
	
	enemyContainer = {e1 = Enemy:New()}
	
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