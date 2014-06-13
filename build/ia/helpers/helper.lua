
require "api"
require "tags"

Helper = {
	_frames_since_action = 0,
}

function Helper:initialization_base(repeat_max, vision_size)
	math.randomseed(os.time())
	Coord:init()
	MapManager:init(100,100, vision_size)
	Actions:init(repeat_max)
end

-- * TIME_HELPER *

function Helper:get_current_time()
	self:to_implement()
	return 0
end
function Helper:get_elapsed_time(origin_time)
	self:to_implement()
	return 0
end
function Helper:get_frames_since_action()
	return self._frames_since_action
end
function Helper:register_frame_action()
	self._frames_since_action = 0
end
function Helper:increase_frames()
	self._frames_since_action = self._frames_since_action + 1
end

-- * DEV_HELPER *

function Helper:warning(msg)
	print("WARNING...")
	print(debug.traceback())
	print("...WARNING : "..msg)
end
function Helper:to_implement()
	print("ERROR : FUNCTION NOT IMPLEMENTED")
	print(debug.traceback())
end
function Helper:to_override()
	print("WARNING : this method should be override")
	print(debug.traceback())
end
function Helper:debug_print(msg)
	if active_debug then print("DEBUG : "..msg) end
end
function Helper:debug_dump_list(list)
	if active_debug then
		self:debug_print("DUMP ",list._name," : ")
		for elem in List:iter_case(list) do
			self:debug_print(elem.idx)
		end
		self:debug_print("...DUMP END")
	end
end

-- * OBJECTS_HELPER *

function Helper:get_my_coord()
	return Coord:new(me:getPosition())
end

local function search_obj(filter, found,default, x,y,type)
	local case = map:get(x,y,1)
	if case == nil then
		return default end
	for _,obj in pairs(case) do
		if filter(obj,type) then
			return found end
	end
	return default
end

function Helper:are_objects_in_case(x,y,type)
	local function _filter(obj,type)
		return type == nil or type == obj:getType()
	end
	return search_obj(_filter, true,false, x,y,type)
	-- local case = map:get(x,y,1)
	-- if case == nil then
	-- 	return false end
	-- for _,obj in pairs(case) do
	-- 	if type == nil or type == obj:getType() then
	-- 		return true end
	-- end
	-- return false
end
function Helper:are_objects_in_case_except(x,y,type)
	assert(type ~= nil, "are_objects_in_case_except : type expected")
	local function _filter(obj,type)
		return type ~= obj:getType()
	end
	return search_obj(_filter, true,false, x,y,type)
	-- local case = map:get(x,y,1)
	-- if case == nil then
	-- 	return false end
	-- for _,obj in pairs(case) do
	-- 	if type ~= obj:getType() then
	-- 		return true end
	-- end
	-- return false
end
function Helper:get_objects_from_case(x,y,type,objects)
	local o = objects or {}
	local case = map:get(x,y,1)
	if case == nil then
		return nil end
	for _,obj in pairs(case) do
		if type == nil or type == obj:getType() then
			table.insert(o, obj) end
	end
	return o
end

function Helper:get_all_objects(type)
	local o = {}
	for case in MapManager:iter() do
		o = self:get_objects_from_case(case.x,case.y,type,o)
	end
	return o
end
function Helper:are_objects(type)
	for case in MapManager:iter() do
		if self:are_objects_in_case(case.x,case.y,type,o) then
			return true end
	end
	return false
end

function Helper:are_objects_around(type,x,y,radius)
	local r = radius or 1
	local vision_state = MapManager._vision.active
	MapManager:set_vision_activate(Coord:new(x,y), r)
	local found = self:are_objects(type)
	if not vision_state then MapManager:desactivate_vision() end
	return found
end
function Helper:get_objects_around(type,x,y,radius)
	local r = radius or 1
	local vision_state = MapManager._vision.active
	MapManager:set_vision_activate(Coord:new(x,y), r)
	local o = self:get_all_objects(type)
	if not vision_state then MapManager:desactivate_vision() end
	return o
end
function Helper:enemy_in_view()
	return not Helper:are_objects_around("enemy",me:getPosition(),MapManager.size / 2)
end


-- * BOMB_HELPER *

local function is_case_safe(case)
	return not Helper:are_objects_in_case_except(case.x,case.y,"enemy")
		and List:empty(case.previews)
end

function Helper:is_place_safe()
	return not self:are_objects_around("bomb",me:getPosition(),3)
end
function Helper:is_place_dangerous()
	return not self:is_place_safe()
end

function Helper:clean_preview()
	for case in MapManager:iter() do
		List:clear(case.previews)
	end
end
function Helper:preview_bomb(bomb_coord)
	local function _preview_fire(coord)
		local x,y = Coord:unpack(coord)
		if not MapManager:check_coord(x,y) then
			return false end
		local case = MapManager:get_case(MapManager:coord_to_idx(x,y))
		if not List:is_elem_in_list(case.previews, "preview_fire") then
			List:push_back(case.previews, "preview_fire") end
		return true
	end
	_preview_fire(bomb_coord)
	for radius=1,3 do
		local function _call_preview(dir)
			_preview_fire(Coord:from_direction(bomb_coord, dir, radius))
		end
		Coord:apply_to_all_directions(_call_preview)
	end
end

function Helper:mark_all_safe_cases()
	for case in MapManager:iter() do
		if is_case_safe(case)
			and not List:is_elem_in_list(case.marks, "safe_place") then
				List:push_back(case.marks, "safe_place") end
	end
end
function Helper:preview_all_bombs()
	for case in MapManager:iter() do
		if self:are_objects_in_case(case.x,case.y,"bomb")
			or List:is_elem_in_list(case.previews, "preview_bomb") then
				self:preview_bomb(Coord:new(case.x,case.y))
		end
	end
end
