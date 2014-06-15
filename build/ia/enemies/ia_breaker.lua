require 'actions'
require 'state'
require 'state_machine'

-- * BEGIN_STATE *

BeginState = State:new("begin_state")

function BeginState:action()
	Helper:debug_print("action : ".."begin_state")
	return true
end

BeginState.pre_conditions = {

}


-- * AVOID_BOMB_STATE *

AvoidBombState = State:new("avoid_bomb_state")

function AvoidBombState:action()
	Helper:debug_print("action : ".."avoid_bomb_state")
	return Actions:avoid_bomb()
end

AvoidBombState.pre_conditions = {
	{ function()
		return Helper:is_place_safe() end,
		"pop", },
}

AvoidBombState.post_conditions = {
	{ function()
		return Helper:is_place_safe() end,
		"pop", },
}

-- * BREAK_WALL_STATE *

BreakWallState = State:new("break_wall_state")

function BreakWallState:action()
	Helper:debug_print("action : ".."break_wall_state")
	return true
end

BreakWallState.pre_conditions = {
	{ function()
		return Helper:is_place_dangerous() end,
		"push", "avoid_bomb", },
}

BreakWallState.post_conditions = {

}




StateList = {
	["begin_state"] = BeginState,
	["break_wall_state"] = BreakWallState,--a copier dans StateList
	["avoid_bomb_state"] = AvoidBombState,--a copier dans StateList
}

function initialization()
	Helper:debug_print("\n\nIA_BREAKER) initialization")
	Helper:initialization_base(10, 10)
	StateMachine:init(3, 1000,
							10, 100)
end

-- DEBUG = 0
-- DEBUG_MAX = 100

-- active_debug = true

function play()
  -- if DEBUG == DEBUG_MAX then
		-- Helper:debug_print("\n\nIA_BREAKER) play")
		MapManager:update()
		StateMachine:play()
    -- DEBUG = 0
  -- end
  -- DEBUG = DEBUG + 1
end
