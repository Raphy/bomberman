
require 'list'
require 'helper'
require 'path_algo'
require 'map_manager'

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

function Path:register_case_open(open_list, case)
	case.status = "open"
	List:add_case_in_list(open_list, case)
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
		-- print("cases status = "..Tags[case.status])
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

local DEBUG = 0
local DEBUG_MAX = 10000


--[[ 
A SAVOIR :
si dest_idx == -1 :
	quelque soit l'algo choisi, dijkstra sera automatiquement utilisé
	type doit etre precisé
si dest_idx != -1 :
	type est ignoré
]]

--[[ TODO : verifier le fonctionnement du Dijkstra]]

--retourne le path le plus court pour aller des current a destination
function Path:calc_path(algo_name, start_idx, dest_idx, type)
  	MapManager:clean_map()
	local algoModule = PathAlgos[algo_name]
	local open_list = List:new("open_list")
	local closed_list = List:new("closed_list")
	local start = MapManager:get_case(start_idx)
	local dest = nil
	if dest_idx ~= -1 then dest = MapManager:get_case(dest_idx) end

	local function _calc_path(start, curr, open_list, closed_list)	
		if DEBUG == DEBUG_MAX then return nil end	
		-- Helper:debug_print("*calc_path : node "..curr.idx)
		if dest ~= nil and curr.idx == dest.idx then
			print("*calc_path : found !")
			return Path:get_final_path(start.idx, curr.idx)
		elseif dest == nil then
			local x,y = MapManager:idx_to_coord(curr.idx)
			-- print("x = "..x.." y = "..y)
			if Helper:are_objects_in_case(x,y,type) then
			print("*calc_path : found !")
				return Path:get_final_path(start.idx, curr.idx)
			end
		end
		
		if curr.idx == start.idx then
			Path:register_case_open(open_list, curr) end
	
		local side_cases, side_open_cases = Path:get_side_cases(curr.idx)
		Path:register_case_closed(open_list, closed_list, curr)
		algoModule:open_side_cases(open_list, curr.idx, side_cases, dest)	
		
		if List:size(open_list) == 0 then
			print("*calc_path : aucun path!")
			return nil end
		local next_case = algoModule:get_next_open_case(open_list)
	
		DEBUG =  DEBUG + 1
		return _calc_path(start, next_case, open_list, closed_list)
	end

	print("Start calc_path with algo "..algo_name.." ; start "..start_idx.." ; destination "..dest_idx)
	print("start : x y = "..start.x.." "..start.y)
	-- print("destination : x y = "..dest.x.." "..dest.y)
	print("type = "..type)
	-- TODO : trouver moyen d'optimiser en ne cleanant pas (toute ?) la map à chaque fois
	return _calc_path(start, start, open_list, closed_list)
end
