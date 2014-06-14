
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
	-- return round_x == wanted_x and round_y == wanted_y
	local res = round_x == wanted_x and round_y == wanted_y
	-- if res
	-- 	then print("\tOK : ",type,x,round_x,wanted_x)
	-- 	print("\t\t",y,round_y,wanted_y)
	-- 	else print("\tFAIL : ",type,x,round_x,wanted_x)
	-- 	print("\t\t",y,round_y,wanted_y)
	-- end
	return res
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


function HelperPrivate:is_case_safe(case)
	return not Helper:are_objects_in_case_except(case.x,case.y,"Player")
		and List:empty(case.previews)
end
