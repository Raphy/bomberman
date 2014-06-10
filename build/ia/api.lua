
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

function map:get(this, x,y)
	return nil
end

GameObject = Class:new({_type = "GameObject"})

function GameObject:getType(this)
	return this._type
end

function GameObject:getX(this)
	return 4.0
end

function GameObject:getY(this)
	return 6.0
end

Player = GameObject:new({_type = "Player", _name = "PlayerName"})

function Player:getName(this)
	return this._name
end

me = Player:new({_name = "Marie"})

function me:moveUp(this)
	print("moveUp")
	return true
end

function me:moveDown(this)
	print("moveDown")
	return true
end

function me:moveLeft(this)
	print("moveLeft")
	return true
end

function me:moveRight(this)
	print("moveRight")
	return true
end

function me:putBomb(this)
	print("putBomb")
	return true
end


Item = GameObject:new({_type = "Item"})

Bomb = Item:new({_type = "Bomb"})

function Bomb:getTimeBeforeExplosion(this)
	return 2
end
