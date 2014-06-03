
require 'list'
require 'helper'

function create_case(curr_idx, i,j)
	return {
		idx = curr_idx,
		walkable = not Helper:areObjectsInCase(map,i,j,nil),
		status = Tags["unknown"],--/open/closed
		parent = -1,--idx du parent
		x,y = j,i,
		g,h,f = 0,0,0
	}
end

cases_map = {}

for i=1,Helper.h do
	for j=1,Helper.w do
		local curr_idx = Helper:coord_to_idx(j,i)
		cases_map[curr_idx] = create_case(curr_idx,i,j)
		if (curr_idx > 61 and curr_idx < 69) or (curr_idx > 51 and curr_idx < 54) then
			cases_map[curr_idx].walkable = false end
	end
end

function calc_h_cost(start, dest)
	return (maths.abs(start.x - dest.x) + maths.abs(start.y - dest.y))
end

function get_next_open_case(open_list)
	local min = -1

	for case in List:iter_case(cases_map, open_list) do
		if min > case.f or min == -1 then min = case.f end
	end
	for case in List:iter_case(cases_map, open_list) do
		if case.f == min then return case end
	end
end

local function get_final_path(start_idx, curr_idx)
	local path = List:new("path")
	local tmp = cases_map[curr_idx]
	while tmp.idx ~= start_idx do
		List:addCaseInList(path, tmp)
		tmp = cases_map[tmp.parent]
	end
	--TODO : reverse path
	return path
end

function register_case_open(open_list, case)
	case.status = Tags["open"]
	List:addCaseInList(open_list, case)
end

function register_case_closed(open_list, closed_list, case)
	case.status = Tags["closed"]
	List:removeCaseFromList(open_list, case)
	List:addCaseInList(closed_list, case)
end

function open_side_cases(open_list, curr_idx, side_cases)
	-- print("open cases.............. ")
	-- print("length = "..List:size(side_cases))

	for case in List:iter_case(cases_map, side_cases) do
		-- print("open case "..case.idx)
		case.parent = curr_idx
		-- case.g = cases_map[case.parent].g + 10
		-- case.h = calc_h_cost(case, dest)
		-- case.f = case.g + case.h
		case.g = 10
		case.h = 50
		case.f = 60
	end
	for case in List:iter_case(cases_map, side_cases) do
		register_case_open(open_list, case)
	end
	-- TODO:inserer les side_cases en fonction de leur f_cost
end

local function get_side_cases(curr_idx)
	local function _insert_case(x,y, side_cases, side_open_cases)
		local case_idx = Helper:coord_to_idx(x,y)
		local case = cases_map[case_idx]
		-- print("cases status = "..TagsList[case.status])
		if case.status == Tags["unknown"] and case.walkable then
			List:addCaseInList(side_cases, case)
		elseif case.status == Tags["open"] then
			List:addCaseInList(side_open_cases, case)
		end
	end

	local side_cases = List:new("size_cases")
	local side_open_cases = List:new("side_open_cases")
	local x,y = Helper:idx_to_coord(curr_idx)

	-- TODO : check si les nouveaux x et y sont bien dans la map
	_insert_case(x-1,y,side_cases,side_open_cases)
	_insert_case(x+1,y,side_cases,side_open_cases)
	_insert_case(x,y-1,side_cases,side_open_cases)
	_insert_case(x,y+1,side_cases,side_open_cases)

	-- for tmp_x=x-1, x+1 do
	-- 	for tmp_y=y-1, y+1 do
	-- 		if tmp_x > 0 and tmp_x < Helper.w
	-- 			and tmp_y > 0 and tmp_y < Helper.h
	-- 		then _insert_case(tmp_x,tmp_y,side_cases,side_open_cases) end
	-- 	end
	-- end
	return side_cases,side_open_cases
end

local DEBUG = 0
local DEBUG_MAX = 10


--retourne le path le plus court pour aller des current a destination
function calc_path_astar(start_idx, dest_idx, curr_idx, open_list, closed_list)

	if DEBUG == DEBUG_MAX then return nil end

	print("*astar : node "..curr_idx)

	if curr_idx == dest_idx then
		print("*astar : found "..dest_idx.."!")
		return get_final_path(start_idx, curr_idx)
	end
	
	local current = cases_map[curr_idx]
	local dest = cases_map[dest_idx]
	if curr_idx == start_idx
		then register_case_open(open_list, current) end

	local side_cases, side_open_cases = get_side_cases(curr_idx)
	register_case_closed(open_list, closed_list, current)	
	open_side_cases(open_list, curr_idx, side_cases)	
	
	if List:size(open_list) == 0 then
		print("*astar : aucun path!")
		return nil
	end
	local next_case = get_next_open_case(open_list)

	DEBUG =  DEBUG + 1

	return calc_path_astar(start_idx, dest_idx, next_case.idx, open_list, closed_list)
	-- return nil
end




function calc_path_dijkstra(destination, curr_idx, open_list, closed_list)
	-- TODO
	return false
end
