
require "actions"
require "state"
require "state_machine"




-- * GET_CLOSER_OF_ENEMY *

GetCloserOfEnemyState = State:new("get_closer_of_enemy_state")

function GetCloserOfEnemyState:action()
  Actions:get_closer_of_one_enemy()
  return Helper:are_objects_around("enemy",me:getPosition(),2) then
    StateMachine:action_terminated() end
end

GetCloserOfEnemyState.pre_conditions = {
  { function()-- en danger
      return not Helper:is_place_safe() end,
    "push", "avoid_bomb_state", },
  { function()-- enemy assez pres
      return Helper:are_objects_around("enemy",me:getPosition(),2) end,
    "push", "kill_enemy_state", },--pop ?
  { function()-- impossible de l'atteindre
      return not Helper:are_objects_around("enemy",me:getPosition(),MapManager.size / 2) end,
    "push", "break_wall_state", },
  { function()-- pas d'enemy sur la map
      return not Helper:are_objects_around("enemy",me:getPosition(),MapManager.size / 2) end,
    "push", "kill_enemy_state", },
}

-- * AVOID_BOMB *

AvoidBombState = State:new("avoid_bomb_state")

function AvoidBombState:action()
  Helper:debug_print("action : avoid_bomb_state")
  -- if not Actions:avoid_bomb() then
  --   "push", "break_wall_state"
  if Helper:is_place_safe() then
    StateMachine:action_terminated() end
end

AvoidBombState.pre_conditions = {
  { function()-- impossible de s'enfuir
      return not Helper:are_objects_around("enemy",me:getPosition(),MapManager.size / 2) end,
    "push", "break_wall_state", },
  { function()
    return Helper:is_place_safe() end,
    "pop", },
}


-- * KILL_ENEMY *

KillEnemyState = State:new("kill_enemy_state")

function KillEnemyState:action()
  Helper:debug_print("action : ".."kill_enemy_state")
  --corps
  if true --[[pas d'ennemie]] then StateMachine:action_terminated() end
end

KillEnemyState.pre_conditions = {
  { function()
    return not Helper:is_place_safe() end,
    "push", "avoid_bomb_state", },
}

-- * GET_AWAY_OF_ENEMY *

GetAwayOfEnemyState = State:new("get_away_of_enemy_state")

function GetAwayOfEnemyState:action()
  Helper:debug_print("action : ".."get_away_of_enemy_state")
  --corps
  if true --[[pas d'ennemie]] then StateMachine:action_terminated() end
end

GetAwayOfEnemyState.pre_conditions = {
  --conditions
}

-- * PUT_BOMB *

PutBombState = State:new("put_bomb_state")

function PutBombState:action()
  Helper:debug_print("action : ".."put_bomb_state")
  if Actions:place_bomb() then
    StateMachine:action_terminated() end
end

PutBombState.pre_conditions = {
  { function()
    return not Helper:is_place_safe() end,
    "push", "avoid_bomb_state", },  
}


-- * GET_BONUS *

GetBonusState = State:new("get_bonus_state")

function GetBonusState:action()
  Helper:debug_print("action : ".."get_bonus_state")
  StateMachine:action_terminated()
end

GetBonusState.pre_conditions = {
  --conditions
}


-- * BEGIN *

BeginState = State:new("begin_state")

function BeginState:action()
  Helper:debug_print("action : ".."begin_state")
end

BeginState.pre_conditions = {
  { function()
    return true end,
    "push", "get_closer_of_enemy_state", },
}


StateList = {
  ["get_closer_of_enemy_state"] = GetCloserOfEnemyState,
  ["avoid_bomb_state"] = AvoidBombState,
  ["kill_enemy_state"] = KillEnemyState,--a copier dans StateList
  ["get_away_of_enemy_state"] = GetAwayOfEnemyState,--a copier dans StateList
  ["put_bomb_state"] = PutBombState,--a copier dans StateList
  ["begin_state"] = BeginState,--a copier dans StateList
  ["get_bonus_state"] = GetBonusState,--a copier dans StateList
}


function initialization()
  print("\n\nis_state : initialization...")
  Helper:initialization_base(10,10)
  StateMachine:init()
end

DEBUG = 0
DEBUG_MAX = 100

active_debug = true

function play()
  if DEBUG == DEBUG_MAX then
    MapManager:update()
    StateMachine:play()
    DEBUG = 0
  end
  DEBUG = DEBUG + 1
  -- Helper:debug_print("\n\nIA_SIMPLE) play")
end
