print("LoL");
player = {
    position = {
    x = 32.5, y = 20.0
    },
    filename = "sprite.png",
    HP = 300
}

array = {1, 1, 2, 3, 5, 10, 20}

print("##################################")

-- call the registered C-function
io.write('[Lua] Calling the C functionn')
a = displayLuaFunction(12, 3.141592, 'hola')

-- print the return values
-- io.write('[Lua] The C function returned <' .. a .. '> and <' .. b .. '>n')
print("A=" .. a)


print("##################################")

my_lua_class:printMsg();
my_lua_class:setMsg("LUA");
my_lua_class:printMsg();