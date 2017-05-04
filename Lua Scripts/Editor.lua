dofile("../Lua Scripts/Node.lua")
dofile("../Lua Scripts/Vector.lua")

Editor = {size = Vector:New({x = 16, y = 16}),
			nodeList = {}}

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

	for i = 1, self.size.x do
		for j = 1, self.size.y do
			self.nodeList[i][j] = Node:New()
		end
	end
end

function Editor:Update(dt)
	nodeTypeSelected = CheckEditorInput()

	local pos = Vector:New()
	pos.x, pos.y = MousePosition()

	if (pos.x > -1) then
		pos.x = pos.x % self.size.x
		pos.y = pos.y % self.size.y

		self.nodeList[pos.x][pos.y].setNodeType(nodeTypeSelected)
	end
end