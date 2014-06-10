
require 'path'
require 'helper'

Actions = {
	act = {
		function() me.moveUp(me) end,
		function() me.moveDown(me) end,
		function() me.moveLeft(me) end,
		function() me.moveRight(me) end,
		function() me.putBomb(me) end,
		}
	}

--[[
TODO : mettre en place un mecanisme d'action courante, sauvegarde de path, timer...
]]

function Actions:wait()
	return true
end

-- TODO : "lisser" le random
function Actions:go_random()
	local dir = math.random(1, 4)
	return self.act[dir]()
end

function Actions:act_random()
	local dir = math.random(1, 5)
	return self.act[dir]()
end

function Actions:go_to(x,y)

	if not MapManager:check_coord(x,y)
		then --[[Helper:debug_--]]print("goTo outside case !!"); return false end
		--car le joueur essaie d'acceder a une case hors de la map

	print("Actions:goTo) player : x="..me.getX().." y="..me.getY())
	local start_idx = MapManager:coord_to_idx(me.getX(), me.getY())
	local dest_idx = MapManager:coord_to_idx(x, y)

	Path:calc_path(Tags:v("dijkstra"), start_idx, dest_idx)
	Path:calc_path(Tags:v("astar"), start_idx, dest_idx)

	return me:moveUp()
end

function Actions:go_towards(direction)
	Helper:to_implement()
	return me:moveUp()
end

-- TODO : faire 2 versions, une safe et une simple
function Actions:get_closer_of_one_enemy(enemy_id)
	local id = enemy_id or -1
	Helper:to_implement()
	return me:moveUp()
end

function Actions:get_away_of_one_enemy(enemy_id)
	local id = enemy_id or -1
	Helper:to_implement()
	return me:moveUp()
end

function Actions:avoid_bomb(bomb_id)
	Helper:to_implement()
	return me:moveUp()
end

--chaque placeBomb doit etre suivi d'un avoidBomb (sauf s'il on veut se suicider ;) )
function Actions:place_bomb()
	--chercher un endroit "safe" où la placer ?
	Helper:to_implement()
	return me:putBomb()
end
