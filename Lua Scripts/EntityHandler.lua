dofile("../Lua Scripts/Vector.lua")
dofile("../Lua Scripts/Player.lua")
dofile("../Lua Scripts/Enemy.lua")

function Start()
	player1 = Player:New()
	
	enemy1 = Enemy:New()
end

function Update(dt)
	player1:Update(dt)
	enemy1:Update(player1.pos, dt)
end

function getPlayerPos()
	return player1:getPlayerPos()
end