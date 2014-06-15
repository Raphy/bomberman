require 'actions'

function initialization()
	Helper:debug_print("\n\nSEARCH_BOX) initialization")
	Helper:initialization_base(10, 2)
end

DEBUG_MAX = 1
DEBUG = DEBUG_MAX

-- active_debug = true
-- active_debug_list = true

-- local function _get_obj(x,y)
-- 	print("Helper:get_objects_from_case(",x,y,")")
-- 	local boxes = Helper:get_objects_from_case(x,y)
-- 	for _,obj in ipairs(boxes) do
-- 		print(obj:getType())
-- 	end
-- end

function play()
	-- if DEBUG >= DEBUG_MAX then
		-- print("\n\n--------------------------\n")
		-- _get_obj(Helper:get_my_position())
		MapManager:update()
		Actions:avoid_bomb()
		-- print("\n\n--------------------------\n")
   	-- DEBUG = 0
  -- end
  -- DEBUG = DEBUG + 1
end
