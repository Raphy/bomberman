
Class = {
	-- name = "Class"
}

function Class:new(fields)	-- exemple de constructeur
	tab = fields or {}
	setmetatable(tab, self)
	self.__index = self
	self.__metatable = self
	return tab
end

map = Class:new()

function map:get(x,y,distance)
	if type(x) ~= "number" or type(y) ~= "number"
		then print("map:get expects a number"); print(debug.traceback()) end
	if x == 5.0 and y == 5.0 then print("map:get enemy !!!!!!"); return {[1]=Enemy} end
	if x == 1.0 and y == 9.0 then print("map:get bonus !!!!!!"); return {[1]=Bonus} end
	if x == 9.0 and y == 1.0 then print("map:get bomb !!!!!!"); return {[1]=Bomb} end
	return nil
end

GameObject = {_type = "GameObject"}

function GameObject:getType()
	return "Enemy"
end

function GameObject:getX()
	return 4.0
end

function GameObject:getY()
	return 6.0
end

-- Player = GameObject:new({_type = "Player", _name = "PlayerName"})

-- function Player:getName()
-- 	return "the_name"
-- end

-- me = Player:new({_type = "me", _name = "Marie"})

-- function me:moveUp()
-- 	print("moveUp")
-- 	return true
-- end

-- function me:moveDown()
-- 	print("moveDown")
-- 	return true
-- end

-- function me:moveLeft()
-- 	print("moveLeft")
-- 	return true
-- end

-- function me:moveRight()
-- 	print("moveRight")
-- 	return true
-- end

-- function me:putBomb()
-- 	print("putBomb")
-- 	return true
-- end

Enemy = {_type = "Enemy", _name = "TheEnemy"}

function Enemy:getType()
	return "Enemy"
end

function Enemy:getX()
	return 5.0
end

function Enemy:getY()
	return 5.0
end

Item = {_type = "Item"}

function Item:getType()
	return "Item"
end

function Item:getX()
	return 5.0
end

function Item:getY()
	return 5.0
end

Bomb = {_type = "Bomb"}

function Bomb:getTimeBeforeExplosion()
	return 2
end

function Bomb:getType()
	return "Bomb"
end

function Bomb:getX()
	return 9.0
end

function Bomb:getY()
	return 1.0
end

Bonus = {_type = "Bonus"}

function Bonus:getType()
	return "Bonus"
end

function Bonus:getX()
	return 1.0
end

function Bonus:getY()
	return 9.0
end