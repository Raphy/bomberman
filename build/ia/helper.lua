
require 'api'

  -- The scripts is provided by the following objects:
  -- Variable "me" (API::Me) represents the player by this script
  -- Variable "map" (API::Map) represents the game map
-- print(map:get(1,1))


TagsList = { "up","down","left","right","player","me","bomb","item","open","closed","unknown" }
Tags = {}
for i,v in ipairs(TagsList) do
	Tags[v] = i
end

Helper = {
	w = 100,-- TODO : initialiser dans init
	h = 100,
}

function Helper:coord_to_idx(x,y)
	return (x*self.w + y)
end

function Helper:idx_to_coord(idx)
	return (idx % self.w + self.h),(idx / self.w)--TODO : verifier les formules
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
	while i < Y do
		local j = 0
		while j < X do
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
