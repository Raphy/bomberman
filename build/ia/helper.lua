
require 'api'
require 'tags'

Helper = {}

function Helper:initialization_base(repeat_max, vision_size)
	math.randomseed(os.time())
	Coord:init()
	MapManager:init(100,100, vision_size)
	Actions:init(repeat_max)
end

-- * TIME_HELPER *

function Helper:get_current_time()
	self:to_implement()
	return 0
end
function Helper:get_elapsed_time(origin_time)
	self:to_implement()
	return 0
end

-- * DEV_HELPER *

function Helper:warning(msg)
	print("WARNING...")
	print(debug.traceback())
	print("...WARNING : "..msg)
end
function Helper:to_implement()
	print("ERROR : FUNCTION NOT IMPLEMENTED")
	print(debug.traceback())
end
function Helper:to_override()
	print("WARNING : this method should be override")
	print(debug.traceback())
end
function Helper:debug_print(msg)
	-- print("DEBUG : "..msg)
end
function Helper:debug_dump_list(list)
	self:debug_print("DUMP ",list._name," : ")
	for elem in List:iter_case(list) do
		self:debug_print(elem.idx)
	end
	self:debug_print("...DUMP END")
end

-- * OBJECTS_HELPER *

function Helper:get_my_coord()
	return Coord:new(me:getX(), me:getY())
end

function Helper:are_objects_in_case(x,y,type)
	local case = map:get(x,y,1)
	if x == 5.0 and y == 5.0 then return true end
	-- local case = map:get(5.0,5.0)
	if case == nil then
		return false end
	for _,obj in pairs(case) do
		-- print("parcours enemy")
		-- if type == nil or type == obj:getType() then
			return true --end
	end
	return false
end
function Helper:are_objects_in_case_except(x,y,type)
	assert(type ~= nil, "are_objects_in_case_except : type expected")
	do return false end--debug
	local case = map:get(x,y,1)
	if x == 5.0 and y == 5.0 then return true end
	-- local case = map:get(5.0,5.0)
	if case == nil then
		return false end
	for _,obj in pairs(case) do
		if type ~= obj:getType() then
			return true end
	end
	return false
end
function Helper:get_objects_from_case(x,y,type,objects)
	local o = objects or {}
	local case = map:get(x,y,1)
	if case == nil then
		return nil end
	for _,obj in pairs(case) do
		if type == nil or type == obj:getType() then
			table.insert(o, obj) end
	end
	return o
end

function Helper:get_all_objects(type)
	self:debug_print("get all objects of type "..type)
	local o = {}
	for case in MapManager:iter() do
		o = self:get_objects_from_case(case.x,case.y,type,o)
	end
	return o
end
function Helper:are_objects(type)
	self:debug_print("get all objects of type "..type)
	for case in MapManager:iter() do
		if self:are_objects_in_case(case.x,case.y,type,o) then
			return true end
	end
	return false
end

function Helper:are_objects_around(type,x,y,radius)
	local r = radius or 1
	local vision_state = MapManager._vision.active
	MapManager:set_vision_activate(Coord:new(x,y), r)
	local found = self:are_objects(type)
	if not vision_state then MapManager:desactivate_vision() end
	return found
end
function Helper:get_objects_around(type,x,y,radius)
	local r = radius or 1
	local vision_state = MapManager._vision.active
	MapManager:set_vision_activate(Coord:new(x,y), r)
	local o = self:get_all_objects(type)
	if not vision_state then MapManager:desactivate_vision() end
	return o
end
-- function Helper:are_objects_in_front(type,x,y,direction)
-- 	local dir = direction or 0
-- 	self:to_implement()
-- 	return false
-- end
-- function Helper:get_objects_in_front(type,x,y,direction)
-- 	local dir = direction or 0
-- 	self:to_implement()
-- 	return nil
-- end


-- * BOMB_HELPER *

local function is_case_safe(case)
	return not Helper:are_objects_in_case_except(case.x,case.y,"enemy")
		and List:empty(case.previews)
end

-- TODO: calculer le rayon en fonction du temps de la bombe ou de son etendu

function Helper:is_place_safe()
	-- TODO : checker les previews en plus ?
	return not Helper:are_objects_around("bomb",me:getX(),me:getY(),3)
end

function Helper:get_dangerous_cases_around_bomb(bomb_position)
	local radius = 2
	-- MapManager:set_vision_activate(bomb_position, radius)
	-- MapManager:preview_bomb_explosion()
	-- return self:get_objects_around("preview_fire",Coord:unpack(bomb_position),radius)
	--desactivate vision ?
	self:to_implement()
	return false
end

function Helper:get_nearest_safe_case(bomb_position)
	local radius = 2
	MapManager:set_vision_activate(bomb_position, radius)
	MapManager:preview_bomb_explosion()
	-- execute dijkstra sur type case vide
	self:to_implement()
	return nil
	-- return self:get_objects_around("bomb",Coord:unpack(bomb_position),radius)
end

function Helper:clean_preview()
	for case in MapManager:iter() do
		List:clear(case.previews)
	end
end
function Helper:preview_bomb(bomb_coord)
	print("debut preview bomb..........")
	local function _preview_fire(coord)
		local x,y = Coord:unpack(coord)
		if not MapManager:check_coord(x,y) then
			return false end
		local case = MapManager:get_case(MapManager:coord_to_idx(x,y))-- faire une methode pour ça ?
		self:debug_print("preview_fire on x = "..x.." y = "..y)
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

function Helper:mark_all_safe_cases()
	for case in MapManager:iter() do
		if is_case_safe(case) and not List:is_elem_in_list(case.marks, "safe_place") then
			List:push_back(case.marks, "safe_place")
		end
	end
end
-- explode all bombs in vision and put "preview_fire" in map
function Helper:preview_all_bombs()
	for case in MapManager:iter() do
		if self:are_objects_in_case(case.x,case.y,"bomb")
			or List:is_elem_in_list(case.previews, "preview_bomb") then
				self:preview_bomb(Coord:new(case.x,case.y))
		end
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
