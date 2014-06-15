base_path = './build/ia/'
package.path = base_path .. '?.lua;' .. package.path
package.path = base_path .. 'enemies/?.lua;' .. package.path
package.path = base_path .. 'enemies/one_actions/?.lua;' .. package.path
package.path = base_path .. 'basic/?.lua;' .. package.path
package.path = base_path .. 'helpers/?.lua;' .. package.path

DEBUG = 0
DEBUG_MAX = 50
active_debug = false
-- active_debug_list = false
active_debug_objects = false
active_debug_walkable = false




require "ia_killer"
-- require "nothing"
-- require "ia_breaker"
-- require "ia_state"
-- require "ia_stalker"
-- require "ia_seeker"
-- require "ia_intro"
-- require "ia_simple"
-- require "ia_coward"
-- require "ia_intelligent_coward"
-- require "search_box"
-- require "avoid_bomb"
-- require "test_dangerous"
-- require "put_bomb"

-- -- require "ia_unit_test"
