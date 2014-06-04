
Map2D = {
	_map2D = nil,
	w,h,size = -1,-1,-1,
}


-- return true if x and y are valids coordinates in the map
function Map2D:check_coord(x,y)
	return x > 0 and y > 0 and x <= self.w and y <= self.h
end

function Map2D:coord_to_idx(x,y)
	-- debug_print(debug.traceback())
	local idx = (y - 1) * self.w + x
	-- debug_print("coord_to_idx : i="..idx.." x="..x.." y="..y)
	return idx
end

-- retourne x,y
function Map2D:idx_to_coord(idx)
	local x = idx % self.w
	local y = math.ceil(idx / self.w) --+ 1
	-- debug_print("idx_to_coord : i="..idx.." x="..x.." y="..y)
	return x,y--TODO : verifier les formules
end


function Map2D:create_case(curr_idx, i,j)
	local case = {}
	case.idx = curr_idx
	case.walkable = not Helper:areObjectsInCase(map,i,j,nil)
	case.status = Tags["unknown"]--/open/closed
	case.parent = -1--idx du parent
	case.x,case.y = j,i
	case.g,case.h,case.f = 0,0,0
	return case
end

function Map2D:get_case(i)
	if i <= 0 or i > self.size then
		Helper:warning("get_case : idx="..i.." is outside the map")
	end
	return self._map2D[i]
end
-- function Map2D:set_case(i, case)
-- 	-- TODO : check i
-- 	return self._map2D[i]
-- end

function Map2D:clean_map()
  for i=1,Map2D.h do
    for j=1,Map2D.w do
      local curr_idx = Map2D:coord_to_idx(j,i)
      local case = self._map2D[curr_idx]
     	case.status = Tags["unknown"]
     	case.parent = -1
		case.g,case.h,case.f = 0,0,0
    end
  end
end

function Map2D:init_map(w,h)
	self._map2D = {}
	self.w, self.h = w, h
	self.size = self.w * self.h
	print("init map2D of size "..self.size.." (w = "..self.w.." and h = "..self.h..")")

  for i=1,Map2D.h do
    for j=1,Map2D.w do
      local curr_idx = Map2D:coord_to_idx(j,i)
      self._map2D[curr_idx] = Map2D:create_case(curr_idx,i,j)
      -- if (curr_idx > 61 and curr_idx < 69) or (curr_idx > 51 and curr_idx < 54) then
        -- self._map2D[curr_idx].walkable = false end
    end
  end
end
