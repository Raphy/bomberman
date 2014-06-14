
require "tags"
require "helper"

-- * PATH_ALGO *

PathAlgo = {
	_name = "path_algo",
}

function PathAlgo:new(algo_name)
	tab = {}
	setmetatable(tab, self)
	self.__index = self
	self.__metatable = self
	tab._name = algo_name
	return tab
end

--ne retourne rien
function PathAlgo:open_side_cases(open_list, curr_idx, side_cases)--, dest
	Helper:to_override()
end
--retourne une case
function PathAlgo:get_next_open_case(open_list)
	Helper:to_override()
end
function PathAlgo:check_side_open_cases(curr, side_open_cases)--, dest)
	Helper:to_override()
end


-- * ASTAR *

Astar = PathAlgo:new("astar")

local function calc_h_cost(start, dest)
	return (math.abs(start.x - dest.x) + math.abs(start.y - dest.y))
end

function Astar:open_side_cases(open_list, curr_idx, side_cases, dest)
	assert(dest ~= nil)
	for case in List:iter_case(side_cases) do
		case.parent = curr_idx
		case.g = MapManager:get_case(case.parent).g + 1
		case.h = calc_h_cost(case, dest)
		case.f = case.g + case.h
	end
	for case in List:iter_case(side_cases) do
		Path:register_case_open(open_list, case, true)
	end
end
function Astar:get_next_open_case(open_list)
	return List:front_case(open_list)
end
function Astar:check_side_open_cases(curr, side_open_cases, dest)
	assert(dest ~= nil, "astar needs a destination")
	for case in List:iter_case(side_open_cases) do
		if case.g > curr.g + 1
			and Case:are_adjacents(case,curr) then
			case.parent = curr.idx
			case.g = curr.g + 1
			case.h = calc_h_cost(case, dest)
			case.f = case.g + case.h
		end
	end
end

-- * DIJKSTRA *

Dijkstra = PathAlgo:new("dijkstra")

function Dijkstra:open_side_cases(open_list, curr_idx, side_cases, dest)
	for case in List:iter_case(side_cases) do
		case.parent = curr_idx
		case.g = MapManager:get_case(case.parent).g + 1
		if dest ~= nil then
			case.h = calc_h_cost(case, dest)
			case.f = case.g + case.h
		end
	end
	for case in List:iter_case(side_cases) do
		Path:register_case_open(open_list, case)
	end
end
function Dijkstra:get_next_open_case(open_list)
	return List:front_case(open_list)
end
function Dijkstra:check_side_open_cases(curr, side_open_cases, dest)
	for case in List:iter(side_open_cases) do
		if case.g > curr.g + 1
			and Case:are_adjacents(case,curr) then
			case.parent = curr.idx
			case.g = curr.g + 1
			if dest ~= nil then
				case.h = calc_h_cost(case, dest)
				case.f = case.g + case.h
			end
		end
	end
end

-- * GLOUTON *

Glouton = PathAlgo:new("glouton")

function Glouton:open_side_cases(open_list, curr_idx, side_cases)
	for case in List:iter_case(side_cases) do
		case.parent = curr_idx
		Path:register_case_open(open_list, case)
	end
end
function Glouton:get_next_open_case(open_list)
	return List:front_case(open_list)
end
function Dijkstra:check_side_open_cases(curr, side_open_cases, dest)
	return nil
end

-- * OPEN_LIST_MANAGERS *

PathAlgos = {
	["astar"] = Astar,
	["dijkstra"] = Dijkstra,
	["glouton"] = Glouton,
}
