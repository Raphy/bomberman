
require "coord"

--[[
	A SAVOIR : 
	tous les intervalles min/max sont consideres comme inclus
		dans les valeurs possibles lors des verifications de coordonnees
	!! au moment d'interroger la map de l'api, soustraire de 1 chaque coordonee !!
]]

MapManager = {
	_map = nil,
	w,h,size = -1,-1,-1,
	min,max = nil,nil,

	_vision = {
		active = false,
		size = -1,
		min,max = nil,nil,
		abs_min,abs_max = nil,nil,
		center = nil,
	},
	_perso_vision = {
		size = -1,
		min,max = nil,nil,
		abs_min,abs_max = nil,nil,
		center = nil,
	},
}

function MapManager:init(w,h, vision_size)
	self._map = {}
	self.w, self.h = w, h
	self.size = self.w * self.h
	self.min = Coord:new(1,1)
	self.max = Coord:new(w,h)
	self:set_vision(Helper:get_my_coord(), vision_size or 2)
	self:set_vision(Helper:get_my_coord(), vision_size or 2, true)
	for i,j in self:iter_ij() do
		local curr_idx = MapManager:coord_to_idx(j,i)
	   self._map[curr_idx] = MapManager:create_case(curr_idx,i,j)
	end
end

function MapManager:update()
	self:set_vision(Helper:get_my_coord(), self._vision.size, true)
	for i,j in self:iter_ij() do
		local curr_idx = MapManager:coord_to_idx(j,i)
	   self._map[curr_idx] = MapManager:create_case(curr_idx,i,j)
	end
end

-- * VISION *


--[[ private ]]
function MapManager:get_vision()
	if self._vision.active then
		return self._vision
	else
		return self._perso_vision
	end
end

function MapManager:activate_vision() self._vision.active = true end
function MapManager:desactivate_vision() self._vision.active = false end
function MapManager:set_vision(center, size, modify_perso)
	local function _set(vision)
		vision.center = center
		vision.size = size
		vision.abs_min = center - size
		vision.abs_max = center + size
		vision.min = Coord:max_filter(vision.abs_min, self.min)
		vision.max = Coord:min_filter(vision.abs_max, self.max)
	end
	if modify_perso then _set(self._perso_vision) else _set(self._vision) end
end
function MapManager:set_vision_activate(center, size)
	self:set_vision(center, size)
	self:activate_vision()
end


-- * COORDINATES *

function MapManager:check_coord(x,y)
	local vision = self:get_vision()
	local pos = Coord:new(x,y)
	return pos >= vision.min and pos <= vision.max
end
function MapManager:coord_to_idx(x,y)
	local idx = (y - 1) * self.w + x
	return idx
end
function MapManager:idx_to_coord(idx)
	local x = idx % self.w
	local y = math.ceil(idx / self.w)
	return x,y
end


-- * CASE/ACCESS *
local case_mt =
{
	__lt = function (lhs, rhs)
				return lhs.g < rhs.g
			end,
	__eq = function (rhs)
				local new_case = rhs
				setmetatable(new_case, getmetatable(rhs))
				return new_case
			end,
}

function MapManager:create_case(curr_idx, i,j)
	assert(self:check_coord(j,i))

	local case = {}
	setmetatable(case, case_mt)
	case.idx = curr_idx
	case.x,case.y = j,i
	case.walkable = true
	case.previews = List:new("case_previews_"..curr_idx)
	case.marks = List:new("case_marks_"..curr_idx)
	case.status = "unknown"--/open/closed
	case.parent = -1--idx du parent
	case.g,case.h,case.f = 0,0,0
	return case
end
function MapManager:clean_map()
	for case in self:iter() do
		List:clear(case.previews)
		List:clear(case.marks)
     	case.status = "unknown"
     	case.parent = -1
		case.g,case.h,case.f = 0,0,0
	end
end

function MapManager:get_case(i)
	assert(i ~= nil, "get_case expect an index")
	i = math.ceil(i)
	if i <= 0 or i > self.size then
		Helper:warning("get_case : idx="..i.." is outside the map")
	end
	return self._map[i]
end
function MapManager:iter()
	local function _iter(min, max)
		local i,j = min.y, min.x - 1
		return function ()
			j = j + 1
			if j > max.x then i = i + 1; j = min.x end
			if i <= max.y then return self:get_case(self:coord_to_idx(j,i)) end
		end
	end
	local vision = self:get_vision()
	return _iter(vision.min, vision.max)
end
--[[ private ]]
function MapManager:iter_ij()
	local function _iter(min, max)
		local i,j = min.y, min.x - 1
		return function ()
			j = j + 1
			if j > max.x then i = i + 1; j = min.x end
			if i <= max.y then return i,j end
		end
	end
	local vision = self:get_vision()
	return _iter(vision.min, vision.max)
end

-- * MAP ALTERATIONS *

function MapManager:make_type_unwalkable(type)
	for case in self:iter() do
		if string.find(type, "preview") ~= nil then
			case.walkable = List:empty(case.previews)
		else
			case.walkable = not Helper:are_objects_in_case(case.x,case.y,type)
		end
	end
end
