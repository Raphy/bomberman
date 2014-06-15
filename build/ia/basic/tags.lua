
TagsList = { "up","down","left","right","put_bomb",
				"Me","Player", "Item","Bomb","Item",
				"preview_bomb","preview_fire","mark_safe_case",
				"open","closed","unknown",
				"astar","dijkstra","glouton",
				"push","pop","continue", }
Tags = {}
for i,v in ipairs(TagsList) do
	Tags[v] = i
end

function Tags:v(key)
	return self[key]
end
function Tags:k(value)
	return TagsList[value]
end

function Tags:is_a_tag_value(v)
	return TagsList[v] ~= nil
end
function Tags:is_a_tag_key(k)
	return Tags[k] ~= nil
end
