
List = {
	_nb_elem = 0,
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



-- * GENERAL_LIST *


function List:front(list)
	if list._nb_elem <= 0 then
		Helper:warning("front on empty list "..list._name)
	end
	return list[1]
end
function List:back(list)
	if list._nb_elem <= 0 then
		Helper:warning("back on empty list "..list._name)
	end
	return list[list._nb_elem]
end

function List:push(list, elem)
	-- if List:is_case_in_list(list, elem) then
	-- 	Helper:warning("try to add idx "..elem.idx.." already in list "..list._name)
	-- end
	-- Helper:debug_print("add_elem_in_list : "..list._name..". _idx = "..elem)
	list._nb_elem = list._nb_elem + 1
	table.insert(list, 1, elem)
end
function List:push_back(list, elem)
	-- if List:is_case_in_list(list, elem) then
	-- 	Helper:warning("try to add idx "..elem.idx.." already in list "..list._name)
	-- end
	-- Helper:debug_print("add_elem_in_list : "..list._name..". _idx = "..elem)
	list._nb_elem = list._nb_elem + 1
	table.insert(list, list._nb_elem, elem)
end

function List:pop(list)
	if list._nb_elem <= 0 then
		Helper:warning("pop on empty list "..list._name)
	end
	table.remove(list, 1)
	list._nb_elem = list._nb_elem - 1
end
function List:pop_back(list)
	if list._nb_elem <= 0 then
		Helper:warning("pop_back on empty list "..list._name)
	end
	table.remove(list, list._nb_elem)
	list._nb_elem = list._nb_elem - 1
end

function List:size(list)
	return list._nb_elem
end
function List:iter(list)
	local i = 0
	local n = list._nb_elem
	return function ()
		i = i + 1
		if i <= n then return list[i] end
	end
end



-- * CASE_LIST *

function List:front_case(list)
	if list._nb_elem <= 0 then
		Helper:warning("front_case on empty list "..list._name)
	end
	return MapManager:get_case(list[1])
end

function List:add_case_in_list(list, case)
	if List:is_case_in_list(list, case) then
		Helper:warning("try to add idx "..case.idx.." already in list "..list._name)
	end
	Helper:debug_print("add_case_in_list : "..list._name..". _idx = "..case.idx)
	list._nb_elem = list._nb_elem + 1
	table.insert(list, list._nb_elem, case.idx)
end
function List:remove_case_from_list(list, case)
	if not List:is_case_in_list(list, case) then
		Helper:warning("try to remove unexisted idx "..case.idx.." from list "..list._name)
	end
	Helper:debug_print("remove_case_from_list : "..list._name..". _idx = "..case.idx)
	for i,v in ipairs(list) do
		if v == case.idx then
			table.remove(list, i)
			list._nb_elem = list._nb_elem - 1
		end
	end
end

function List:is_case_in_list(list, case)
	for _,v in ipairs(list) do
		if v == case.idx then
			return true
		end
	end
end

function List:iter_case(list)
	local i = 0
	local n = list._nb_elem
	return function ()
		i = i + 1
		if i <= n then return MapManager:get_case(list[i]) end
	end
end

