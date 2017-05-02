dofile("../Lua Scripts/Vector.lua")

Enemy = {pos = Vector:New(), 
			speed = 50}

function Enemy:New(e)
	e = e or {}
	self.__index = self
	setmetatable(e, self)
	return e
end

--Game Logic
function Enemy:Start()
	--local dir = Vector:New({x = 0, y = 0})
	--local movementLength = Vector:New({x = 0, y = 0})
end

function Enemy:Update(playerPos, dt)
	
	self:updateMovement(playerPos, dt)

end

--Update Movements
function Enemy:updateMovement(playerPos, dt)
	local dir = Vector:New()
	dir = playerPos - self.pos
	dir:Normalize()

	local movementLength = Vector:New()
	movementLength = dir * self.speed * dt

	self.pos = self.pos + movementLength
end

--Positions
function Enemy:setEnemyPos(x, y)
	self.pos.x = x
	self.pos.y = y
end

function Enemy:getEnemyPos()
	return self.pos.x, self.pos.y
end