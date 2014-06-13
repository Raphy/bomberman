function initialization()

end

function play()
   print("[[ - START - ]]")
   local objects = map:get(0, 0, 100, me)
   for i=1, #objects do
      local x, y = objects[i]:getPosition()
      print("[IA] " .. objects[i]:getType() .. " (" .. x .. ", " .. y .. ")")
   end
   print("   -  END  -   ")
   print("")
end

--[[
base_path = './build/ia/'
package.path = base_path .. '?.lua;' .. package.path
package.path = base_path .. 'enemies/?.lua;' .. package.path
package.path = base_path .. 'basic/?.lua;' .. package.path
package.path = base_path .. 'helpers/?.lua;' .. package.path

active_debug = false
active_debug_list = false

-- require "ia_state"
-- require "ia_intro"
-- require "ia_simple"
-- require "ia_coward"
-- require "ia_stalker"

require "ia_unit_test"
]]
