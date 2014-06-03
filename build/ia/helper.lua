
require 'api'

  -- The scripts is provided by the following objects:
  -- Variable "me" (API::Me) represents the player by this script
  -- Variable "map" (API::Map) represents the game map
-- print(map:get(1,1))


TagsList = { "up","down","left","right",
				"player","me","bomb","item",
				"open","closed","unknown" }
Tags = {}
for i,v in ipairs(TagsList) do
	Tags[v] = i
end

Helper = {
	w = 10,-- TODO : initialiser dans init
	h = 10,
}

function Helper:coord_to_idx(x,y)
	-- print(debug.traceback())
	local idx = y * self.w + x
	-- print("coord_to_idx : i="..idx.." x="..x.." y="..y)
	return idx
end

-- retourne x,y
function Helper:idx_to_coord(idx)
	local x = idx % self.w
	local y = math.floor(idx / self.w)
	-- print("idx_to_coord : i="..idx.." x="..x.." y="..y)
	return x,y--TODO : verifier les formules
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
	while i < Helper.h do
		local j = 0
		while j < Helper.w do
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
