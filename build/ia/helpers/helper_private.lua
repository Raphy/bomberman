
HelperPrivate = {}

function HelperPrivate:round_v(v)
	local min = math.floor(v)
	local max = math.ceil(v)
	if (max - v) <= 0.3 then
		return max end
	return min
end
function HelperPrivate:filter_pos(x,y, wanted_x,wanted_y, type)
	local round_x = self:round_v(x)
	local round_y = self:round_v(y)
	return round_x == wanted_x and round_y == wanted_y
end
function HelperPrivate:filter_objects(objects, x,y)
	local new_objects = {}
	for _,obj in pairs(objects) do
		local obj_x,obj_y = obj:getPosition()
		local obj_type = obj:getType()
		if self:filter_pos(obj_x,obj_y, x,y, obj_type) then
			table.insert(new_objects, #new_objects + 1, obj) end
	end
	return new_objects
end


function HelperPrivate:search_obj(filter, found,default, x,y,type)
	local case = Helper:map_get(x,y,1)
	if case == nil then
		return default end
	for _,obj in pairs(case) do
		if filter(obj,type) then
			return found end
	end
	return default
end


function HelperPrivate:preview_fire(coord)
	local x,y = Coord:unpack(coord)
	if not MapManager:check_xy(x,y) then
		return false end
	local idx = MapManager:xy_to_idx(x,y)
	local case = MapManager:get_case(idx)
	if not List:is_elem_in_list(case.previews, "preview_fire") then
		List:push_back(case.previews, "preview_fire") end
	return true
end
function HelperPrivate:preview_bomb(bomb_coord)
	self:preview_fire(bomb_coord)
	for radius=1,1 do
		Coord:for_each_direction(function (dir)
			self:preview_fire(Coord:from_direction(bomb_coord, dir, radius))
		end)
	end
end
function HelperPrivate:preview_all_bombs()
	for case in MapManager:iter() do
		if Helper:are_objects_in_case(case.x,case.y,"Bomb")
			or List:is_elem_in_list(case.previews, "preview_bomb") then
				self:preview_bomb(Coord:new(case.x,case.y))
		end
	end
end

function HelperPrivate:is_case_safe(case)
	-- return not Helper:are_objects_in_case_except(case.x,case.y,"Player")
	return List:empty(case.previews)
end
function HelperPrivate:mark_all_safe_cases()
	for case in MapManager:iter() do
		if self:is_case_safe(case) then
				List:push_back_unique(case.marks, "mark_safe_case")
		end
	end
end
