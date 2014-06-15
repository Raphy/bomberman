
require "actions"
require "state"
require "state_machine"




-- * GET_CLOSER_OF_ENEMY *

GetCloserOfEnemyState = State:new("get_closer_of_enemy_state")

function GetCloserOfEnemyState:action()
  return Actions:get_closer_of_one_enemy()
end

GetCloserOfEnemyState.pre_conditions = {
  { function()-- en danger
      return Helper:is_place_dangerous() end,
    "push", "avoid_bomb_state", },
  { function()
    return Helper:obj_in_action_range("Player") end,
    "push", "kill_enemy_state", },

  -- { function()-- enemy assez pres
  --     return Helper:are_objects_around("Player",Helper:get_my_position(),2) end,
  --   "push", "kill_enemy_state", },--pop ?
  -- { function()-- impossible de l'atteindre
  --     return not Helper:are_objects_around("Player",Helper:get_my_position(),MapManager.size / 2) end,
  --   "push", "break_box_state", },
  -- { function()-- pas d'enemy sur la map
  --     return not Helper:are_objects_around("Player",Helper:get_my_position(),MapManager.size / 2) end,
  --   "push", "kill_enemy_state", },
}

GetCloserOfEnemyState.post_conditions = {
  -- { function()
  --   return Helper:obj_in_view("Player") end,
  --   "pop", },
}

-- * AVOID_BOMB *

AvoidBombState = State:new("avoid_bomb_state")

function AvoidBombState:action()
  Helper:debug_print("action : avoid_bomb_state")
  return Actions:avoid_bomb()
end

AvoidBombState.pre_conditions = {
  { function()-- impossible de s'enfuir
    return false end,
      -- return not Helper:are_objects_around("Player",Helper:get_my_position(),MapManager.size / 2) end,
    "push", "break_box_state", },
  { function()
    return Helper:is_place_safe() end,
    "pop", },
}

AvoidBombState.post_conditions = {
  { function()
    return true end,-- impossible de s'enfuir
    "push", "break_box_state", },
}

-- * KILL_ENEMY *

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
    return not Helper:obj_in_view("Player") end,
    "push", "get_closer_of_enemy_state", },
  { function()
    return Helper:obj_in_view("Player") end,
    "push", "put_bomb_state", },
}

KillEnemyState.post_conditions = {
  { function()
    return not Helper:obj_in_view("Player") end,
    "pop", },
}

-- * GET_AWAY_OF_ENEMY *

GetAwayOfEnemyState = State:new("get_away_of_enemy_state")

function GetAwayOfEnemyState:action()
  Helper:debug_print("action : ".."get_away_of_enemy_state")
  return false
end

GetAwayOfEnemyState.pre_conditions = {
  { function()
    return true end,
    "pop", },
}

-- * PUT_BOMB *

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


-- * GET_ITEM *

GetItemState = State:new("get_item_state")

function GetItemState:action()
  Helper:debug_print("action : ".."get_item_state")
  return false
end

GetItemState.pre_conditions = {
  --conditions
}
GetItemState.post_conditions = {
  { function()
    return true end,
    "pop", },
}


-- * BREAK_BOX_STATE *

BreakBoxState = State:new("break_box_state")

function BreakBoxState:action()
  Helper:debug_print("action : ".."break_box_state")
  return false
end

BreakBoxState.pre_conditions = {
  -- { function()
  --   return Helper:cond() end,--mur trop loin
  --   "push", "get_closer_of_box", },
  { function()
    return true end,
    "push", "put_bomb_state", },
}

BreakBoxState.post_conditions = {
  { function()
    return StateMachine._action_status.status end,
    "pop", },
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
  ["get_item_state"] = GetItemState,--a copier dans StateList
  ["break_box_state"] = BreakBoxState,--a copier dans StateList
}


function initialization()
  print("\n\nis_state : initialization...")
  Helper:initialization_base(10,10)
  StateMachine:init(1,1000,10,10)
end

DEBUG = 0
DEBUG_MAX = 50

active_debug = true

function play()
  -- StateMachine:play()
  if DEBUG == DEBUG_MAX then
    MapManager:update()
    StateMachine:play()
    DEBUG = 0
  end
  DEBUG = DEBUG + 1
  -- Helper:debug_print("\n\nIA_SIMPLE) play")
end
