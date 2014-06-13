
require "list"
require "helper"
require "path_algo"
require "map_manager"

Path = {}


function Path:get_final_path(start_idx, curr_idx)
	local rev_path = List:new("rev_path")
	local tmp = MapManager:get_case(curr_idx)
	while tmp.idx ~= start_idx do
		List:add_case_in_list(rev_path, tmp)
		tmp = MapManager:get_case(tmp.parent)
	end
	local path = List:rev("path", rev_path)
	tmp = nil
	local dir_path = List:new("dir_path")
	for case in List:iter_case(path) do
		if tmp ~= nil then
			local c1,c2 = Coord:new(tmp.x, tmp.y), Coord:new(case.x, case.y)
			List:push_back(dir_path, Coord:to_direction(c1, c2))
		end
		tmp = case
	end
	return dir_path
end

function Path:register_case_open(open_list, case, sort)
	case.status = "open"
	List:add_case_in_list(open_list, case)
	if sort ~= nil and sort ~= false then
		List:sort(open_list) end
end
function Path:register_case_closed(open_list, closed_list, case)
	case.status = "closed"
	List:remove_case_from_list(open_list, case)
	List:add_case_in_list(closed_list, case)
end

function Path:get_side_cases(curr_idx)

	local function _insert_case(x,y, side_cases, side_open_cases)
		if not MapManager:check_coord(x,y) then return end
		local case_idx = MapManager:coord_to_idx(x,y)
		local case = MapManager:get_case(case_idx)
		if case.status == "unknown" and case.walkable then
			List:add_case_in_list(side_cases, case)
		elseif case.status == "open" then
			List:add_case_in_list(side_open_cases, case)
		end
	end

	local side_cases = List:new("size_cases")
	local side_open_cases = List:new("side_open_cases")
	local x,y = MapManager:idx_to_coord(curr_idx)

	_insert_case(x-1,y,side_cases,side_open_cases)
	_insert_case(x+1,y,side_cases,side_open_cases)
	_insert_case(x,y-1,side_cases,side_open_cases)
	_insert_case(x,y+1,side_cases,side_open_cases)
	return side_cases,side_open_cases
end


--[[ 
A SAVOIR :
si dest_idx == -1 :
	quelque soit l'algo choisi, dijkstra sera automatiquement utilisé
	type doit etre precisé
si dest_idx != -1 :
	type est ignoré
]]

local function check_finish(start, curr, dest, type)
	local finish = false
	if dest ~= nil and curr.idx == dest.idx then
		finish = true
	elseif dest == nil then
		local x,y = MapManager:idx_to_coord(curr.idx)
		if Helper:are_objects_in_case(x,y,type)
			or List:is_elem_in_list(curr.previews, type)
			or List:is_elem_in_list(curr.marks, type) then
				finish = true end
	end
	if finish then return true, Path:get_final_path(start.idx, curr.idx) end
	return false
end

-- local DEBUG = 0
-- local DEBUG_MAX = 2

function Path:calc_path(algo_name, start_idx, dest_idx, type)
	start_idx = math.floor(start_idx)
	dest_idx = math.floor(dest_idx)
  	MapManager:clean_map()
	local algoModule = PathAlgos[algo_name]
	local open_list = List:new("open_list")
	local closed_list = List:new("closed_list")
	local start = MapManager:get_case(start_idx)
	Helper:debug_print("start calc_path : "..start_idx)
	local dest = nil; if dest_idx ~= -1 then dest = MapManager:get_case(dest_idx) end

	local function _calc_path(start, curr, open_list, closed_list)
		-- if DEBUG == DEBUG_MAX then return true end

		if active_debug_list then Helper:debug_print("_calc_path : node "..curr.idx) end
		local finish, finish_path = check_finish(start, curr, dest, type)
		if finish == true then return finish_path end

		local side_cases, side_open_cases = Path:get_side_cases(curr.idx)
		algoModule:check_side_open_cases(curr, side_open_cases, dest)
		Path:register_case_closed(open_list, closed_list, curr)
		algoModule:open_side_cases(open_list, curr.idx, side_cases, dest)	
		if List:empty(open_list) then return nil end

		local next_case = algoModule:get_next_open_case(open_list)
		-- DEBUG =  DEBUG + 1
		return _calc_path(start, next_case, open_list, closed_list)
	end

	Path:register_case_open(open_list, start)
	-- return _calc_path(start, start, open_list, closed_list)
	local res = _calc_path(start, start, open_list, closed_list)
	if res == nil then Helper:debug_print("path not found....") else Helper:debug_print("path found !!") end
	return res
end
