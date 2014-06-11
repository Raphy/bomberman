
require 'actions'
require 'state'
require 'state_machine'


-- * BEGIN *

BeginState = State:new("begin")

function BeginState:action()
  Helper:debug_print("action : ".."begin")
end

BeginState.pre_conditions = {
  { function()
    return true end,
    "push", "put_bomb", },
}



-- * GET_CLOSER_OF_ENEMY *

GetCloserOfEnemyState = State:new("get_closer_of_enemy")

function GetCloserOfEnemyState:action()
  Actions:get_closer_of_one_enemy()
  -- if true --[[enemy found]] then StateMachine:action_terminated() end
end

GetCloserOfEnemyState.pre_conditions = {
  -- { function()
  --     return not Helper:is_place_safe() end,
  --   "push", "avoid_bomb", },
  -- { function()
  --     return Helper:are_objects_around("enemy",me:getX(),me:getY(),2) end,
  --   "push", "kill_enemy", },
  -- { function()
  --     return Helper:are_objects_around("enemy",me:getX(),me:getY(),(MapManager.size / 2)) end,
  --   "push", "get_bonus", },
}

-- * AVOID_BOMB *

AvoidBombState = State:new("avoid_bomb")

function AvoidBombState:action()
  print("action : avoid_bomb")
  Actions:avoid_bomb()
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

-- * PUT_BOMB *

PutBombState = State:new("put_bomb")

function PutBombState:action()
  Helper:debug_print("action : ".."put_bomb")
  Actions:place_bomb()
end

PutBombState.pre_conditions = {
  { function()
    return Helper:is_place_safe() end,
    "push", "avoid_bomb", },  
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
  ["put_bomb"] = PutBombState,--a copier dans StateList
  ["begin"] = BeginState,--a copier dans StateList
}


function onInitialization()
  math.randomseed(os.time())
  Coord:init()
  MapManager:init(10,10)
  -- MapManager:set_vision_activate(Helper:get_my_coord(), 10)
  StateMachine:init()
  local x,y = MapManager:idx_to_coord(45)
  print("x,y = "..x.." "..y)
  print(Helper:are_objects_in_case(x,y,type))
  print(Helper:are_objects_in_case(5.0,5.0,type))
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

for i=0, 2 do
print("\n-----myturn-----")
onMyTurn()
print("-----fin myturn-----")
end
