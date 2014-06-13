
require "tags"
require "list"

StateMachine = {
	_current = nil,
	_change = "continue",-- tags_value de "push""pop"ou "continue"
	_changes_per_frame = 3,
	_next_state = nil,
	_action_duration = 0,-- represente le nombre de frames depuis le dernier state change
	_executed = false,
	_states = List:new("StateMachine_states"),
}

function StateMachine:init(changes_per_frame)
	self:push_state("begin_state")
	self._changes_per_frame = changes_per_frame or 3
end
function StateMachine:play()
	self._executed = false
	local i = 1
	while i <= self._changes_per_frame and self._executed == false do
	  self:update()
	  i = i + 1
	end
end
function StateMachine:update()
	Helper:debug_print("StateMachine:update) _current = "..self._current.name)
	for _,cond in pairs(self._current.pre_conditions) do
		if cond[1]() then
			self._change = cond[2]
			self._next_state = cond[3]
			break
		end
	end
	if self._change == "continue" then
		self:execute()
		self._action_duration = self._action_duration + 1
	else
		if self._change == "push" then
			self:push_state(self._next_state)
		elseif self._change == "pop" then
			self:pop_state()
		end
		self._action_duration = 0
		self._change = "continue"
	end
end

function StateMachine:action_terminated()
	-- assert(key == "push" or key == "pop") --or key == "continue")
	self._change = "pop"
end

function StateMachine:push_state(state_name)
	Helper:debug_print("push_state "..state_name)
	assert(StateList[state_name] ~= nil)
	List:push_back(self._states, StateList[state_name])
	self._current = List:back(self._states)
end
function StateMachine:pop_state()
	Helper:debug_print("pop_state")
	List:pop_back(self._states)
	self._current = List:back(self._states)
end

function StateMachine:execute()
	Helper:debug_print("StateMachine: execute) _current = "..self._current.name)
	-- if self._nb_elem <= 0
	-- 	then Helper:warning("execute with empty stack") end
	self._current.action()--action doit setter _change a pop si elle a atteint son objectif
	self._executed = true
	--check pos_conditions
end


-------------------------------------------------------------


	-- _changes_action = {
	-- ["push"] = function()
	-- 	if self._current.next_state ~= nil then
	-- 		self._current = StateList[self._current.next_state] end
	-- end,
	-- ["pop"] = function()
	-- 	self:pop_state()
	-- 	self._current = StateList:back()
	-- end,
	-- }


--[[
	a appeler a chaque frame,
	qu'il y ai eu un changement d'etat ou pas
]]
-- function StateMachine:update()
-- 	for cond in List:iter(self._current.pre_conditions) do
-- 		-- if cond[1]() then cond[2]() end
-- 	end
-- 	if self._current.enable_exec
-- 		then self._current:action()
-- 		else List:pop_back(self._states)
-- 			self._current = List:back(self._states)
-- 	end
-- 	--stocker le retour de action ?
-- 	for cond in List:iter(self._current.post_conditions) do
-- 		if cond[1]() then cond[2]() end
-- 	end
-- end
