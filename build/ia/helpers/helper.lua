
require "api"
require "tags"
require "helper_private"

Helper = {
	_frames_since_action = 0,
}

function Helper:initialization_base(repeat_max, vision_size)
	math.randomseed(os.time())
	Coord:init()
	MapManager:init(10,10, vision_size)
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

function Helper:warning(...)
	print("WARNING : ")
	print(...)
	print(debug.traceback())
	print("...WARNING")
end
function Helper:to_implement()
	print("ERROR : FUNCTION NOT IMPLEMENTED")
	print(debug.traceback())
end
function Helper:to_override()
	print("WARNING : this method should be override")
	print(debug.traceback())
end
function Helper:debug_print(...)
	if active_debug then
		print("\t ")
		print(...)
	end
end
function Helper:debug_dump_list(list)
	if active_debug then
		self:debug_print("DUMP ",list._name," : ")
		for elem in List:iter(list) do
			self:debug_print(elem)
			-- self:debug_print(elem.idx)
		end
		self:debug_print("...DUMP END")
	end
end
function Helper:display_objects(objects)
	if active_debug_objects then
  		for i,obj in ipairs(objects) do
  		   local x, y = obj:getPosition()
  		   local type = obj:getType()
			print("[IA] obj ",type,"-> ",x,y)
  		end
  end
end

-- * API_HELPER *

function Helper:get_my_idx()
	return MapManager:xy_to_idx(self:get_my_position())
end
function Helper:get_my_coord()
	return Coord:new(self:get_my_position())
end
function Helper:get_my_position()
	local x,y = me:getPosition()
	return x+1,y+1--arrondir directement ici ?
end

function Helper:map_get(x,y,distance)
	local x,y = math.ceil(x)-1,math.ceil(y)-1
	return HelperPrivate:filter_objects(map:get(x,y,2,me), x,y)
end
--[[TODO : faire la meme chose avec la position des gameobjects]]



-- * OBJECTS_HELPER *

function Helper:are_objects_in_case(x,y,type)
	local function _filter(obj,type)
		return obj:getType() ~= "Me" and type == nil or type == obj:getType()
	end
	return HelperPrivate:search_obj(_filter, true,false, x,y,type)
end
function Helper:are_objects_in_case_except(x,y,type)
	assert(type ~= nil, "are_objects_in_case_except : type expected")
	local function _filter(obj,type)
		return obj:getType() ~= "Me" and type ~= obj:getType()
	end
	return HelperPrivate:search_obj(_filter, true,false, x,y,type)
end
function Helper:get_objects_from_case(x,y,type,objects)
	local o = objects or {}
	local case = self:map_get(x,y,1)
	if case == nil then
		return nil end
	for _,obj in pairs(case) do
		if obj:getType() ~= "Me" and type == nil or type == obj:getType() then
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



-- * BOMB_HELPER *

function Helper:preview_safe_cases()
	MapManager:update()
	HelperPrivate:preview_all_bombs()
	-- MapManager:make_type_unwalkable("preview_fire")
	-- MapManager:make_type_unwalkable("preview_bomb")
	HelperPrivate:mark_all_safe_cases()
	MapManager:clean_previews()
	MapManager:clean_marks()
	-- MapManager:make_type_walkable("preview_fire")
	-- MapManager:make_type_walkable("preview_bomb")
end

-- * WRAPPERS *

function Helper:last_action_succeed()
	assert(StateMachine ~= nil, "this check could only be done with a StateMachine")
	return StateMachine._action_status.status
end
function Helper:last_action_failed()
	assert(StateMachine ~= nil, "this check could only be done with a StateMachine")
	return not StateMachine._action_status.status
end
function Helper:obj_in_view(type)
	return self:are_objects_around(type,Helper:get_my_position(),MapManager.size / 2)
end
function Helper:obj_in_map(type) --[[ est ce une bonne idee ?? ]]
	return self:are_objects_around(type,Helper:get_my_position(),MapManager.size / 2)
end
function Helper:obj_in_action_range(type)
	return self:are_objects_around(type,Helper:get_my_position(),2)
end
function Helper:is_place_safe()
	return not self:are_objects_around("Bomb",Helper:get_my_position(),3)
end
function Helper:is_place_dangerous()
	return self:are_objects_around("Bomb",Helper:get_my_position(),3)
end
