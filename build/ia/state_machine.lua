
require 'tags'
require 'list'

StateMachine = {
	_current = nil,
	_change = Tags:v("continue"),-- tags_value de "push""pop"ou "continue"
	_executed = false,
	_states = List:new("StateMachine_states"),
}

function StateMachine:init(begin_state)
	self:push_state(begin_state)
end
function StateMachine:update()
	print("StateMachine:update) _current = "..self._current.name)
	for _,cond in pairs(self._current.pre_conditions) do
		if cond[1]() then
			self._change = Tags:v(cond[2])
			if self._change == Tags:v("push") then
				self:push_state(cond[3])
			elseif self._change == Tags:v("pop") then
				self:pop_state()
			end
		else break end
	end
	if self._change == Tags:v("continue")
		then self:execute()
		else self._change = Tags:v("continue")
		end
end

function StateMachine:action_terminated()
	-- assert(key == "push" or key == "pop") --or key == "continue")
	self._change = Tags:v("pop")
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
	-- if self._nb_elem <= 0
	-- 	then Helper:warning("execute with empty stack") end
	self._current.action()--action doit setter _change a pop si elle a atteint son objectif
	self._executed = true
	--check pos_conditions
end


-------------------------------------------------------------


	-- _changes_action = {
	-- [Tags:v("push")] = function()
	-- 	if self._current.next_state ~= nil then
	-- 		self._current = StateList[self._current.next_state] end
	-- end,
	-- [Tags:v("pop")] = function()
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
