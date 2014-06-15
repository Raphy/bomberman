
require "tags"
require "list"

StateMachine = {
	_current = nil,
	_changes_per_frame,_max_stack_size = 3, 1000,
	_executed = false,
	_change = "continue",
	_next_state = nil,
	_states = List:new("StateMachine_states"),
	_action_duration = 0,
	_action_status = {
		status = false,
		duration = 0,
		duration_max = 10,
	},
	_cool_down = {
		active = false,
		duration = 0,
		duration_max = 10,
	},
}

function StateMachine:init(changes_per_frame, max_stack_size,
									status_duration_max, cool_down_duration_max)
	self:push_state("begin_state")
	self._changes_per_frame = changes_per_frame or 3
	self._max_stack_size = max_stack_size or 1000
	self._action_status.duration_max = status_duration_max or 10
	self._cool_down.duration_max = cool_down_duration or 10
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
	if StateMachine:cool_down() then return nil end
	Helper:debug_print("		StateMachine:update) "..self._current.name)
	self:check_conds(self._current.pre_conditions)
	if self._change ~= "continue"
		then self:check_state_change()
		else self:execute() end
	self:check_conds(self._current.post_conditions)
	if self._change ~= "continue" then
		self:check_state_change() end
end

function StateMachine:action_terminated()
	-- assert(key == "push" or key == "pop") --or key == "continue")
	self._change = "pop"
end
function StateMachine:cool_down()
	if self._cool_down.active then
		self._cool_down.duration = self._cool_down.duration + 1
		if self._cool_down.duration == self._cool_down.duration_max then
			self._cool_down.duration = 0
			self._cool_down.active = false
		end
		return true
	end
	return false
end
function StateMachine:register_status(status)
	if status == self._last_action_status then
		self._action_status.duration = self._action_status.duration + 1
	else
		self._last_action_status = status
		self._action_status.duration = 0
	end
end

function StateMachine:push_state(state_name)
	Helper:debug_print("push_state ",state_name)
	if StateList[state_name] == nil then
		print("unexisting state ",state_name)
	end
	assert(StateList[state_name] ~= nil)
	List:push_back(self._states, StateList[state_name])
	self._current = List:back(self._states)
end
function StateMachine:pop_state()
	Helper:debug_print("pop_state")
	List:pop_back(self._states)
	self._current = List:back(self._states)
end
function StateMachine:cut_stack(cut_size)
	for i=1,cut_size do
		List:pop(self._states)
	end
	List:push(self._states, StateList["begin_state"])
end

function StateMachine:check_conds(conds)
	for _,cond in pairs(conds) do
		if cond[1]() == true then
			self._change = cond[2]
			self._next_state = cond[3]
			break
		end
	end
end
function StateMachine:check_state_change()
	if self._change == "push" then
		self:push_state(self._next_state)
	elseif self._change == "pop" then
		self:pop_state()
	end
	self._action_duration = 0
	self._change = "continue"
	local size = List:size(self._states)
	if size > self._max_stack_size then
		self:cut_stack(size / 2) end
end
function StateMachine:execute()
	Helper:increase_frames()
	Helper:debug_print("		StateMachine: execute) "..self._current.name)
	if self._current == nil
		then Helper:warning("execute with empty stack") end
	local status = self._current.action()
	self:register_status(status)
	self._executed = true
	self._action_duration = self._action_duration + 1
	if status == false and self._action_status.duration > 10 then
		self._cool_down.active = true end
end
