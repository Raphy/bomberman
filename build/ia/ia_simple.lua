
require 'actions'

-- X,Y = 10,10

-- ATTENTION : les index dans la map lua vont de 1 à w(ou h)

function onInitialization()
  Map2D:init_map(10,100)

  Helper:getAllObject("player")
  print(me:getName(me))
  me:moveUp(me)
  math.randomseed( os.time() )
end

function onMyTurn()
  -- Map2D:clean_map() -> ici ou a chaque calc_path ?

  print(" actRandom")
  Actions:actRandom(me)
  print(" goTo 1.0 2.0")
  Actions:goTo(me, 9.0, 100.0)
end

print("-----init----")
onInitialization()
print("-----fin init----")

for i=0, 0 do
print("\n-----myturn-----")
onMyTurn()
print("-----fin myturn-----")
end
