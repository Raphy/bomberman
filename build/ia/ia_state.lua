
require 'actions'
require 'state'
require 'state_machine'


-- * GET_CLOSER_OF_ENEMY *

GetCloserOfEnemyState = State:new("get_closer_of_enemy")

function GetCloserOfEnemyState:action()
  Actions:get_closer_of_one_enemy()
  if true --[[enemy found]] then StateMachine:action_terminated() end
end

GetCloserOfEnemyState.pre_conditions = {
  { function()
      return not Helper:is_place_safe() end,
    "push", "avoid_bomb", },
  { function()
      return Helper:are_objects_around(Tags:v("enemy"),me:getX(),me:getY(),2) end,
    "push", "kill_enemy", },
  { function()
      return Helper:are_objects_around(Tags:v("enemy"),me:getX(),me:getY(),(MapManager.size / 2)) end,
    "push", "get_bonus", },
}

-- * AVOID_BOMB *

AvoidBombState = State:new("avoid_bomb")

function AvoidBombState:action()
  print("action : avoid_bomb")
end

AvoidBombState.pre_conditions = {
  { function()
      return false end,
    "push", "get_closer_of_enemy", },
}


-- * KILL_ENEMY *

KillEnemyState = State:new("kill_enemy")

function KillEnemyState:action()
  Helper:debug_print("action : ".."kill_enemy")
  --corps
end

KillEnemyState.pre_conditions = {
  { function()
    return Helper:is_place_safe() end,
    "push", "avoid_bomb", },
}

-- * GET_AWAY_OF_ENEMY *

GetAwayOfEnemyState = State:new("get_away_of_enemy")

function GetAwayOfEnemyState:action()
  Helper:debug_print("action : ".."get_away_of_enemy")
  --corps
end

GetAwayOfEnemyState.pre_conditions = {
  --conditions
}



-- * GET_AWAY_OF_ENEMY *

-- * BREAK_WALL *

-- * GET_CLOSER_OF_WALL *

-- * WAIT *

-- * GET_CLOSER_OF_BONUS *

-- * USE_BONUS *

-- * GET_BONUS *

-- * BEGIN *



StateList = {
  ["get_closer_of_enemy"] = GetCloserOfEnemyState,
  ["avoid_bomb"] = AvoidBombState,
  ["kill_enemy"] = KillEnemyState,--a copier dans StateList
  ["get_away_of_enemy"] = GetAwayOfEnemyState,--a copier dans StateList
}


function onInitialization()
  math.randomseed(os.time())
  MapManager:init(10,100)
  Coord:init()
  StateMachine:init("get_closer_of_enemy")
end

function onMyTurn()
  StateMachine._executed = false
  local i = 1
  while i <= 3 and StateMachine._executed == false do
    StateMachine:update()
    i = i + 1
  end
end

print("-----init----")
onInitialization()
print("-----fin init----")

for i=0, 1 do
print("\n-----myturn-----")
onMyTurn()
print("-----fin myturn-----")
end
