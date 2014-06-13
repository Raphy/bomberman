
State = {
	name = "toto",--tag ?
	pre_conditions = {},
	post_conditions = {},
}

function State:new(name)
	assert(name ~= nil)
	local o = {name = name, pre_conditions = {}, post_conditions = {}}
	setmetatable(o, State)
	return o
end

function State:action()
	Helper:warning("this method should be override")
end
