dofile("../Lua Scripts/Node.lua")
dofile("../Lua Scripts/Vector.lua")

Editor = {size = 16,
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
	Editor =  Editor:New()
	for i = 1, self.size do
		self.nodeList[i] = {}
	end

	for y = 1, self.size do
		for x = 1, self.size do
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

function Editor:printToTxt(name)
--function Editor.printToTxt(self, name)
	file = io.open("..\\Map\\" .. name .. ".txt", "w")

	for y = 1, Editor.size do
		for x = 1, Editor.size do
		print(self.nodeList[x][y]:getMaterial())
			output = output .. Editor.nodeList[x][y]:getMaterial()
		end
		print(output)
		file:write(output, "\n")
		output = ""
	end

	file:close()
end

function setMapSize(s)
	Editor.size = s
end

function getMapSize()
	return Editor.size
end