base_path = './build/ia/'
package.path = base_path .. '?.lua;' .. package.path
package.path = base_path .. 'enemies/?.lua;' .. package.path
package.path = base_path .. 'enemies/one_actions/?.lua;' .. package.path
package.path = base_path .. 'basic/?.lua;' .. package.path
package.path = base_path .. 'helpers/?.lua;' .. package.path

DEBUG = 0
DEBUG_MAX = 50
active_debug = false
active_debug_list = false
active_debug_objects = false
active_debug_walkable = false


function initialization()
	return true
end
function play()
	return true
end

-- function initialization()
-- 	print("[IA] initialization")
-- end

-- function play()
--    if DEBUG >= DEBUG_MAX then
-- 		print("\n\n--------------------\n")
-- 		local my_x,my_y = me:getPosition()
-- 		-- local my_x,my_y = Helper:get_my_position()
-- 		-- print("[IA] getPosition -> ",my_x,my_y)

--   --  	local objects = map:get(my_x,my_y, 1, me)
-- 		-- print("[IA] tous  : ")
--   --  	_display_objects(objects)
--   --  	local objects = filter_objects(objects, my_x,my_y)
--   		local objects = Helper:map_get(my_x,my_y, 1)
-- 		print("[IA] filter : ")
--    	_display_objects(objects)
-- 		print("\n\n--------------------\n")
--    	DEBUG = 0
--   end
--   DEBUG = DEBUG + 1
-- end


-- -- require "ia_state"
-- require "ia_stalker"
-- require "ia_seeker"
-- -- require "ia_intro"
-- -- require "ia_simple"
-- require "ia_coward"
-- -- require "ia_intelligent_coward"
-- require "search_box"
-- require "avoid_bomb"
-- require "test_dangerous"

-- -- require "ia_unit_test"
