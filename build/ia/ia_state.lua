
require "actions"
require "state"
require "state_machine"




-- * GET_CLOSER_OF_ENEMY *

GetCloserOfEnemyState = State:new("get_closer_of_enemy_state")

function GetCloserOfEnemyState:action()
  Actions:get_closer_of_one_enemy()

  if true --[[enemy found]] then StateMachine:action_terminated() end
end

GetCloserOfEnemyState.pre_conditions = {
  -- { function()
  --     return not Helper:is_place_safe() end,
  --   "push", "avoid_bomb_state", },
  -- { function()
  --     return Helper:are_objects_around("enemy",me:getPosition(),2) end,
  --   "push", "kill_enemy_state", },
  -- { function()
  --     return Helper:are_objects_around("enemy",me:getPosition(),(MapManager.size / 2)) end,
  --   "push", "get_bonus_state", },
}

-- * AVOID_BOMB *

AvoidBombState = State:new("avoid_bomb_state")

function AvoidBombState:action()
  print("action : avoid_bomb_state")
  Actions:avoid_bomb_state()
  if Helper:is_place_safe() then StateMachine:action_terminated() end
end

AvoidBombState.pre_conditions = {
  -- { function()
  --     return false end,
  --   "push", "get_closer_of_enemy_state", },
  -- { function()
  --   return Helper:is_place_safe() end,
  --   "pop", },
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
  Helper:initialization_base()
  StateMachine:init()
  local x,y = MapManager:idx_to_coord(45)
  print("x,y = "..x.." "..y)
  print(Helper:are_objects_in_case(x,y,type))
  print(Helper:are_objects_in_case(5.0,5.0,type))
end

function play()
  -- print("\n\nis_state : play...")
  StateMachine:play()
  -- StateMachine._executed = false
  -- local i = 1
  -- while i <= 3 and StateMachine._executed == false do
  --   StateMachine:update()
  --   i = i + 1
  -- end
end

-- print("-----init----")
-- initialization()
-- print("-----fin init----")

-- for i=0, 2 do
-- print("\n-----myturn-----")
-- play()
-- print("-----fin myturn-----")
-- end
