dofile("../Lua Scripts/Vector.lua")

Enemy = {pos = Vector:New({x = 50, y = 50}), 
			speed = 100}

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
	local dir = Vector:New({x = 0, y = 0})
	dir = playerPos - self.pos
	dir:Normalize()
	
	local movementLength = Vector:New({x = 0, y = 0})
	movementLength = dir * self.speed * dt

	--print(self.pos)

	self.pos = self.pos + movementLength
end

--Positions
function Enemy:setEnemyPos(x, y)
	self.pos.x = (x * 16) + 32
	self.pos.y = (y * 16) + 32
end

function Enemy:getEnemyPos()
	return self.pos.x, self.pos.y
end

function Enemy:restart()
	self = nil
end