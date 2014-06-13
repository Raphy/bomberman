
require 'actions'
require 'state'
require 'state_machine'

-- * BEGIN_STATE *

BeginState = State:new("begin_state")

function BeginState:action()
	Helper:debug_print("action : ".."begin_state")
	--corps
end

BeginState.pre_conditions = {
	--conditions
}

StateList = {
  ["begin_state"] = BeginState
}

active_debug = true
active_debug_list = false

function initialization()
	Helper:debug_print("\n\nIA_SIMPLE) initialization")
	Helper:initialization_base(20, 2)
	StateMachine:init(1)

	MapManager:update()
	Actions:get_closer_of_one_enemy()
end

DEBUG = 0
DEBUG_MAX = 100

function play()
	if DEBUG == DEBUG_MAX then
		MapManager:update()
		StateMachine:play()
		DEBUG = 0
	end
	DEBUG = DEBUG + 1
	-- Helper:debug_print("\n\nIA_SIMPLE) play")
end
