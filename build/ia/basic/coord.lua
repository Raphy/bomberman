
--[[
	A SAVOIR : 
	'+' permet d'additionner une valeur à des coordonnees
	'-' permet de soustraire une valeur à des coordonnees
	'*' permet d'additionner 2 jeux de coordonnees ensemble
	'/' permet de diviser 2 jeux de coordonnees ensemble
	'<' '<=' '>' '>=' permettent de comparer les x ET y de 2 jeux de coordonnees
	les transitions coord <=> direction ne fontionnent que sur des cases adjacentes !
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
				return lhs.x <= rhs.x and lhs.y <= rhs.y
			end,
}

Coord = {
	_is_in_direction = nil,
	_direction_diff = nil,
}

function Coord:init()
	self._is_in_direction = {
		["up"] = function(c1,c2) return c1.x == c2.x and c1.y > c2.y end,
		["down"] = function(c1,c2) return c1.x == c2.x and c1.y < c2.y end,
		["left"] = function(c1,c2) return c1.x > c2.x and c1.y == c2.y end,
		["right"] = function(c1,c2) return c1.x < c2.x and c1.y == c2.y end,
	}
	self._direction_diff = {
		["up"] = self:new(0,-1),
		["down"] = self:new(0,1),
		["left"] = self:new(-1,0),
		["right"] = self:new(1,0),
	}
end
function Coord:new(x,y)
	local o = {x=x,y=y}
	setmetatable(o, coord_mt)
	return o
end
function Coord:cpy(rhs)
	local o = {x=rhs.x,y=rhs.y}
	setmetatable(o, coord_mt)
	return o
end

function Coord:are_adjacents(c1,c2)
	return abs(c1.x - c2.x) <= 1 and abs(c1.y - c2.y) <= 1
end

function Coord:to_direction(c1,c2)
	local function _check_dir(dir_value,c1,c2)
		local dir_key = Tags:k(dir_value)
		assert(dir_key == "up" or dir_key == "down" or dir_key == "left" or dir_key == "right", "bad direction key")
		if self._is_in_direction[dir_key](c1,c2) then
			return dir_key end
		if dir_value == Tags:v("right") then
			Helper:warning("can't find direction, maybe cases aren't adjacents.")
			return "right" end
		return _check_dir(dir_value + 1,c1,c2)
	end
	assert(c1 ~= c2)
	return _check_dir(Tags:v("up"),c1,c2)
end
function Coord:from_direction(c1,dir,radius)
	assert(dir == "left" or dir == "right" or dir == "up" or dir == "down")
	local r = radius or 1
	local diff = Coord:cpy(self._direction_diff[dir])
	diff.x, diff.y = (diff.x * r),(diff.y * r)
	return c1 * diff
end

function Coord:apply_to_all_directions(f)
	local function _apply(dir_v)
		f(Tags:k(dir_v))
		if dir_v == Tags:v("right") then
			return end
		_apply(dir_v + 1)
	end
	_apply(Tags:v("up"))
end

function Coord:min_filter(c1, c2)
	local function _min(v1,v2) return v1 <= v2 and v1 or v2 end
	return Coord:new(_min(c1.x,c2.x),_min(c1.y,c2.y))
end
function Coord:max_filter(c1, c2)
	local function _max(v1,v2) return v1 >= v2 and v1 or v2 end
	return Coord:new(_max(c1.x,c2.x),_max(c1.y,c2.y))
end

function Coord:unpack(c) return c.x, c.y end
