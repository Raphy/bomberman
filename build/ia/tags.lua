
TagsList = { "up","down","left","right",
				"player","me","enemy","item","bomb",
				"open","closed","unknown",
				"astar","dijkstra",
				"push","pop","continue" }
Tags = {}
for i,v in ipairs(TagsList) do
	Tags[v] = i
end

function Tags:v(key)
	local value = self[key]
	if value == nil then Helper:warning("Unexisting tag \""..key.."\"") end
	return value
end
function Tags:k(value)
	local key = TagsList[value]
	if key == nil then Helper:warning("Unexisting value \""..value.."\" in TagsList") end
	return key
end

function Tags:is_a_tag_value(v)
	Helper:to_implement()
end
function Tags:is_a_tag_key(v)
	Helper:to_implement()
end
