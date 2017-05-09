dofile("../Lua Scripts/Editor.lua")
dofile("../Lua Scripts/EntityHandler.lua")

function Start()
	startStateOn = true
	editorStateOn = false

	entityHandler = EntityHandler:New()
	editor = Editor:New()
end

function Update(dt)

	if (startStateOn) then
		entityHandler:Update(dt)
	end
	if (editorStateOn) then
		editor:Update(dt)
	end

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
	entityHandler.enemyContainer[entityHandler.nrOfEnemys + 1] = Enemy:New({x = x, y = y})
	entityHandler.nrOfEnemys = entityHandler.nrOfEnemys + 1
end

function restart()
	entityHandler:restart()
end