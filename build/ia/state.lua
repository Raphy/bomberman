
State = {
	name = "toto",--tag ?
	pre_conditions = {}
	-- pre_conditions,pos_conditions = nil,nil
	-- enable_exec,enable_repeat = false,false,
	-- next_state = -1,
}

--[[
require doit appeler des fonctions de helper,
execute doit setter next_state, enable_exec et enable_repeat
]]
-- Condition = {
-- 	function ()	print("require : should return a boolean") end,
-- 	function ()	print("execute : should execute the correspondante action") end,
-- }

function State:new(name)
	assert(name ~= nil)
	local o = {name = name, pre_conditions = {}}
	setmetatable(o, State)
	return o
end

function State:action()
	Helper:warning("this method should be override")
end
-- function State:pre_condition()
-- 	Helper:warning("this method should be override")
-- end
-- function State:pos_condition()
-- 	Helper:warning("this method should be override")
-- end
