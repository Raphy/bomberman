
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
	-- if x == 5.0 and y == 5.0 then print("map:get enemy !!!!!!"); return {[1]=Enemy} end
	return nil
end

-- GameObject = Class:new({_type = "GameObject"})

-- function GameObject:getType()
-- 	return "enemy"
-- end

-- function GameObject:getX()
-- 	return 4.0
-- end

-- function GameObject:getY()
-- 	return 6.0
-- end

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

-- Enemy = Player:new({_type = "enemy", _name = "TheEnemy"})

-- function Enemy:getX()
-- 	return 5.0
-- end

-- function Enemy:getY()
-- 	return 5.0
-- end

-- Item = GameObject:new({_type = "Item"})

-- Bomb = Item:new({_type = "Bomb"})

-- function Bomb:getTimeBeforeExplosion()
-- 	return 2
-- end
