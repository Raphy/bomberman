
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
		"push", "random_state", },
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



-- * GET_CLOSER_OF_ENEMY_STATE *

GetCloserOfEnemyState = State:new("get_closer_of_enemy_state")

function GetCloserOfEnemyState:action()
	Helper:debug_print("action : ".."get_closer_of_enemy_state")
	return Actions:get_closer_of_one_enemy()
end

GetCloserOfEnemyState.pre_conditions = {
	{ function()
		return Helper:is_place_dangerous() end,
		"push", "avoid_bomb_state", },
  { function()
      return Helper:obj_in_action_range("Player") end,
    "push", "kill_enemy_state" },
  { function()--pas d'enemy en vue
      return not Helper:obj_in_view("Player") end,
    "push", "random_state", },
}
GetCloserOfEnemyState.post_conditions = {
  { function()--pas d'enemy en vue
      return not Helper:obj_in_view("Player") end,
    "push", "random_state", },
}

-- * RANDOM_STATE *

RandomState = State:new("random_state")

function RandomState:action()
	Helper:debug_print("action : ".."random_state")
	return Actions:go_random()
end

RandomState.pre_conditions = {
	{ function()
		return Helper:is_place_dangerous() end,
		"push", "avoid_bomb_state", },
  { function()
      return Helper:obj_in_view("Player") end,
    "push", "get_closer_of_enemy_state" },
}

-- * KILL_ENEMY_STATE *

KillEnemyState = State:new("kill_enemy_state")

function KillEnemyState:action()
	Helper:debug_print("action : ".."kill_enemy_state")
	return true
end

KillEnemyState.pre_conditions = {
	{ function()
		return Helper:is_place_dangerous() end,
		"push", "avoid_bomb_state", },
  { function()
      return not Helper:obj_in_action_range("Player") end,
    "pop", },
	{ function()
		return true end,
		"push", "put_bomb_state", },
}

KillEnemyState.post_conditions = {

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
	["get_closer_of_enemy_state"] = GetCloserOfEnemyState,--a copier dans StateList
	["random_state"] = RandomState,--a copier dans StateList
	["kill_enemy_state"] = KillEnemyState,--a copier dans StateList
	["put_bomb_state"] = PutBombState,--a copier dans StateList
}

function initialization()
	Helper:debug_print("\n\nIA_STALKER) initialization")
	Helper:initialization_base(10, 10)
	StateMachine:init(3, 1000, 30, 10)
	MapManager:update()
end


function play()
	MapManager:update()
	StateMachine:play()
end

