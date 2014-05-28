print(me:getName())
print("%f", me:getPositionX())
print(me:getPositionY())

if me:moveUp() then
   print("Move Up OK");
else
   print("Move Up KO");
end

if me:moveDown() then
   print("Move Down OK");
else
   print("Move Down KO");
end

if me:moveLeft() then
   print("Move Left OK");
else
   print("Move Left KO");
end

if me:moveRight() then
   print("Move Right OK");
else
   print("Move Right KO");
end

if me:putBomb() then
   print("Put Bomb OK");
else
   print("Put bomb KO");
end
