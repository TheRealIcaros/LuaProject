dofile("../Lua Scripts/Vector.lua")

--Position
playerPos = Vector.New({x = 0, y = 0});

function setPlayerPos(x, y)
	playerPos.x = x
	playerPos.y = y
end

function getPlayerPos()
	return playerPos.x, playerPos.y
end

--Color
playerColor = {r = 0, g = 0, b = 0, a = 255}

function changeColorR(r, Red)
	playerColor[r] = Red
end