
Vector = {x = 0, y = 0, 
	Normalize = function(self) 
	local length = self:Length() 
	self.x = self.x / length
	self.y = self.y / length
end 
}

function Vector:New(v)
	v = v or {}
	self.__index = self
	setmetatable(v, self)
	return v
end

function Vector:Normalize() 
	local length = self:Length() 
	self.x = self.x / length
	self.y = self.y / length
end

function Vector:Length()
	return math.sqrt(self.x ^ 2 + self.y ^ 2)
end

function Vector:__tostring()
	return "(" .. self.x .. ", " .. self.y .. ")"
end

function Vector.__add(a, b)
	if(type(a) == "number") then
		return Vector:New({x = b.x + a, y = b.y + a})
	elseif(type(b) == "number") then
		return Vector:New({x = a.x + b, y = a.y + b})
	else
		return Vector:New({x = a.x + b.x, y = a.y + b.y})
	end		
end

function Vector.__sub(a, b)
	if(type(a) == "number") then
		return Vector:New({x = b.x - a, y = b.y - a})
	elseif(type(b) == "number") then
		return Vector:New({x = a.x - b, y = a.y - b})
	else
		return Vector:New({x = a.x - b.x, y = a.y - b.y})
	end		
end

function Vector.__mul(a, b)
	if(type(a) == "number") then
		return Vector:New({x = b.x * a, y = b.y * a})
	elseif(type(b) == "number") then
		return Vector:New({x = a.x * b, y = a.y * b})
	else
		return Vector:New({x = a.x * b.x, y = a.y * b.y})
	end
end