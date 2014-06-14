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

-- * GET_CLOSER_OF_ENEMY_STATE *

GetCloserOfEnemyState = State:new("get_closer_of_enemy_state")

function GetCloserOfEnemyState:action()
	Helper:debug_print("action : ".."get_closer_of_enemy_state")
	return Actions:get_closer_of_one_enemy()
end

GetCloserOfEnemyState.pre_conditions = {
  { function()--pas d'enemy en vue
      return not Helper:enemy_in_view() end,
    "push", "random_state", },
}
GetCloserOfEnemyState.post_conditions = {
  { function()--pas d'enemy en vue
      return not Helper:enemy_in_view() end,
    "push", "random_state", },
}

-- * RANDOM_STATE *

RandomState = State:new("random_state")

function RandomState:action()
	Helper:debug_print("action : ".."random_state")
	return Actions:go_random()
end

RandomState.pre_conditions = {
  { function()--enemy en vue
      return Helper:enemy_in_view() end,
    "push", "get_closer_of_enemy_state" },
}



StateList = {
	["begin_state"] = BeginState,
	["get_closer_of_enemy_state"] = GetCloserOfEnemyState,--a copier dans StateList
	["random_state"] = RandomState,--a copier dans StateList
}

function initialization()
	Helper:debug_print("\n\nIA_STALKER) initialization")
	Helper:initialization_base(10, 5)
	StateMachine:init(3, 1000, 5, 10)
	MapManager:update()
end


function play()
	StateMachine:play()
end
