
require 'api'
require 'tags'

Helper = {}

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


-- * OBJECTS_HELPER *

function Helper:get_my_coord()
	return Coord:new(me:getX(), me:getY())
end

function Helper:are_objects_in_case(x,y,type)
	local case = map:get(x,y)
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
function Helper:get_objects_from_case(x,y,type,objects)
	local o = objects or {}
	local case = map:get(x,y)
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
function Helper:are_objects_in_front(type,x,y,direction)
	local dir = direction or 0
	self:to_implement()
	return false
end
function Helper:get_objects_in_front(type,x,y,direction)
	local dir = direction or 0
	self:to_implement()
	return nil
end


-- * BOMB_HELPER *

-- TODO: calculer le rayon en fonction du temps de la bombe ou de son etendu

function Helper:is_place_safe()
	-- TODO : checker les previews a la place ?
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
