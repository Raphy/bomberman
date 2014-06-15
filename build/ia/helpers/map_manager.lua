
require "coord"
require "case"

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
	unwalkables = nil,

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

function MapManager:debug_dump()
	if active_debug_walkable then
		for i=1,self.w do
			for j=1,self.h do
				local idx = self:xy_to_idx(j,i)
				local case = self._map[idx]
				print("case x,y",j,i,"walkable : ",case.walkable)
			end
			print("")
		end
	end
	return nil
end

-- * GENERAL *

function MapManager:init(w,h, vision_size)
	self._map = {}
	self.w, self.h = w, h
	self.size = self.w * self.h
	self.min = Coord:new(1,1)
	self.max = Coord:new(w,h)
	self.unwalkables = List:new("unwalkables")
	self:set_vision(Helper:get_my_coord(), vision_size or 2)
	self:set_vision(Helper:get_my_coord(), vision_size or 2, true)
	for i,j in self:complete_iter_ij() do
		local curr_idx = MapManager:xy_to_idx(j,i)
	   self._map[curr_idx] = Case:create_case(curr_idx,i,j)
	end
	self:make_type_unwalkable("Wall")
	self:make_type_unwalkable("Box")
end
function MapManager:update()
	self:set_vision(Helper:get_my_coord(), self._vision.size, true)
	self:clean_map()
	self:update_walkables()
	-- for i,j in self:iter_ij() do
	-- 	local curr_idx = MapManager:xy_to_idx(j,i)
	--    self._map[curr_idx] = Case:create_case(curr_idx,i,j)
	-- end
end
function MapManager:clean_map()
	self:for_each_case(function(case) Case:clean_case(case) end)
end
function MapManager:clean_previews()
	self:for_each_case(function(case) Case:clean_previews(case) end)
end
function MapManager:clean_marks()
	self:for_each_case(function(case) Case:clean_marks(case) end)
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
	self:set_vision(center, size, false)
	self:activate_vision()
end


-- * COORDINATES *

function MapManager:check_coord(coo)
	local vision = self:get_vision()
	return coo >= vision.min and coo <= vision.max
end
function MapManager:coord_to_idx(coo)
	return self:xy_to_idx(Coord:unpack(coo))
end
function MapManager:idx_to_coord(coo)
	return self:idx_to_xy(Coord:unpack(coo))
end

function MapManager:check_xy(x,y)
	return self:check_coord(Coord:new(x,y))
end
function MapManager:xy_to_idx(x,y)
	local x,y = math.floor(x),math.floor(y)
	local idx = (y - 1) * self.w + x
	return idx
end
function MapManager:idx_to_xy(idx)
	local x = idx % self.w
	local y = math.ceil(idx / self.w)
	return x,y
end


-- * CASE/ACCESS *


function MapManager:get_case(i)
	i = math.ceil(i)
	-- if i <= 0 or i > self.size then
	-- 	Helper:warning("get_case : idx="..i.." is outside the map")
	-- end
	return self._map[i]
end
function MapManager:iter()
	local function _iter(min, max)
		local i,j = min.y, min.x - 1
		return function ()
			j = j + 1
			if j > max.x then i = i + 1; j = min.x end
			if i <= max.y then return self:get_case(self:xy_to_idx(j,i)) end
		end
	end
	local vision = self:get_vision()
	return _iter(vision.min, vision.max)
end
function MapManager:for_each_case(f)
	for case in self:iter() do f(case) end
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
function MapManager:complete_iter_ij()
	local function _iter(min, max)
		local i,j = min.y, min.x - 1
		return function ()
			j = j + 1
			if j > max.x then i = i + 1; j = min.x end
			if i <= max.y then return i,j end
		end
	end
	return _iter(self.min, self.max)
end

-- * MAP ALTERATIONS *

function MapManager:make_type_unwalkable(type)
	if not List:is_elem_in_list(self.unwalkables, type) then
		List:push(self.unwalkables, type) end
	self:for_each_case(function(case) Case:make_type_unwalkable(case,type) end)
end
function MapManager:make_type_walkable(type)
	if List:is_elem_in_list(self.unwalkables, type) then
		List:remove(self.unwalkables, type) end
	self:update_walkables()
end
function MapManager:update_walkables()
	self:for_each_case(function(case)
		case.walkable = true
		for unwalkable in List:iter(self.unwalkables) do
			Case:make_type_unwalkable(case,unwalkable) end
		end)
end
