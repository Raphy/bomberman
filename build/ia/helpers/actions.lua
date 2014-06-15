
require "path"
require "helper"

Actions = {
	act = {
		["up"] = function() me:moveUp() end,
		["down"] = function() me:moveDown() end,
		["left"] = function() me:moveLeft() end,
		["right"] = function() me:moveRight() end,
		["put_bomb"] = function() me:putBomb() end,
		},
	_path = nil,
	_global_direction = "up",
	_current_dest = Coord:new(1,1),
	_repeat_max = 10,
}

function Actions:init(repeat_max)
	self._repeat_max = repeat_max or 10
end
function Actions:path_recalc_needed(new_dest)
	return (StateMachine ~= nil and StateMachine._action_duration == 0)
		or self._path == nil
		or List:empty(self._path)
		or (new_dest and new_dest ~= self._current_dest)
		-- or Helper:last_action_failed()
end
function Actions:follow_path()
	if self._path == nil or List:empty(self._path) then
		return false end
	return self:go_towards(List:front_and_pop(self._path))
end

function Actions:wait()
	return true
end

function Actions:go_random()
	if self:path_recalc_needed() then
		local dir = math.random(Tags:v("up"), Tags:v("right"))
		local repeat_nb = math.random(1,10)
		self._path = List:new("random_path")
		for i=1,repeat_nb do
			List:push_back(self._path, Tags:k(dir))
		end
	end
	return self:follow_path()
end
function Actions:act_random()-- A savoir : complete random, use with cautions
	local dir = math.random(Tags:v("up"), Tags:v("put_bomb"))
	return self.act[dir]()
end

function Actions:go_to(x,y)
	if not MapManager:check_xy(x,y) then
		Helper:debug_print("goTo outside case !!")
		return false end
	if self:path_recalc_needed() then
		local start_idx = Helper:get_my_idx()
		local dest_idx = MapManager:xy_to_idx(x, y)
		if start_idx == dest_idx then
			return false end
		self._path = Path:calc_path("astar", start_idx, dest_idx)
	end
	return self:follow_path()
end
function Actions:go_towards(direction)
	return self.act[direction]()
end
function Actions:get_closer_of_obj(type)
	if self:path_recalc_needed() then
		local start_idx = Helper:get_my_idx()
		local dest_idx = -1
		MapManager:clean_map()--update?
		self._path = Path:calc_path("dijkstra", start_idx, -1, type)
	end
	return self:follow_path()
end

function Actions:get_closer_of_one_enemy(enemy_pos)--si c'est pour faire enemy_pos, autant faire un go_to !!!
	return self:get_closer_of_obj("Player")
end
function Actions:get_away_of_one_enemy(enemy_id)
	local id = enemy_id or -1
	Helper:to_implement()
	return me:moveUp()
end

function Actions:avoid_bomb()
	MapManager:update()
	HelperPrivate:preview_all_bombs()
	local path = Path:calc_path("dijkstra", Helper:get_my_idx(), -1, "mark_safe_case")
	if path == nil then
		return false end
	self._path = path
	return self:follow_path()
end
function Actions:place_bomb()
	MapManager:update()
	-- List:push_back_unique((Helper:get_my_case()).previews, "preview_bomb")
	HelperPrivate:preview_all_bombs(true)
	local path = Path:calc_path("dijkstra", Helper:get_my_idx(), -1, "mark_safe_case")
	if path == nil then
		return false end
	return me:putBomb()
end
