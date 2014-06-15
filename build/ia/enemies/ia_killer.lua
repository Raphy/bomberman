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
		"push", "kill_enemy_state", },
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
		"push", "get_closer_of_enemy_state", },
	{ function()
		return not Helper:obj_in_view("Player") end,
		"push", "wait_state", },
}

KillEnemyState.post_conditions = {
}

-- -- * WAIT_STATE *

-- WaitState = State:new("wait_state")

-- function WaitState:action()
-- 	Helper:debug_print("action : ".."wait_state")
-- 	 Actions:wait(100)
-- 	-- Actions._wait.begin = Helper:get_current_time()
-- 	-- Actions._wait.duration = duration
-- 	 print("wait begin", Actions._wait.begin)
-- 	 print("		 duration", Actions._wait.duration)
-- end

-- WaitState.pre_conditions = {
-- 	{ function()
-- 		return Helper:is_place_dangerous() end,
-- 		"push", "avoid_bomb_state", },
-- 	{ function()
-- 		return Helper:no_more_wait() end,
-- 		"pop", },
-- }

-- WaitState.post_conditions = {
-- }

-- * GET_CLOSER_OF_ENEMY_STATE *

GetCloserOfEnemyState = State:new("get_closer_of_enemy_state")

function GetCloserOfEnemyState:action()
	Helper:debug_print("action : ".."get_closer_of_enemy_state")
	return Actions:get_closer_of_obj("Player")
end

GetCloserOfEnemyState.pre_conditions = {
	{ function()
		return Helper:is_place_dangerous() end,
		"push", "avoid_bomb_state", },
	{ function()
		return Helper:obj_in_action_range("Player") end,
		"pop", },
	-- { function()
	-- 	return not Helper:obj_in_view("Player") end,
	-- 	"push", "wait_state", },
}

GetCloserOfEnemyState.post_conditions = {
}







StateList = {
	["begin_state"] = BeginState,
	["avoid_bomb_state"] = AvoidBombState,
	["kill_enemy_state"] = KillEnemyState,--a copier dans StateList
	["wait_state"] = WaitState,--a copier dans StateList
	["get_closer_of_enemy_state"] = GetCloserOfEnemyState,--a copier dans StateList
}


function initialization()
	Helper:debug_print("\n\nIA_KILLER) initialization")
	Helper:initialization_base(10, 10)
	StateMachine:init(3, 1000,
							30, 50)
end

-- DEBUG = 0
-- DEBUG_MAX = 100

active_debug = true

function play()
--   if DEBUG == DEBUG_MAX then
-- 		Helper:debug_print("\n\nIA_KILLER) play")
		MapManager:update()
		StateMachine:play()
--     DEBUG = 0
--   end
--   DEBUG = DEBUG + 1
end
