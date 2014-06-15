
-- Class = {
-- 	-- name = "Class"
-- }

-- function Class:new(fields)	-- exemple de constructeur
-- 	tab = fields or {}
-- 	setmetatable(tab, self)
-- 	self.__index = self
-- 	self.__metatable = self
-- 	return tab
-- end

-- map = Class:new()

-- function map:get(x,y,distance,me)
-- 	if type(x) ~= "number" or type(y) ~= "number"
-- 		then print("map:get expects a number"); print(debug.traceback()) end
-- 	if x == 5.0 and y == 5.0 then print("map:get enemy !!!!!!"); return {[1]=Player} end
-- 	if x == 1.0 and y == 9.0 then print("map:get item !!!!!!"); return {[1]=Item} end
-- 	if x == 9.0 and y == 1.0 then print("map:get bomb !!!!!!"); return {[1]=Bomb} end
-- 	return nil
-- end

-- GameObject = {_type = "GameObject"}

-- function GameObject:getType()
-- 	return "Player"
-- end

-- function GameObject:getX()
-- 	return 4.0
-- end

-- function GameObject:getY()
-- 	return 6.0
-- end

-- -- Player = GameObject:new({_type = "Player", _name = "PlayerName"})

-- -- function Player:getName()
-- -- 	return "the_name"
-- -- end

-- -- me = Player:new({_type = "Me", _name = "Marie"})

-- -- function me:moveUp()
-- -- 	print("moveUp")
-- -- 	return true
-- -- end

-- -- function me:moveDown()
-- -- 	print("moveDown")
-- -- 	return true
-- -- end

-- -- function me:moveLeft()
-- -- 	print("moveLeft")
-- -- 	return true
-- -- end

-- -- function me:moveRight()
-- -- 	print("moveRight")
-- -- 	return true
-- -- end

-- -- function me:putBomb()
-- -- 	print("putBomb")
-- -- 	return true
-- -- end

-- Player = {_type = "Player", _name = "ThePlayer"}

-- function Player:getType()
-- 	return "Player"
-- end

-- function Player:getX()
-- 	return 5.0
-- end

-- function Player:getY()
-- 	return 5.0
-- end

-- Item = {_type = "Item"}

-- function Item:getType()
-- 	return "Item"
-- end

-- function Item:getX()
-- 	return 5.0
-- end

-- function Item:getY()
-- 	return 5.0
-- end

-- Bomb = {_type = "Bomb"}

-- function Bomb:getTimeBeforeExplosion()
-- 	return 2
-- end

-- function Bomb:getType()
-- 	return "Bomb"
-- end

-- function Bomb:getX()
-- 	return 9.0
-- end

-- function Bomb:getY()
-- 	return 1.0
-- end

-- Item = {_type = "Item"}

-- function Item:getType()
-- 	return "Item"
-- end

-- function Item:getX()
-- 	return 1.0
-- end

-- function Item:getY()
-- 	return 9.0
-- end
