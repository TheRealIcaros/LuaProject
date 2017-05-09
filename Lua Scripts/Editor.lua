dofile("../Lua Scripts/Node.lua")
dofile("../Lua Scripts/Vector.lua")

Editor = {size = Vector:New({x = 16, y = 16}),
			nodeList = {},
			startPos = Vector:New({x = 0, y = 0})}

function Editor:New(e)
	e = e or {}
	self.__index = self
	setmetatable(e, self)
	return e
end

--Logic
function Editor:Start()
	for i = 1, self.size.x do
		self.nodeList[i] = {}
	end

	for x = 1, self.size.x do
		for y = 1, self.size.y do
			self.nodeList[x][y] = Node:New()
		end
	end
end

function Editor:Update(dt)
	
end

function Editor:setStartPosition(x, y)
	self.startPos.x = x
	self.startPos.y = y
end


function Editor:setPostion(x, y)
	self.nodeList[x + 1][y + 1]:setPosition(x, y)
end

function Editor:addNode(x, y)

end

function Editor:setMaterial(x, y, material)
	self.nodeList[x + 1][y + 1]:setMaterial(material)
end