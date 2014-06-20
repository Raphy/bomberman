print("[LUA] ----------------------------------")

local tests = {"#1", "#2", "#3"}
for i=1, #tests do
   print(tests[i])
end

print("[LUA] map:get")
local objects = map:get(42, 21, 2)

print("[LUA] for objects")
for i=1, #objects do
   print(objects[i]:getType())
   --print("[Object " .. objects[i]:getType() .. "] (" .. objects[i]:getX() .. ", " .. objects[i]:getY().. ")")
end
map:free(objects)


--[[
local objects = map:get(42, 21, 2)
for i=1, #objects do
   print("[LUA] " .. objects[i])
end
]]


print("[LUA] ----------------------------------")


function initialization()
   print("[LUA] initialization()")
end

function play()
   print("[LUA] play")
end
