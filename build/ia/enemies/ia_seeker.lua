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
		"push", "get_bonus_state", },
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

-- * GET_BONUS_STATE *

GetBonusState = State:new("get_bonus_state")

function GetBonusState:action()
	Helper:debug_print("action : ".."get_bonus_state")
	return Actions:get_closer_of_obj("Bonus")
end

GetBonusState.pre_conditions = {
	{ function()
		return Helper:is_place_dangerous() end,
		"push", "avoid_bomb_state", },
}

GetBonusState.post_conditions = {
}



StateList = {
	["begin_state"] = BeginState,
	["avoid_bomb_state"] = AvoidBombState,--a copier dans StateList
	["get_bonus_state"] = GetBonusState,--a copier dans StateList
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
