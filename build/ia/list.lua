
List = {
	_nbElem = 0,
	_name = "ListName",
}

function List:new(name)
	tab = {}
	setmetatable(tab, self)
	self.__index = self
	self.__metatable = self
	tab._name = name
	return tab
end

-- idx = id = value_dans_les_listes


function List:addCaseInList(list, case)
	if List:isInList(list, case) then
		Helper:warning("try to add idx "..case.idx.." already in list "..list._name)
	end
	Helper:debug_print("addCaseInList : "..list._name..". Idx = "..case.idx)
	list._nbElem = list._nbElem + 1
	table.insert(list, list._nbElem, case.idx)
end

function List:removeCaseFromList(list, case)
	if not List:isInList(list, case) then
		Helper:warning("try to remove unexisted idx "..case.idx.." from list "..list._name)
	end
	Helper:debug_print("removeCaseFromList : "..list._name..". Idx = "..case.idx)
	for i,v in ipairs(list) do
		if v == case.idx then
			table.remove(list, i)
			list._nbElem = list._nbElem - 1
		end
	end
end

function List:front_case(list)
	if list._nbElem <= 0 then
		Helper:warning("front_case on empty list "..list._name)
	end
	return Map2D:get_case(list[1])
end

function List:front_idx(list)
	if list._nbElem <= 0 then
		Helper:warning("front_idx on empty list "..list._name)
	end
	return list[1]
end

function List:pop(list)
	if list._nbElem <= 0 then
		Helper:warning("pop on empty list "..list._name)
	end
	table.remove(list, 1)
	list._nbElem = list._nbElem - 1
end


function List:isInList(list, case)
	for _,v in ipairs(list) do
		if v == case.idx then
			return true
		end
	end
end

function List:size(list)
	return list._nbElem
end

function List:iter_case(list)
	local i = 0
	local n = list._nbElem
	return function ()
		i = i + 1
		if i <= n then return Map2D:get_case(list[i]) end
	end
end

function List:iter_idx(list)
	local i = 0
	local n = list._nbElem
	return function ()
		i = i + 1
		if i <= n then return list[i] end
	end
end
