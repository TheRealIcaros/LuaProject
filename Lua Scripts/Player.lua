dofile("../Lua Scripts/Vector.lua")

Player = {pos = Vector:New({x = 15, y = 15}),
			speed = 75,
			lookDirection = 0}

function Player:New(p)
	p = p or {}
	self.__index = self
	setmetatable(p, self)
	return p
end

--Game Logic
function Player:Start()
	--playerPos = Vector:New({x = 0, y = 0})
	--dir = Vector:New({x = 0, y = 0})
	--movementSpeed = 75
end

function Player:Update(dt)

	self:updateMovement(dt)	
	
end

--Update Movements
function Player:updateMovement(dt)
	local dir = Vector:New()
	dir.x, dir.y, self.lookDirection = CheckMovement()

	if((dir.x > 0 or dir.x < 0) and (dir.y > 0 or dir.y < 0))then
		dir.x = dir.x * 0.707
		dir.y = dir.y * 0.707
	end
		
	local movementLength = Vector:New({x = 0, y = 0})
	movementLength = dir * self.speed * dt

	self.pos = self.pos + movementLength
end

--Positions
function Player:setPlayerPos(x, y)
	self.pos.x = x
	self.pos.y = y
end

function Player:getPlayerPos()
	return self.pos.x, self.pos.y
end

function Player:getPlayerLookDirection()
	return self.lookDirection
end