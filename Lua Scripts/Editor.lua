dofile("../Lua Scripts/Node.lua")
dofile("../Lua Scripts/Vector.lua")

--Editor = {size = 16,
			--nodeList = {},
			--startPos = Vector:New({x = 0, y = 0})}

--Logic

editor = {}

function Start()
	editor = {size = 16, nodeList = {}, startPos = Vector:New({x = 0, y = 0})}

	for i = 1, editor.size do
		editor.nodeList[i] = {}
	end

	for y = 1, editor.size do
		for x = 1, editor.size do
			editor.nodeList[y][x] = Node:New()
		end
	end
end

function Update(dt)
	
end

function setStartPosition(x, y)
	editor.startPos.x = x
	editor.startPos.y = y
end

function setPostion(x, y)
	editor.nodeList[x + 1][y + 1]:setPosition(x, y)
end

function addNode(x, y)

end

function setMaterial(x, y, material)
	editor.nodeList[x + 1][y + 1]:setMaterial(material)
end

function getMaterial(x, y)
	return editor.nodeList[x + 1][y + 1]:getMaterial()
end

function printToTxt(name)
	local file = io.open("..\\Map\\" .. name .. ".txt", "w")
	
	if(file ~= nil) then
		print("The map '" .. name .. ".txt' already exists. Do you want to overwrite. [y/n]: ")
		local input = confirmOverwrite()

		if(input)then
			file:write(editor.size, "\n")
			for y = 1, editor.size do
				for x = 1, editor.size do
					file:write(editor.nodeList[x][y]:getMaterial())
				end
				file:write("\n")
			end

			file:close()
			print("The map size is: " .. editor.size .. "x" .. editor.size .. "\nThe name of the map is: " .. name .. ".txt" .. " \nAnd is saved in Map folder")
			return true
		else
			return false
		end
	end
end

function setMapSize(s)
	editor.size = s
	resetTables()
end

function getMapSize()
	return editor.size
end

function resetTables()
	for i = 1, editor.size do
		editor.nodeList[i] = {}
	end

	for y = 1, editor.size do
		for x = 1, editor.size do
			editor.nodeList[x][y] = Node:New()
		end
	end
end

function loadFromFile(name)
	print(name)
	local file = io.open("..\\Map\\" .. name .. ".txt", "r")
	if(file ~= nil) then
		print("Loading map: " .. name)
		io.input(file)
	
		editor.size = tonumber(io.read())
		resetTables()

		for y = 1, editor.size do
			local temp = io.read()
			for x = 1, editor.size do
				local c = temp:sub(x, x)
				editor.nodeList[x][y]:setMaterial(tonumber(c))
			end
		end
		return true
	else
		return false
	end
end