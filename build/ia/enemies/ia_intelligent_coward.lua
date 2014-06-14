require 'actions'
require 'state'
require 'state_machine'

-- * BEGIN_STATE *

BeginState = State:new("begin_state")

function BeginState:action()
  Helper:debug_print("action : ".."begin_state")
  return false
end

BeginState.pre_conditions = {
  { function()
    return true end,
    "push", "wait_state", },
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
  { function()
    return Helper:last_action_failed() end,
    "push", "break_box_state" },
}

-- * WAIT_STATE *

WaitState = State:new("wait_state")

function WaitState:action()
  Helper:debug_print("action : ".."wait_state")
  return Actions:wait()
end

WaitState.pre_conditions = {
  { function()
    return Helper:is_place_dangerous() end,
    "push", "avoid_bomb_state", },
}

WaitState.post_conditions = {
}

-- * BREAK_BOX_STATE *

BreakBoxState = State:new("break_box_state")

function BreakBoxState:action()
  Helper:debug_print("action : ".."break_box_state")
  return true
end

BreakBoxState.pre_conditions = {
  { function()
    return not Helper:obj_in_action_range("Box") end,
    "push", "get_closer_of_box_state", },
  { function()
    return not Helper:obj_in_view("Box") end,
    "pop", },-- faire un wait avant ?
  { function()
    return true end,
    "push", "put_bomb", },
}

BreakBoxState.post_conditions = {
  { function()
    return Helper:last_action_succeed() end,
    "pop", },
}

-- * GET_CLOSER_OF_BOX_STATE *

GetCloserOfBoxState = State:new("get_closer_of_box_state")

function GetCloserOfBoxState:action()
  Helper:debug_print("action : ".."get_closer_of_box_state")
  return Actions:get_closer_of_obj("Box")
end

GetCloserOfBoxState.pre_conditions = {
  { function()
    return Helper:obj_in_action_range() end,
    "pop", },
  { function()
    return not Helper:obj_view() end,
    "pop", },-- ??
}

GetCloserOfBoxState.post_conditions = {
}






StateList = {
  ["begin_state"] = BeginState,
  ["avoid_bomb_state"] = AvoidBombState,--a copier dans StateList
  ["wait_state"] = WaitState,--a copier dans StateList
  ["break_box_state"] = BreakBoxState,--a copier dans StateList
  ["get_closer_of_box_state"] = GetCloserOfBoxState,--a copier dans StateList
}

function initialization()
  Helper:debug_print("\n\nIA_INTELLIGENT_COWARD) initialization")
  Helper:initialization_base(20, 10)
  StateMachine:init(3, 1000,
              10, 20)
end

DEBUG = 0
DEBUG_MAX = 1

active_debug = true
active_debug_list = true

function play()
  if DEBUG >= DEBUG_MAX then
    MapManager:update()
    Helper:debug_print("\n\nIA_INTELLIGENT_COWARD) play")
    StateMachine:play()
    DEBUG = 0
  end
  DEBUG = DEBUG + 1
end
