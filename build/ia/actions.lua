
require 'path'
require 'helper'

Actions = {
	act = {
		[0] = function(player) player.moveUp(player) end,
		function(player) player.moveDown(player) end,
		function(player) player.moveLeft(player) end,
		function(player) player.moveRight(player) end,
		function(player) player.putBomb(player) end,
		}
	}

function Actions:wait()
	return true
end

-- TODO : "lisser" le random
function Actions:goRandom(player)
	local dir = math.random(0, 3)
	return self.act[dir](player)
end

function Actions:actRandom(player)
	local dir = math.random(0, 4)
	return self.act[dir](player)
end

function Actions:goTo(player,x,y)
	if not Map2D:check_coord(x,y) then --[[Helper:debug_--]]print("goTo outside case !!"); return false end
		--car le joueur essaie d'acceder a une case hors de la map

	print("Actions:goTo) player : x="..player.getX().." y="..player.getY())
	local start_idx = Map2D:coord_to_idx(player.getX(), player.getY())
	local dest_idx = Map2D:coord_to_idx(x, y)

	Path:calc_path(Tags["dijkstra"], start_idx, dest_idx)
	Path:calc_path(Tags["astar"], start_idx, dest_idx)

	return player:moveUp()
end

function Actions:goTowards(player,direction)
	return player:moveUp()
end

function Actions:getCloserOfOneEnemy(player,enemyId)
	local id = enemyId or -1
	return player:moveUp()
end

function Actions:getAwayOfOneEnemy(player,enemyId)
	local id = enemyId or -1
	return player:moveUp()
end

function Actions:avoidBomb(player,bombId)
	return player:moveUp()
end
