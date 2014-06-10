
require 'coord'

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
	case.x,case.y = j,i
	case.walkable = true--not Helper:are_objects_in_case(j,i,"wall")
	case.previews = List:new("case_previews_"..curr_idx)
	case.status = "unknown"--/open/closed
	case.parent = -1--idx du parent
	case.g,case.h,case.f = 0,0,0
	return case
end
function MapManager:clean_map()
	-- use iter() ?
  for i=1,MapManager.h do
    for j=1,MapManager.w do
      local curr_idx = MapManager:coord_to_idx(j,i)
      local case = self._map[curr_idx]
     	case.status = "unknown"
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
-- TODO : tester iter pour etre sur qu'il va bien exactement de min a max inclus
function MapManager:iter()
	local function _iter(min, max)
		local i,j = min.y, min.x - 1
		return function ()
			j = j + 1
			if j > max.x then i = i + 1; j = min.x end
			if i <= max.y then return self:get_case(self:coord_to_idx(j,i)) end
		end
	end
	return self._vision.active
		and _iter(self._vision.min, self._vision.max)
		or _iter(self.min, self.max)
end


-- * MAP ALTERATIONS *
-- TODO : deplacer dans helper ?

-- TODO : se servir de cette methode pour init la map et choisir d'eviter murs, joueurs ...

-- the parameter is a tag
function MapManager:make_type_unwalkable(type)
	for case in self:iter() do
		if string.find(type, "preview") ~= nil then
			case.walkable = List:empty(case.previews)
		else
			case.walkable = not Helper:are_objects_in_case(case.x,case.y,type)
		end
	end
end

function MapManager:clean_preview()
	for case in self:iter() do
		List:clear(case.previews)
	end
end
function MapManager:preview_bomb(bomb_coord)
	print("debut preview bomb..........")
	-- verifier s'il y a bien une bombe a ces coordonnees ?
	local function _preview_fire(coord)
		local x,y = Coord:unpack(coord)
		if not self:check_coord(x,y) then
			return false end
		local case = self:get_case(self:coord_to_idx(x,y))-- faire une methode pour ça ?
		Helper:debug_print("preview_fire on x = "..x.." y = "..y)
		if not List:is_elem_in_list(case.previews, "preview_fire") then
			List:push_back(case.previews, "preview_fire") end
		return true
	end
	_preview_fire(bomb_coord)
	for radius=1,3 do -- radius max = celui de la bomb
		local function _call_preview(dir)
			_preview_fire(Coord:from_direction(bomb_coord, dir, radius))
		end
		Coord:apply_to_all_directions(_call_preview)
	end
	print("fin preview bomb..........")
end

-- explode all bombs in vision and put "preview_fire" in map
function MapManager:preview_all_bombs()
	for case in MapManager:iter() do
		if Helper:are_objects_in_case(case.x,case.y,"bomb")
			or List:is_elem_in_list(case.previews, "preview_bomb") then
				self:preview_bomb(Coord:new(case.x,case.y))
		end
	end

	--[[
	quelles cases sont affecté ?
	est ce qu'on met du feu aussi dans les murs ?
		(sachant que dans les murs incassables, ils ne pourront jamais aller normalement)
	comment on fait une preview ? copie complete ou seulement des cases affectes ?
		(sachant que ca modifie les cases de MapManager._map et peux fausser d'autres calculs exterieurs par la suite)
	ou alors clean la map juste apres ?
	comment on annule une preview ?
	]]
end
