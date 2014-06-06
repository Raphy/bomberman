
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
				return lhs.x <= rhs.x and lhs.y <= rhs.y
			end,
	-- __tostring = function (c)
	-- 	return c.x..c.y
	-- end
}

Coord = {}

function Coord:new(x,y)
	local o = {x=x,y=y}
	setmetatable(o, coord_mt)
	return o
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

