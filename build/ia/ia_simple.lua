
require 'actions'

-- X,Y = 10,10

-- ATTENTION : les index dans la map lua vont de 1 à w(ou h)

function onInitialization()
  MapManager:init(10,100)

  Helper:getAllObject("player")
  print(me:getName(me))
  me:moveUp(me)
  math.randomseed( os.time() )
end

function onMyTurn()
  -- MapManager:clean_map() -> ici ou a chaque calc_path ?

  print(" actRandom")
  Actions:actRandom(me)
  print(" goTo 1.0 2.0")
  MapManager:setVisionActivate(Coord:new(me:getX(), me:getY()), 2)
  Actions:goTo(me, me:getX()+2, me:getY()+1)
  -- Actions:goTo(me, 9.0, 100.0)
end

print("-----init----")
onInitialization()
print("-----fin init----")

for i=0, 0 do
print("\n-----myturn-----")
onMyTurn()
print("-----fin myturn-----")
end
