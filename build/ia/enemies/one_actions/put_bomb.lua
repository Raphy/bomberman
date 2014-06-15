require 'actions'

function initialization()
	Helper:debug_print("\n\nPUT_BOMB) initialization")
	Helper:initialization_base(10, 10)
end

-- DEBUG = 0
-- DEBUG_MAX = 100

-- active_debug = true

local first = 0

function play()
--   if DEBUG == DEBUG_MAX then
		Helper:debug_print("\n\nPUT_BOMB) play")
		MapManager:update()
		if first == 0 then
			Actions:place_bomb()
			first = 1
		else Actions:avoid_bomb()
		end
--     DEBUG = 0
--   end
--   DEBUG = DEBUG + 1
end
