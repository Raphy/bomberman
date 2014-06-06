
require 'list'
require 'helper'
require 'open_list_manager'
require 'map_manager'

Path = {}


function Path:get_final_path(start_idx, curr_idx)
	local path = List:new("path")
	local tmp = MapManager:get_case(curr_idx)
	while tmp.idx ~= start_idx do
		List:addCaseInList(path, tmp)
		tmp = MapManager:get_case(tmp.parent)
	end
	--TODO : reverse path
	return path
end

function Path:register_case_open(open_list, case)
	case.status = Tags:v("open")
	List:addCaseInList(open_list, case)
end

function Path:register_case_closed(open_list, closed_list, case)
	case.status = Tags:v("closed")
	List:removeCaseFromList(open_list, case)
	List:addCaseInList(closed_list, case)
end

function Path:get_side_cases(curr_idx)

	local function _insert_case(x,y, side_cases, side_open_cases)
		if not MapManager:check_coord(x,y) then return end
		local case_idx = MapManager:coord_to_idx(x,y)
		local case = MapManager:get_case(case_idx)
		-- print("cases status = "..TagsList[case.status])
		if case.status == Tags:v("unknown") and case.walkable then
			List:addCaseInList(side_cases, case)
		elseif case.status == Tags:v("open") then
			List:addCaseInList(side_open_cases, case)
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


--[[ TODO : verifier le fonctionnement du Dijkstra
		et lui faire prendre un type d'objet en parametre plutot qu'une case ?]]

--retourne le path le plus court pour aller des current a destination
function Path:calc_path(algoTag, start_idx, dest_idx)--, curr_idx, open_list, closed_list)
	local function _calc_path(algoModule, start, dest, curr, open_list, closed_list)
	
		if DEBUG == DEBUG_MAX then return nil end	
		Helper:debug_print("*calc_path : node "..curr.idx)
		if curr.idx == dest.idx then
			print("*calc_path : found "..dest.idx.."!")
			return Path:get_final_path(start.idx, curr.idx)
		end
		
		if curr.idx == start.idx
			then Path:register_case_open(open_list, curr) end
	
		local side_cases, side_open_cases = Path:get_side_cases(curr.idx)
		Path:register_case_closed(open_list, closed_list, curr)
		algoModule:open_side_cases(open_list, curr.idx, side_cases, dest)	
		
		if List:size(open_list) == 0
			then print("*calc_path : aucun path!"); return nil end
		local next_case = algoModule:get_next_open_case(open_list)
	
		DEBUG =  DEBUG + 1
		return _calc_path(algoModule, start, dest, next_case, open_list, closed_list)
	end

  	MapManager:clean_map()
	local algoModule = OpenListManagers[algoTag]
	local open_list = List:new("open_list")
	local closed_list = List:new("closed_list")
	local start = MapManager:get_case(start_idx)
	local dest = MapManager:get_case(dest_idx)

	print("Start calc_path with algo "..TagsList[algoTag].." ; start "..start_idx.." ; destination "..dest_idx)
	print("start : x y = "..start.x.." "..start.y)
	print("destination : x y = "..dest.x.." "..dest.y)
	-- TODO : trouver moyen d'optimiser en ne cleanant pas (toute ?) la map à chaque fois
	_calc_path(algoModule, start, dest, start, open_list, closed_list)
end
