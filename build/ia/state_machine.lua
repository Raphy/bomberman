
require "tags"
require "list"

StateMachine = {
	_current = nil,
	_change = "continue",-- /"push"/"pop"
	_changes_per_frame = 3,
	_next_state = nil,
	_action_duration = 0,-- represente le nombre de frames depuis le dernier state change
	_last_action_status = false,
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
	Helper:debug_print("		StateMachine:update) "..self._current.name)
	for _,cond in pairs(self._current.pre_conditions) do
		if cond[1]() then
			self._change = cond[2]
			self._next_state = cond[3]
			break
		end
	end
	if self._change == "continue" then
		Helper:increase_frames()
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
	Helper:debug_print("		StateMachine: execute) "..self._current.name)
	if self._current == nil
		then Helper:warning("execute with empty stack") end
	self._last_action_status = self._current.action()
	self._executed = true
end
