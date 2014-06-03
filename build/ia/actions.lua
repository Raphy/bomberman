
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
	print("Actions:goTo) player : x="..player.getX().." y="..player.getY())
	local start_idx = Helper:coord_to_idx(player.getX(), player.getY())
	local dest_idx = Helper:coord_to_idx(x, y)
	local open_list = List:new("open_list")
	local closed_list = List:new("closed_list")

	calc_path_astar(start_idx, dest_idx, start_idx, open_list, closed_list)

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
