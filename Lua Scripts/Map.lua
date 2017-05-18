dofile("../Lua Scripts/Node.lua")
dofile("../Lua Scripts/Vector.lua")

Map = {size = 16, nodeList = {}, startPos = Vector:New({x = 0, y = 0})}

function Map:New(m)
	m = m or {}
	self.__index = self
	setmetatable(m, self)
	return m
end

function Map:Start()
	for i = 1, self.size do
		self.nodeList[i] = {}
	end

	for y = 1, self.size do
		for x = 1, self.size do
			self.nodeList[y][x] = Node:New()
		end
	end
end

function Map:setStartPosition(x, y)
	self.startPos.x = x
	self.startPos.y = y
end

function Map:setPostion(x, y)
	self.nodeList[x + 1][y + 1]:setPosition(x, y)
end

function Map:addNode(x, y)

end

function Map:setMaterial(x, y, material)
	self.nodeList[x + 1][y + 1]:setMaterial(material)
end

function Map:getMaterial(x, y)
	return self.nodeList[x + 1][y + 1]:getMaterial()
end

function Map:setMapSize(s)
	self.size = s
	self:resetTables()
end

function Map:getMapSize()
	return self.size
end

function Map:resetTables()
	for i = 1, self.size do
		self.nodeList[i] = {}
	end

	for y = 1, self.size do
		for x = 1, self.size do
			self.nodeList[x][y] = nil
			self.nodeList[x][y] = Node:New()
		end
	end
end

function Map:loadFromFile(name)
	local file = io.open("..\\Map\\" .. name .. ".txt", "r")
	if(file ~= nil) then
		print("Loading map: " .. name)
		io.input(file)
		self.size = tonumber(io.read())
		self:resetTables()

		for y = 1, self.size do
			local temp = io.read()
			for x = 1, self.size do
				local c = temp:sub(x, x)
				self.nodeList[x][y]:setMaterial(tonumber(c))
				if (tonumber(c) == 4) then
					self:setStartPosition(x, y)
				end
			end
		end
		return true	
	else
		return false
	end	
end