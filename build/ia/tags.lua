
TagsList = { "up","down","left","right",
				"player","me","bomb","fire","item",
				"open","closed","unknown",
				"astar","dijkstra" }

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
