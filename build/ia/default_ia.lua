
base_path = './build/ia/'
package.path = base_path .. '?.lua;' .. package.path
package.path = base_path .. 'enemies/?.lua;' .. package.path
package.path = base_path .. 'basic/?.lua;' .. package.path
package.path = base_path .. 'helpers/?.lua;' .. package.path

active_debug = false
active_debug_list = false

-- require "ia_state"
require "ia_intro"
-- require "ia_simple"
-- require "ia_coward"
-- require "ia_stalker"
