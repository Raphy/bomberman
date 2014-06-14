-- function initialization()

-- end

-- function play()
--    local objects = map:get(5, 5, 10, me)
--    for i=1, #objects do
--       local x, y = objects[i]:getPosition()
--       if objects[i]:getType() == "Bomb" then
-- 	 print("[IA] " .. objects[i]:getType() .. " (" .. x .. ", " .. y .. ") time " .. objects[i]:getTime())
--       end
--    end
-- end

base_path = './build/ia/'
package.path = base_path .. '?.lua;' .. package.path
package.path = base_path .. 'enemies/?.lua;' .. package.path
package.path = base_path .. 'basic/?.lua;' .. package.path
package.path = base_path .. 'helpers/?.lua;' .. package.path

active_debug = false
active_debug_list = false

-- require "ia_state"
require "ia_stalker"
-- require "ia_intro"
-- require "ia_simple"
-- require "ia_coward"

-- require "ia_unit_test"
