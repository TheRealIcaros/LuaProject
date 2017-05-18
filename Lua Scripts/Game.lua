dofile("../Lua Scripts/EntityHandler.lua")
dofile("../Lua Scripts/Map.lua")

function Start()
	startStateOn = true
	--editorStateOn = false

	entityHandler = EntityHandler:New()

	map = Map:New()
end

function Update(dt)

	entityHandler:Update(dt)

end

function setPlayerPos(x, y)
	entityHandler:setPlayerPos(x, y);
end

function getPlayerPos()
	return entityHandler.player1:getPlayerPos()
end

function getEnemyPos(key)
	return entityHandler.enemyContainer[key]:getEnemyPos()
end

function getPlayerLookDirection()
	return entityHandler.player1:getPlayerLookDirection()
end

function addEnemy(x, y)
	entityHandler:addEnemy(x, y)
end

function restart()
	entityHandler:restart()
end

function loadFromFile(name)
	return map:loadFromFile(name)
end

function getMaterial(x, y)
	return map:getMaterial(x, y)
end

function getMapSize()
	return map:getMapSize()
end

function getPlayerIsAttacking()
	return entityHandler:getPlayerIsAttacking()
end

function killEnemy(i)
	entityHandler:killEnemy(i);
end

function getPlayerDir()
	return entityHandler:getPlayerDir()
end

function setPlayerDir(x, y)
	entityHandler:setPlayerDir(x, y)
end

function setCanMove(Up, Down, Left, Right)
	entityHandler:setCanMove(Up, Down, Left, Right)
end

function movePlayerFromC(x, y, dt)
	entityHandler:movePlayerFromC(x, y, dt)
end

function getCanMove()
	return entityHandler:getCanMove()
end