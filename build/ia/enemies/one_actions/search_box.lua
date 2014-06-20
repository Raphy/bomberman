require 'actions'

function initialization()
	Helper:debug_print("\n\nSEARCH_BOX) initialization")
	Helper:initialization_base(10, 10)
end

function play()
		Actions:get_closer_of_obj("Box")
end
