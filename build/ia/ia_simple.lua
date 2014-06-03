
require 'actions'

X,Y = 10,10

function onInitialization()
  print(me:getName(me)) -- Prints the player name
  Helper:getAllObject("player")
  me:moveUp(me)
  math.randomseed( os.time() )
end

function onMyTurn()
  Actions:actRandom(me)
end

print("-----init----")
onInitialization()
print("-----fin init----")

for i=0, 10 do
print("\n-----myturn-----")
onMyTurn()
end
