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
		"push", "get_item_state", },
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

-- * GET_ITEM_STATE *

GetItemState = State:new("get_item_state")

function GetItemState:action()
	Helper:debug_print("action : ".."get_item_state")
	return Actions:get_closer_of_obj("Item")
end

GetItemState.pre_conditions = {
	{ function()
		return Helper:is_place_dangerous() end,
		"push", "avoid_bomb_state", },
	{ function()
		return not Helper:obj_in_view("Item") end,
		"push", "break_box_state", },
}

GetItemState.post_conditions = {
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
		"push", "avoid_bomb_state", },
	{ function()
		return not Helper:obj_in_view("Box") end,
		"pop", },
	{ function()
		return not Helper:obj_in_action_range("Box") end,
		"push", "get_closer_of_box_state" },
	{ function()
		return true end,
		"push", "put_bomb_state", },
}

BreakBoxState.post_conditions = {

}

-- * GET_CLOSER_OF_BOX_STATE *

GetCloserOfBoxState = State:new("get_closer_of_box_state")

function GetCloserOfBoxState:action()
	Helper:debug_print("action : ".."get_closer_of_box_state")
	return Actions:get_closer_of_obj("Box")
end

GetCloserOfBoxState.pre_conditions = {
	{ function()
		return Helper:is_place_dangerous() end,
		"push", "avoid_bomb_state", },
	{ function()
		return not Helper:obj_in_view("Box") end,
		"pop", },
	{ function()
		return Helper:obj_in_action_range("Box") end,
		"pop", },
}

GetCloserOfBoxState.post_conditions = {

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
		return true end,
		"pop", },
}







StateList = {
	["begin_state"] = BeginState,
	["avoid_bomb_state"] = AvoidBombState,--a copier dans StateList
	["get_item_state"] = GetItemState,--a copier dans StateList
	["break_box_state"] = BreakBoxState,--a copier dans StateList
	["get_closer_of_box_state"] = GetCloserOfBoxState,--a copier dans StateList
	["put_bomb_state"] = PutBombState,--a copier dans StateList
}

function initialization()
	Helper:debug_print("\n\nIA_SEEKER) initialization")
	Helper:initialization_base(10, 10)
	StateMachine:init(3, 1000,
							10, 1000)
end

-- DEBUG = 0
-- DEBUG_MAX = 100

-- active_debug = true

function play()
	me:putBomb()
  -- if DEBUG == DEBUG_MAX then
		-- MapManager:update()
		-- Helper:debug_print("\n\nIA_SEEKER) play")
		-- StateMachine:play()
    -- DEBUG = 0
  -- end
  -- DEBUG = DEBUG + 1
end
