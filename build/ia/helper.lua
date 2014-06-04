
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
function Helper:debug_print(msg)
	-- print("DEBUG : "..msg)
end

function Helper:areObjectsInCase(map,i,j,objType)
	local o = {}
	local case = map:get(i,j)
	-- for obj in case do
	-- 	if objType == nil or objType == obj:getType() then
	-- 		o:insert(obj)
	-- 	end
	-- end
	-- return (#o == 0)	
	return false
end

function Helper:getObjectsFromCase(map,i,j,objType,objects)
	local o = objects or {}
	local case = map:get(i,j)
	-- for obj in case do
	-- 	if objType == nil or objType == obj:getType() then
	-- 		o:insert(obj)
	-- 	end
	-- end
	return o
end

function Helper:getAllObject(objType)
	print("get all objects of type " .. objType)
	local objects = {}
	local i = 0
	while i < Map2D.h do
		local j = 0
		while j < Map2D.w do
			Helper:getObjectsFromCase(map,i,j,objects)
			j = j + 1
		end
		i = i + 1
	end
end

function Helper:areObjectsAround(objType,x,y,radius)
	local r = radius or 1
	return false
end

function Helper:getObjectsAround(objType,x,y,radius)
	local r = radius or 1
	return nil
end

function Helper:areObjectsInFront(objType,x,y,direction)
	local dir = direction or 0
	return false
end

function Helper:getObjectsInFront(objType,x,y,direction)
	local dir = direction or 0
	return nil
end
