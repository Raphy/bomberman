require 'actions'

function initialization()
	Helper:debug_print("\n\nPUT_BOMB) initialization")
	Helper:initialization_base(10, 10)
end

local first = 0

function play()
		Helper:debug_print("\n\nPUT_BOMB) play")
		MapManager:update()
		if first == 0 then
			Actions:place_bomb()
			first = 1
		else Actions:avoid_bomb()
		end
end
