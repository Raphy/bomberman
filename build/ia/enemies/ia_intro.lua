require "actions"
require "state"
require "state_machine"

-- * BEGIN_STATE *

BeginState = State:new("begin_state")

function BeginState:action()
	Helper:debug_print("action : ".."begin_state")
end

BeginState.pre_conditions = {
	{ function()
		return true end,
		"push", "random_state", },
}

-- * RANDOM_STATE *

RandomState = State:new("random_state")

function RandomState:action()
	Helper:debug_print("action : ".."random_state")
	return Actions:go_random()
end

RandomState.pre_conditions = {
	-- { function()
	-- 		return Helper:get_elapsed_time() > 15--[[??]] end,
	-- 		"push", "put_bomb_state", },	
}

-- * PUT_BOMB_STATE *

PutBombState = State:new("put_bomb_state")

function PutBombState:action()
	Helper:debug_print("action : ".."put_bomb_state")
	return Actions:place_bomb()
end

PutBombState.pre_conditions = {
	{ function()
		return Helper:is_place_dangerous() end,
		"push", "avoid_bomb_state", },
}

PutBombState.post_conditions = {
	{ function()
		return StateMachine._last_action_status == true end,
		"pop", },
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



StateList = {
	["begin_state"] = BeginState,
	["random_state"] = RandomState,
	["put_bomb_state"] = PutBombState,
	["avoid_bomb_state"] = AvoidBombState,
}

-- active_debug = true

function initialization()
	Helper:debug_print("\n\nIA_INTRO) initialization")
	Helper:initialization_base()
	StateMachine:init(3, 1000, 10, 10)
end

function play()
	Helper:debug_print("\n\nIA_INTRO) play")
	StateMachine:play()
end
