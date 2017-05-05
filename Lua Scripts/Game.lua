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
	return entityHandler.getPlayerPos()
end

function getEnemyPos(key)
	return entityHandler:getEnemyPos(key)
end

function getPlayerLookDirection()
	return entityHandler:getPlayerLookDirection()
end

function addEnemy(x, y)
	entityHandler:addEnemy(x, y)
end