
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


function List:push(list, elem)
	list._nb_elem = list._nb_elem + 1
	table.insert(list, 1, elem)
end
function List:pop(list)
	-- if list._nb_elem <= 0 then
	-- 	Helper:warning("pop on empty list "..list._name)
	-- end
	table.remove(list, 1)
	list._nb_elem = list._nb_elem - 1
end
function List:front(list)
	-- if list._nb_elem <= 0 then
	-- 	Helper:warning("front on empty list "..list._name)
	-- end
	return list[1]
end
function List:front_and_pop(list)
	-- if list._nb_elem <= 0 then
	-- 	Helper:warning("pop on empty list "..list._name)
	-- end
	local head = table.remove(list, 1)
	list._nb_elem = list._nb_elem - 1
	return head
end

function List:push_back(list, elem)
	-- if list._nb_elem == nil then print(debug.traceback()); assert(false) end
	list._nb_elem = list._nb_elem + 1
	table.insert(list, list._nb_elem, elem)
end
function List:push_back_unique(list, elem)
	-- if list._nb_elem == nil then print(debug.traceback()); assert(false) end
	if not List:is_elem_in_list(list,elem) then
		list._nb_elem = list._nb_elem + 1
		table.insert(list, list._nb_elem, elem)
	end
end
function List:pop_back(list)
	-- if list._nb_elem <= 0 then
	-- 	Helper:warning("pop_back on empty list "..list._name)
	-- end
	table.remove(list, list._nb_elem)
	list._nb_elem = list._nb_elem - 1
end
function List:back(list)
	-- if list._nb_elem <= 0 then
	-- 	Helper:warning("back on empty list "..list._name)
	-- end
	return list[list._nb_elem]
end
function List:back_and_pop(list)
	-- if list._nb_elem <= 0 then
	-- 	Helper:warning("pop_back on empty list "..list._name)
	-- end
	local tail = table.remove(list, list._nb_elem)
	list._nb_elem = list._nb_elem - 1
	return tail
end

function List:remove(list, elem)
	-- if not List:is_elem_in_list(list, elem) then
	-- 	Helper:warning("try to remove unexisted elem ",elem," from list "..list._name)
	-- end
	-- if active_debug_list then
	-- 	Helper:debug_print("remove_from_list : "..list._name.." elem : ",elem) end
	for i,v in ipairs(list) do
		if v == elem then
			table.remove(list, i)
			list._nb_elem = list._nb_elem - 1
		end
	end
end

function List:size(list)
	return list._nb_elem
end
function List:empty(list)
	-- if list == nil then print(debug.traceback()) end
	return list._nb_elem == 0
end
function List:clear(list)
	while not self:empty(list) do self:pop_back(list) end
end
function List:iter(list)
	local i = 0
	local n = list._nb_elem
	return function ()
		i = i + 1
		if i <= n then return list[i] end
	end
end
function List:rev(new_name, list)
	local new_list = List:new(new_name)
	for elem in self:iter(list) do
		self:push_back(new_list, elem)
	end
	return new_list
end
--[[ A SAVOIR :
	pour les listes de tables, necessite que l'operateur == soit implementé
]]
function List:is_elem_in_list(list, elem)
	for tmp in self:iter(list) do
		if elem == tmp then
			return true end
	end
	return false
end
--[[ A SAVOIR :
	pour les listes de tables, necessite que l'operateur < soit implementé
]]
function List:sort(list)
	table.sort(list)
end
function List:push_and_sort(list, elem)
	self:push_back(list,elem)
	self:sort(list)
end


-- * CASE_LIST *

function List:front_case(list)
	return MapManager:get_case(self:front(list))
end
function List:front_case_and_pop(list)
	return MapManager:get_case(self:front_and_pop(list))
end

function List:add_case_in_list(list, case)
	-- if List:is_case_in_list(list, case) then
	-- 	Helper:warning("try to add idx "..case.idx.." already in list "..list._name)
	-- end
	-- if active_debug_list then
	-- 	Helper:debug_print("add_case_in_list : "..list._name..". x,y = ",case.x,case.y) end
	self:push_back(list, case.idx)
end
function List:remove_case_from_list(list, case)
	self:remove(list, case.idx)
end

function List:is_case_in_list(list, case)
	return self:is_elem_in_list(list, case.idx)
end
function List:iter_case(list)
	local i = 0
	local n = list._nb_elem
	return function ()
		i = i + 1
		if i <= n then return MapManager:get_case(list[i]) end
	end
end
