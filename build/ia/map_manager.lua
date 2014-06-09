
require 'coord'

--[[
	A SAVOIR : 
	tous les intervalles min/max sont consideres comme inclus
		dans les valeurs possibles lors des verifications de coordonnees
]]

MapManager = {
	_map = nil,
	w,h,size = -1,-1,-1,
	min,max = nil,nil,

	_vision = {
		active = false,--si il n'y a pas de vision, on considere la map entierement
		size = -1,--la vision s'etend autant de chaque côté
		min,max = nil,nil,
		abs_min,abs_max = nil,nil,
		center = nil,
	}
}

function MapManager:init(w,h)
	local function _init_map()
		for i=1,MapManager.h do
		  for j=1,MapManager.w do
		    local curr_idx = MapManager:coord_to_idx(j,i)
		    self._map[curr_idx] = MapManager:create_case(curr_idx,i,j)
		    -- if (curr_idx > 61 and curr_idx < 69) or (curr_idx > 51 and curr_idx < 54) then
		      -- self._map[curr_idx].walkable = false end
		  end
		end
	end
	self._map = {}
	self.w, self.h = w, h
	self.size = self.w * self.h
	self.min = Coord:new(1,1)
	self.max = Coord:new(w,h)
	self:set_vision(self.max / self.min, self.size)
	_init_map()
	print("init map2D of size "..self.size.." (w = "..self.w.." and h = "..self.h..")")
end


-- * VISION *


function MapManager:activate_vision() self._vision.active = true end
function MapManager:desactivate_vision() self._vision.active = false end

--[[ center must have been created by Coord:new(x,y)
		size is a number ]]
function MapManager:set_vision(center, size)
	self._vision.center = center
	self._vision.size = size
	self._vision.abs_min = center - size
	self._vision.abs_max = center + size
	self._vision.min = Coord:max_filter(self._vision.abs_min, self.min)
	self._vision.max = Coord:min_filter(self._vision.abs_max, self.max)
end
function MapManager:set_vision_activate(center, size)
	self:set_vision(center, size)
	self:activate_vision()
end
function MapManager:set_vision_with_direction(center, direction, radius)
	local r = radius or -1
	Helper:to_implement()
end
function MapManager:set_vision_activate_with_direction(center, direction, radius)
	local r = radius or -1
	Helper:to_implement()
end


-- * COORDINATES *

-- return true if x and y are valids coordinates in the map
function MapManager:check_coord(x,y)
	local function _check_vision(pos)
		return pos >= self._vision.min and pos <= self._vision.max end
	local function _check_map(pos)
		return pos >= self.min and pos <= self.max end
	local pos = Coord:new(x,y)
	return _check_vision(pos)
	-- return self._vision.active and _check_vision(pos) or _check_map(pos)
end

-- return true if idx is a valid index in the map
-- function MapManager:check_idx(idx)
-- 	return idx > 0 and idx <= self.size
-- end

function MapManager:coord_to_idx(x,y)
	-- debug_print(debug.traceback())
	local idx = (y - 1) * self.w + x
	-- debug_print("coord_to_idx : i="..idx.." x="..x.." y="..y)
	return idx
end

-- retourne x,y
function MapManager:idx_to_coord(idx)
	local x = idx % self.w
	local y = math.ceil(idx / self.w) --+ 1
	-- debug_print("idx_to_coord : i="..idx.." x="..x.." y="..y)
	return x,y
end


-- * CASE/ACCESS *

function MapManager:create_case(curr_idx, i,j)
	local case = {}
	case.idx = curr_idx
	case.walkable = not Helper:are_objects_in_case(map,i,j,nil)
	case.status = Tags:v("unknown")--/open/closed
	case.parent = -1--idx du parent
	case.x,case.y = j,i
	case.g,case.h,case.f = 0,0,0
	return case
end
function MapManager:clean_map()
	-- use iter() ?
  for i=1,MapManager.h do
    for j=1,MapManager.w do
      local curr_idx = MapManager:coord_to_idx(j,i)
      local case = self._map[curr_idx]
     	case.status = Tags:v("unknown")
     	case.parent = -1
		case.g,case.h,case.f = 0,0,0
    end
  end
end

function MapManager:get_case(i)
	if i <= 0 or i > self.size then
		Helper:warning("get_case : idx="..i.." is outside the map")
	end
	return self._map[i]
end
-- function MapManager:set_case(i, case)
-- 	-- TODO : check i
-- 	return self._map[i]
-- end
function MapManager:iter()
	local function _iter(min, max)
		local i = min.y
		local j = min.x
		return function ()
			j = j + 1
			if j == max.x then
				i = i + 1
				j = min.x
			end
			if i <= max.y then return self:get_case(self:coord_to_idx(j,i)) end
		end
	end
	return _vision.active
		and _iter(self._vision.min, self._vision.max)
		or _iter(self.min, self.max)
end


-- * MAP ALTERATIONS *

-- the parameter is a tag value
function MapManager:make_type_unwalkable(type)
	Helper:to_implement()
end
-- explode all bombs in vision and put "future_fire" in map
function MapManager:preview_bomb_explosion()
	Helper:to_implement()
end
