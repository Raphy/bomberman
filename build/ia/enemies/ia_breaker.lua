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
	{ function()
		return true end,
		"push", "break_box_state", },
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

-- * BREAK_BOX_STATE *

BreakBoxState = State:new("break_box_state")

function BreakBoxState:action()
	Helper:debug_print("action : ".."break_box_state")
	return true
end

BreakBoxState.pre_conditions = {
	{ function()
		return Helper:is_place_dangerous() end,
		"push", "avoid_bomb", },
	{ function()
		return not Helper:obj_in_view("Box") end,--in map ?
		"pop", },
	{ function()
		return not Helper:obj_in_action_range("Box") end,
		"push", "get_closer_of_box"},
	{ function()
		return true end,
		"push", "put_bomb_state"},
}

BreakBoxState.post_conditions = {

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

}






StateList = {
	["begin_state"] = BeginState,
	["break_box_state"] = BreakBoxState,--a copier dans StateList
	["avoid_bomb_state"] = AvoidBombState,--a copier dans StateList
	["put_bomb_state"] = PutBombState,--a copier dans StateList
}

function initialization()
	Helper:debug_print("\n\nIA_BREAKER) initialization")
	Helper:initialization_base(10, 10)
	StateMachine:init(3, 1000,
							10, 100)
end


function play()
		MapManager:update()
		StateMachine:play()
end
