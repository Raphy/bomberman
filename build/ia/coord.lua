
--[[
	A SAVOIR : 
	'+' permet d'additionner une valeur à des coordonnees
	'-' permet de soustraire une valeur à des coordonnees
	'*' permet d'additionner 2 jeux de coordonnees ensemble
	'/' permet de diviser 2 jeux de coordonnees ensemble
	'<' '<=' '>' '>=' permettent de comparer les x ET y de 2 jeux de coordonnees
]]

--[[
TODO : test '>' et '>=' pour savoir exactement comment lua inverse les operateurs !
]]

local coord_mt =
{
	__add = function (lhs, rhs)
				local o = { x = (lhs.x + rhs),
								y = (lhs.y + rhs) }
				setmetatable(o,getmetatable(lhs))
				return o
			end,
	__sub = function (lhs, rhs)
				local o = { x = (lhs.x - rhs),
								y = (lhs.y - rhs) }
				setmetatable(o,getmetatable(lhs))
				return o
			end,

	__mul = function (lhs, rhs)
				local o = { x = (lhs.x + rhs.x),
								y = (lhs.y + rhs.y) }
				setmetatable(o,getmetatable(lhs))
				return o
			end,
	__div = function (lhs, rhs)
				local o = { x = (lhs.x - rhs.x),
								y = (lhs.y - rhs.y) }
				setmetatable(o,getmetatable(lhs))
				return o
			end,
	__lt = function (lhs, rhs)
				return lhs.x < rhs.x and lhs.y < rhs.y
			end,
	__le = function (lhs, rhs)
				print(debug.traceback())
				return lhs.x <= rhs.x and lhs.y <= rhs.y
			end,
	-- __tostring = function (c)
	-- 	return c.x..c.y
	-- end
}

Coord = {
	_is_in_direction = nil,
	_direction_diff = nil,
}

function Coord:init()
	_is_in_direction = {
		["left"] = function(c1,c2) return c1.x > c2.x and c1.y == c2.y end,
		["right"] = function(c1,c2) return c1.x < c2.x and c1.y == c2.y end,
		["up"] = function(c1,c2) return c1.x == c2.x and c1.y > c2.y end,
		["down"] = function(c1,c2) return c1.x == c2.x and c1.y < c2.y end,
	}
	_direction_diff = {
		["left"] = Coord:new(-1,0),
		["right"] = Coord:new(1,0),
		["up"] = Coord:new(0,-1),
		["down"] = Coord:new(0,1),
	}
end
function Coord:new(x,y)
	local o = {x=x,y=y}
	setmetatable(o, coord_mt)
	return o
end

-- TODO : gerer les diagonales ?
function Coord:to_direction(c1,c2)
	local function _check_dir(dir_value,c1,c2)
		local dir_key = DirectionTags:k(dir_value)
		if dir_value == 4 -- #DirectionTags
			then return self._is_in_direction[dir_key](c1,c2)
								and dir_key
			else return self._is_in_direction[dir_key](c1,c2)
								and _check_dir(dirTag + 1)
		end
	end

	assert(c1 ~= c2)
	return _check_dir(1,c1,c2)
	-- return self._is_in_direction["left"] and "left"
	-- 	or self._is_in_direction["right"] and "right"
	-- 	or self._is_in_direction["up"] and "up"
	-- 	or self._is_in_direction["down"] and "down"
end
function Coord:from_direction(c1,dir)
	--isInTagsList with DirectionTags
	assert(dir == "left" or dir == "right" or dir == "up" or dir == "down")
	return c1 + self._direction_diff[dir]
end

function Coord:min_filter(c1, c2)
	local function _min(v1,v2) return v1 <= v2 and v1 or v2 end
	return Coord:new(_min(c1.x,c2.x),_min(c1.y,c2.y))
end
function Coord:max_filter(c1, c2)
	local function _max(v1,v2) return v1 >= v2 and v1 or v2 end
	return Coord:new(_max(c1.x,c2.x),_max(c1.y,c2.y))
end

-- function Coord:max(c1, c2) return c1 >= c2 and c1 or c2 end

function Coord:unpack(c) return c1.x, c1.y end

-- local toto = Coord:new(0,10)
-- local titi = Coord:new(1,1)

-- print("toto x y ",toto.x,toto.y)
-- print("titi x y ",titi.x,titi.y)

-- print("< ",(toto < titi))
-- print("<= ",(toto <= titi))
-- print("> ",(toto > titi))
-- print(">= ",(toto >= titi))

