
TagsList = { "up","down","left","right","put_bomb",
				"Me","Player", "Item","Bomb","Bonus",
				"preview_bomb","preview_fire","mark_safe_case",
				"open","closed","unknown",
				"astar","dijkstra","glouton",
				"push","pop","continue", }
Tags = {}
for i,v in ipairs(TagsList) do
	Tags[v] = i
end

function Tags:v(key)
	local value = self[key]
	if value == nil then
		Helper:warning("Unexisting tag \"",key,"\"") end
	return value
end
function Tags:k(value)
	local key = TagsList[value]
	if key == nil then
		Helper:warning("Unexisting value \"",value,"\" in TagsList") end
	return key
end

function Tags:is_a_tag_value(v)
	return TagsList[v] ~= nil
end
function Tags:is_a_tag_key(k)
	return Tags[k] ~= nil
end
