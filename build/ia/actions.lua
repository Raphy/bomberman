
require 'path'
require 'helper'

Actions = {
	act = {
		["up"] = function() me.moveUp() end,
		["down"] = function() me.moveDown() end,
		["left"] = function() me.moveLeft() end,
		["right"] = function() me.moveRight() end,
		["put_bomb"] = function() me.putBomb() end,
		},
	_path = nil,
	-- _current_path_cases = nil,
}

--[[
TODO : mettre en place un mecanisme d'action courante, timer...
]]

function Actions:path_recalc_needed()
	return self._path == nil
	-- return StateMachine._action_duration == 0
	-- 	or self._path == nil
	-- 	or List:empty(self._path)
end
function Actions:follow_path()
	print("follow_path) type self._path : "..type(self._path))
	if self._path == nil or List:empty(self._path) then
		return false end
	return self:go_towards(List:front(self._path))
	-- return self:go_towards(List:front_and_pop(self._path))
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
			List:push_back(Tags:k(dir))
		end
	end
	return self:follow_path()
end

-- A savoir : complete random, use with cautions
function Actions:act_random()
	local dir = math.random(Tags:v("up"), Tags:v("put_bomb"))
	return self.act[dir]()
end

function Actions:go_to(x,y)
	if not MapManager:check_coord(x,y)
		then --[[Helper:debug_--]]print("goTo outside case !!"); return false end
		--car le joueur essaie d'acceder a une case hors de la map

	if self:path_recalc_needed() then
		print("Actions:goTo) player : x="..me.getX().." y="..me.getY())
		local start_idx = MapManager:coord_to_idx(me.getX(), me.getY())
		local dest_idx = MapManager:coord_to_idx(x, y)
		self._path = Path:calc_path("astar", start_idx, dest_idx)
	end
	return self:follow_path()
end

function Actions:go_towards(direction)
	print("go_towards : "..direction)
	-- verifier si c'est possible avant ?
	return self.act[direction]()
end

-- TODO : faire 2 versions, une safe et une simple
-- TODO : completer avec enemy_id defini, où prendre plutot une position d'enemy ?
function Actions:get_closer_of_one_enemy(enemy_id)
	local id = enemy_id or -1

	if self:path_recalc_needed() then
		print("path_recalc_needed")
		local start_idx = MapManager:coord_to_idx(me:getX(), me:getY())
		local dest_idx = -1
		self._path = Path:calc_path("dijkstra", start_idx, -1, "enemy")
		print("type self._path : "..type(self._path))
	end
	return self:follow_path()
end

function Actions:get_away_of_one_enemy(enemy_id)
	local id = enemy_id or -1
	Helper:to_implement()
	return me:moveUp()
end

function Actions:avoid_bomb(bomb_id)
	local id = bomb_id or -1
	-- faire un clean_map qqpart ?
	MapManager:preview_bomb(Helper:get_my_coord())-- faire un preview_all_bombs ?
	MapManager:make_type_unwalkable("preview_fire")
	MapManager:make_type_unwalkable("preview_bomb")
	local path = Path:calc_path("dijkstra", MapManager:coord_to_idx(me:getX(), me:getY()), -1, "safe_place")
	if path == nil then
		return false end--potentionnellement mort...
	self._path = path
	return self:follow_path()
end

--chaque placeBomb doit etre suivi d'un avoidBomb (sauf s'il on veut se suicider ;) )
function Actions:place_bomb()
	-- faire un clean_map qqpart ?
	MapManager:preview_bomb(Helper:get_my_coord())-- faire un preview_all_bombs ?
	MapManager:make_type_unwalkable("preview_fire")
	MapManager:make_type_unwalkable("preview_bomb")
	local path = Path:calc_path("dijkstra", MapManager:coord_to_idx(me:getX(), me:getY()), -1, "safe_place")
	MapManager:clean_preview()
	if path == nil then
		return false end
	return me:putBomb()
end
