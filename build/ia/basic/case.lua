
local case_mt =
{
	__lt = function (lhs, rhs)
				return lhs.g < rhs.g
			end,
	-- __newindex = function (rhs)
	-- 			local new_case = rhs
	-- 			setmetatable(new_case, getmetatable(rhs))
	-- 			return new_case
	-- 		end,
	__eq = function (rhs)
				local new_case = rhs
				setmetatable(new_case, getmetatable(rhs))
				return new_case
			end,
}

Case = {}

function Case:create_case(curr_idx, i,j)
	-- assert(MapManager:check_coord(j,i))

	local case = {}
	setmetatable(case, case_mt)
	case.idx = curr_idx
	case.x,case.y = j,i
	case.walkable = true
	case.previews = List:new("case_previews_"..curr_idx)
	case.marks = List:new("case_marks_"..curr_idx)
	case.status = "unknown"--/open/closed
	case.parent = -1--idx du parent
	case.g,case.h,case.f = 0,0,0
	return case
end
function Case:clean_case(case)
	List:clear(case.previews)
	List:clear(case.marks)
	case.walkable = true
  	case.status = "unknown"
  	case.parent = -1
	case.g,case.h,case.f = 0,0,0
end
function Case:get_coord(case)
	return Coord:new(case.x,case.y)
end
function Case:are_adjacents(c1,c2)
	return Coord:are_adjacents(self:get_coord(c1),self:get_coord(c2))
end
