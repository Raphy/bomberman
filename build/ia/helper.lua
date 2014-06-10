
require 'api'
require 'tags'

  -- The scripts is provided by the following objects:
  -- Variable "me" (API::Me) represents the player by this script
  -- Variable "map" (API::Map) represents the game map
-- print(map:get(1,1))

Helper = {}

function Helper:warning(msg)
	print("WARNING : "..msg)
	print(debug.traceback())
end
function Helper:to_implement()
	print("ERROR : FUNCTION NOT IMPLEMENTED")
	-- print(debug.traceback())
end
function Helper:debug_print(msg)
	print("DEBUG : "..msg)
end

function Helper:are_objects_in_case(map,i,j,type)
	local o = {}
	local case = map:get(i,j)
	-- for obj in case do
	-- 	if type == nil or type == obj:getType() then
	-- 		o:insert(obj)
	-- 	end
	-- end
	-- return (#o == 0)	
	return false
end

function Helper:get_objects_from_case(map,i,j,type,objects)
	local o = objects or {}
	local case = map:get(i,j)
	-- for obj in case do
	-- 	if type == nil or type == obj:getType() then
	-- 		o:insert(obj)
	-- 	end
	-- end
	return o
end

function Helper:get_all_object(type)
	print("get all objects of type " .. type)
	local objects = {}
	local i = 0
	while i < MapManager.h do
		local j = 0
		while j < MapManager.w do
			Helper:get_objects_from_case(map,i,j,objects)
			j = j + 1
		end
		i = i + 1
	end
end

function Helper:are_objects_around(type,x,y,radius)
	local r = radius or 1
	return false
end

function Helper:get_objects_around(type,x,y,radius)
	local r = radius or 1
	return nil
end

function Helper:are_objects_in_front(type,x,y,direction)
	local dir = direction or 0
	return false
end

function Helper:get_objects_in_front(type,x,y,direction)
	local dir = direction or 0
	return nil
end

-- * BOMB_HELPER *

-- TODO: calculer le rayon en fonction du temps de la bombe

function Helper:is_place_safe()
	Helper:to_implement()
  -- return Helper:are_objects_around(Tags:v("bomb"),me:getX(),me:getY(),check_radius)
end

function Helper:get_dangerous_cases_around_bomb(bomb_position)
	local radius = 2
	MapManager:set_vision_activate(bomb_position, radius)
	return self:get_objects_around(Tags:v("bomb"),Coord:unpack(bomb_position),radius)
	--le tag n'est pas bomb !
end

function Helper:get_nearest_safe_case(bomb_position)
	local radius = 2
	MapManager:set_vision_activate(bomb_position, radius)
	return self:get_objects_around(Tags:v("bomb"),Coord:unpack(bomb_position),radius)
	--le tag n'est pas bomb !
end
