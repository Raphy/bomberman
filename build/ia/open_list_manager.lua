
-- * OPEN_LIST *

OpenListManager = {
	_tag = -1
}

function OpenListManager:new(algoTag)
	tab = {}
	setmetatable(tab, self)
	self.__index = self
	self.__metatable = self
	tab._tag = algoTag
	return tab
end

--ne retourne rien
function OpenListManager:open_side_cases(open_list, curr_idx, side_cases)--, dest
	Helper:warning("This method should be override")
end

--retourne une case
function OpenListManager:get_next_open_case(open_list)
	Helper:warning("This method should be override")
end

-- * ASTAR *

AstarOpenListManager = OpenListManager:new(Tags["astar"])

function AstarOpenListManager:calc_h_cost(start, dest)
	return (math.abs(start.x - dest.x) + math.abs(start.y - dest.y))
end

function AstarOpenListManager:open_side_cases(open_list, curr_idx, side_cases, dest)
	Helper:debug_print("open cases.............. ")
	Helper:debug_print("length = "..List:size(side_cases))

	for case in List:iter_case(side_cases) do
		Helper:debug_print("open case "..case.idx)
		case.parent = curr_idx
		case.g = Map2D:get_case(case.parent).g + 1
		case.h = self:calc_h_cost(case, dest)
		case.f = case.g + case.h
	end
	for case in List:iter_case(side_cases) do
		Path:register_case_open(open_list, case)
	end
	-- TODO:inserer les side_cases en fonction de leur f_cost
end

function AstarOpenListManager:get_next_open_case(open_list)
	Helper:debug_print("next cases.............. ")
	Helper:debug_print("length = "..List:size(open_list))

	local min = -1

	for case in List:iter_case(open_list) do
		if min > case.f or min == -1 then min = case.f end
	end
	for case in List:iter_case(open_list) do
		if case.f == min then return case end
	end
	-- TODO : faire plus efficace pour recuperer le plus petit F
end

-- * DIJKSTRA *

DijkstraOpenListManager = OpenListManager:new(Tags["dijkstra"])

function DijkstraOpenListManager:open_side_cases(open_list, curr_idx, side_cases)
	Helper:debug_print("open cases.............. ")
	Helper:debug_print("length = "..List:size(side_cases))

	for case in List:iter_case(side_cases) do
		Helper:debug_print("open case "..case.idx)
		case.parent = curr_idx
		Path:register_case_open(open_list, case)
	end
end

function DijkstraOpenListManager:get_next_open_case(open_list)
	Helper:debug_print("next cases.............. ")
	Helper:debug_print("length = "..List:size(open_list))

	return List:front_case(open_list)
end

-- * OPEN_LIST_MANAGERS *

OpenListManagers = {
	[Tags["astar"]] = AstarOpenListManager,
	[Tags["dijkstra"]] = DijkstraOpenListManager
}
