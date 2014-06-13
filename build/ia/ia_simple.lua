
require "helper"
require "map_manager"
require "api"

-- X,Y = 10,10

-- ATTENTION : les index dans la map lua vont de 1 à w(ou h)

function onInitialization()
 MapManager:init(10,100)
 Coord:init()

--  Helper:get_all_object("player")
  print(me:getName())
  me:moveUp()
  math.randomseed( os.time() )
end

function onMyTurn()
  MapManager:clean_map()-- -> ici ou a chaque calc_path ?

  Helper:debug_print(" act_random")
 Actions:act_random()
 Helper:debug_print(" go_to 1.0 2.0")
 local x,y = me:getPosition()
 MapManager:set_vision_activate(Coord:new(x,y), 2)
 Actions:go_to(x+2, y+1)
  Actions:go_to(9.0, 100.0)
end

print("-----init----")
onInitialization()
print("-----fin init----")

for i=0, 0 do
print("\n-----myturn-----")
onMyTurn()
print("-----fin myturn-----")
end
