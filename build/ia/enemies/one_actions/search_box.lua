require 'actions'

function initialization()
	Helper:debug_print("\n\nSEARCH_BOX) initialization")
	Helper:initialization_base(10, 10)
end

DEBUG = 0
DEBUG_MAX = 100

active_debug = true

function play()
  if DEBUG == DEBUG_MAX then
		MapManager:update()
		Helper:debug_print("\n\nSEARCH_BOX) play")
		Actions:get_closer_of_obj("Box")
    DEBUG = 0
  end
  DEBUG = DEBUG + 1
end
