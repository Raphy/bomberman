require 'helper'

function onInitialization()
  -- What to do when the script is loaded
end

function onMyTurn()
  -- What to do when the player by this script will play

  -- The scripts is provided by the following objects:
  -- Variable "me" (API::Me) represents the player by this script
  -- Variable "map" (API::Map) represents the game map

  print(me:getName()) -- Prints the player name

  -- local objects = map:get(me:getX(), me:getY()) -- Returns std::vector<API::GameObject>

  -- print("Objects :")
  -- -- Browse the objects in the current player position
  -- for object in objects do
  --   print("Object "..object:getType().." in position "..object:getX()..","..object:getY())
  -- end

  Helper:getAllObject("player")

end

onInitialization()
onMyTurn()
