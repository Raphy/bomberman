
require 'tags'
require 'helper'

-- * PATH_ALGO *

PathAlgo = {
	_tag = -1
}

function PathAlgo:new(algo_tag)
	tab = {}
	setmetatable(tab, self)
	self.__index = self
	self.__metatable = self
	tab._tag = algo_tag
	return tab
end

--ne retourne rien
function PathAlgo:open_side_cases(open_list, curr_idx, side_cases)--, dest
	Helper:warning("This method should be override")
end
--retourne une case
function PathAlgo:get_next_open_case(open_list)
	Helper:warning("This method should be override")
end


--[[
TODO: adapter g_cost quand il devient plus petit
]]

-- * ASTAR *

Astar = PathAlgo:new("astar")

function Astar:calc_h_cost(start, dest)
	return (math.abs(start.x - dest.x) + math.abs(start.y - dest.y))
end

function Astar:open_side_cases(open_list, curr_idx, side_cases, dest)
	assert(dest ~= nil)
	for case in List:iter_case(side_cases) do
		case.parent = curr_idx
		case.g = MapManager:get_case(case.parent).g + 1
		case.h = self:calc_h_cost(case, dest)
		case.f = case.g + case.h
	end
	for case in List:iter_case(side_cases) do
		Path:register_case_open(open_list, case)
	end
	-- TODO:inserer les side_cases en fonction de leur f_cost
end

function Astar:get_next_open_case(open_list)
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

Dijkstra = PathAlgo:new("dijkstra")

function Dijkstra:open_side_cases(open_list, curr_idx, side_cases)
	for case in List:iter_case(side_cases) do
		case.parent = curr_idx
		case.g = MapManager:get_case(case.parent).g + 1
		case.h = self:calc_h_cost(case, dest)
	end
	for case in List:iter_case(side_cases) do
		Path:register_case_open(open_list, case)
	end
end

function Dijkstra:get_next_open_case(open_list)
	return List:front_case(open_list)
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

-- * OPEN_LIST_MANAGERS *

PathAlgos = {
	["astar"] = Astar,
	["dijkstra"] = Dijkstra,
	["glouton"] = Glouton,
}
