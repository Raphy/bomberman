require 'actions'

function initialization()
	Helper:initialization_base(10, 3)
end

DEBUG_MAX = 1
DEBUG = DEBUG_MAX

active_debug = true

local function _debug_dump_objects(objects)
	for _,obj in ipairs(objects) do
		print(obj:getType())
	end
end

function play()
  -- if DEBUG == DEBUG_MAX then
		MapManager:update()
	 -- if Helper:is_place_dangerous() == true then print("but should match !!!!") end
	 local x,y = Helper:get_my_position()
	if Helper:are_objects_around("Bomb",x,y,3) == true then
 		print("but should match !!!!") end
	if Helper:are_objects_in_case(x,y,"Bomb") == true then
 		print("but should REALLY match !!!!") end
 	local objects = Helper:get_objects_around("Bomb",x,y,3)
 	if objects then _debug_dump_objects(objects) end
     -- DEBUG = 0
  -- end
  -- DEBUG = DEBUG + 1
end
