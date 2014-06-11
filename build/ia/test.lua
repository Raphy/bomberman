print("[LUA] Exec")
x = 42
print("[LUA] ----------------------------------")

go = GameObject:new(10.10, 12.12)
print("[LUA] go.x = " .. go:getX())
go:setX(42.1)
print("[LUA] go.x = " .. go:getX())
print("[LUA] go.y = " .. go:getY())
print("[LUA] go.type = " .. go:getType())
print("[LUA] ----------------------------------")

p = Player:new("Toto", 21.42, 42.84)
print("[LUA] p.name = " .. p:getName());
print("[LUA] p.type = " .. p:getType());
print("[LUA] p.x = " .. p:getX());
print("[LUA] p.y = " .. p:getY());
print("[LUA] ----------------------------------")

--me = Me:new("Raphy", 11.2, 25.12)
print("[LUA] me.name = " .. me:getName());
print("[LUA] me.type = " .. me:getType());
print("[LUA] me.x = " .. me:getX());
print("[LUA] me.y = " .. me:getY());
if me:moveUp() then
   print("[LUA] moved up")
end
print("[LUA] me.y = " .. me:getY());
if me:putBomb() then
   print("[LUA] Bombed")
else
   print("[LUA] NO BOMB!!!")
end

print("[LUA] ----------------------------------")

str = ""

function initialization()
   print("[LUA] initialization()")
   print("[LUA] x = " .. x)
end

function play()
   print("[LUA] play")
   print("[LUA] str = " .. str)
end
