dofile("../Lua Scripts/Vector.lua")

Node = {pos = Vector:New(),
		type = 0}

function Node:New(n)
	n = n or {}
	self.__index = self
	setmetatable(e, self)
	return n
end

function Node:setNodePosition(x, y)
	self.pos.x = x
	self.pos.y = y
end

function Node:getNodePosition()
	return self.pos
end

function Node:setNodeType(t)
	self.type = t
end

function Node:getNodeType()
	return self.type
end


