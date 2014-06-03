
require 'actions'

-- X,Y = 10,10


function onInitialization()
  print(me:getName(me)) -- Prints the player name
  Helper.w = 10
  Helper.h = 10
  Helper:getAllObject("player")
  me:moveUp(me)
  math.randomseed( os.time() )
end

function onMyTurn()
  print(" actRandom")
  Actions:actRandom(me)
  print(" goTo 5.0 5.0")
  Actions:goTo(me, 5.0, 5.0)
end

print("-----init----")
onInitialization()
print("-----fin init----")

for i=0, 0 do
print("\n-----myturn-----")
onMyTurn()
print("-----fin myturn-----")
end
