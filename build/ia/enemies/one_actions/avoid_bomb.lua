require 'actions'

function initialization()
	Helper:debug_print("\n\nSEARCH_BOX) initialization")
	Helper:initialization_base(10, 2)
end

function play()
		MapManager:update()
		Actions:avoid_bomb()
end
