dofile("../Lua Scripts/Vector.lua")

Player = {pos = Vector:New({x = 200, y = 200}),
			speed = 150,
			lookDirection = 0,
			isAttacking = false,
			dir = Vector:New(),
			canMoveUp = true,
			canMoveDown = true,
			canMoveLeft = true,
			canMoveRight = true,
			kills = 0,
			hp = 3}

function Player:New(p)
	p = p or {}
	self.__index = self
	setmetatable(p, self)
	return p
end

--Game Logic
function Player:Start()
	--playerPos = Vector:New({x = 0, y = 0})
	--dir = Vector:New({x = 0, y = 0})
	--movementSpeed = 75
end

function Player:Update(dt)

	self:checkMelee(dt)
	if(not self.isAttacking)then
		self:updateMovement(dt)	
	end
	
end

--Update Movements
function Player:updateMovement(dt)
	self.dir.x, self.dir.y, self.lookDirection = CheckMovement(self.lookDirection)

	if((self.dir.x > 0 or self.dir.x < 0) and (self.dir.y > 0 or self.dir.y < 0))then
		self.dir.x = self.dir.x * 0.707
		self.dir.y = self.dir.y * 0.707
	end

	length = self:calculateMovementLength(dt)

	if(self.lookDirection == 1)then --up
		if(self.canMoveUp)then
			self:movePlayer(0, length.y)
			self.canMoveUp = true
			self.canMoveDown = true
	 		self.canMoveRight = true
	 		self.canMoveLeft = true
		end
	elseif(self.lookDirection == 0)then --down
		if(self.canMoveDown)then
			self:movePlayer(0, length.y)
			self.canMoveUp = true
			self.canMoveDown = true
	 		self.canMoveRight = true
	 		self.canMoveLeft = true
		end
	elseif(self.lookDirection == 3)then --left
		if(self.canMoveLeft)then
			self:movePlayer(length.x, 0)
			self.canMoveUp = true
			self.canMoveDown = true
	 		self.canMoveRight = true
	 		self.canMoveLeft = true
		end
	elseif(self.lookDirection == 2)then --right
		if(self.canMoveRight)then
			self:movePlayer(length.x, 0)
			self.canMoveUp = true
			self.canMoveDown = true
	 		self.canMoveRight = true
	 		self.canMoveLeft = true
		end
	end
end

--Melee
function Player:checkMelee(dt)
	self.isAttacking = playerIsAttacking()
end

--Positions
function Player:setPlayerPos(x, y)
	self.pos.x = x
	self.pos.y = y
end

function Player:getPlayerPos()
	return self.pos.x, self.pos.y
end

function Player:getPlayerLookDirection()
	return self.lookDirection
end

function Player:getPlayerIsAttacking()
	return self.isAttacking
end

function Player:getPlayerDir()
	return self.dir.x, self.dir.y
end

function Player:setPlayerDir(x, y)
	self.dir.x = x
	self.dir.y = y
end

function Player:setCanMove(Up, Down, Left, Right)
print(Up .. " , " .. Down .. " , " .. Left .. " , " .. Up)
	self.canMoveUp = Up
	self.canMoveDown = Down
	self.canMoveLeft = Left
	self.canMoveRight = Right
end

function Player:movePlayer(x, y)
	self.pos.x = self.pos.x + x
	self.pos.y = self.pos.y + y
end

function Player:calculateMovementLength(dt)
	local movementLength = Vector:New({x = 0, y = 0})
	movementLength = self.dir * self.speed * dt

	return movementLength
end

function Player:movePlayerFromC(x, y, dt)
	self.dir.x = x
	self.dir.y = y
	length = self:calculateMovementLength(dt)

	self:movePlayer(length.x, length.y)
end

function Player:getCanMove()
	return self.canMoveUp, self.canMoveDown, self.canMoveLeft, self.canMoveRight
end

function Player:increaseKills()
	self.kills = self.kills + 1
end

function Player:getKills()
	return self.kills
end

function Player:decreaseHp()
	if(self.hp > 0)then
		self.hp = self.hp - 1
	end
end

function Player:getHp()
	return self.hp
end