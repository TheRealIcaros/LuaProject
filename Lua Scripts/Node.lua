dofile("../Lua Scripts/Vector.lua")

Node = {pos = Vector:New(), material = 0}

function Node:New(n)
	n = n or {}
	self.__index = self
	setmetatable(n, self)
	return n
end

function Node:getMaterial()
	return self.material
end

function Node:setPosition(x, y)
	self.pos.x = x
	self.pos.y = y
end

function Node:getPosition()
	return self.pos.x, self.pos.y
end

function Node:setMaterial(material)
	self.material = material
end
