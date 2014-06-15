require 'actions'

function initialization()
	Helper:debug_print("\n\nSEARCH_BOX) initialization")
	Helper:initialization_base(10, 10)
end

DEBUG_MAX = 100
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
		-- print("Actions:get_closer_of_obj(\"Player\")")
		Actions:get_closer_of_obj("Box")
    -- DEBUG = 0
  -- end
  -- DEBUG = DEBUG + 1
end
