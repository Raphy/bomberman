require 'actions'
require 'state'
require 'state_machine'

-- * BEGIN_STATE *

BeginState = State:new("begin_state")

function BeginState:action()
	Helper:debug_print("action : ".."begin_state")
end

BeginState.pre_conditions = {
	{ function()
		return true end,
		"push", "wait_state", },
}

-- * WAIT_STATE *

WaitState = State:new("wait_state")

function WaitState:action()
	Helper:debug_print("action : ".."wait_state")
	Actions:wait()
end

WaitState.pre_conditions = {
	{ function()
		return Helper:is_place_dangerous() end,
		"push", "avoid_bomb_state", },
}

-- * AVOID_BOMB_STATE *

AvoidBombState = State:new("avoid_bomb_state")

function AvoidBombState:action()
	Helper:debug_print("action : ".."avoid_bomb_state")
	Actions:avoid_bomb()
end

AvoidBombState.pre_conditions = {
	{ function()
		return Helper:is_place_safe() end,
		"pop", },
}


StateList = {
	["begin_state"] = BeginState,
	["wait_state"] = WaitState,--a copier dans StateList
	["avoid_bomb_state"] = AvoidBombState,--a copier dans StateList
}

function initialization()
	Helper:debug_print("\n\nIA_COWARD) initialization")
	Helper:initialization_base(10, 5)
	StateMachine:init(3)
end

-- function play()
-- 	Helper:debug_print("\n\nIA_COWARD) play")
-- 	StateMachine:play()
-- end

DEBUG = 0
DEBUG_MAX = 100

active_debug = true

function play()
  if DEBUG == DEBUG_MAX then
    MapManager:update()
	Helper:debug_print("\n\nIA_COWARD) play")
    StateMachine:play()
    DEBUG = 0
  end
  DEBUG = DEBUG + 1
  -- Helper:debug_print("\n\nIA_SIMPLE) play")
end
