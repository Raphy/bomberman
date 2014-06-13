
require 'actions'
require 'state'
require 'state_machine'

-- * BEGIN_STATE *

BeginState = State:new("begin_state")

function BeginState:action()
	Helper:debug_print("action : ".."begin_state")
	--return corps
end

BeginState.pre_conditions = {
	--conditions
}

StateList = {
	["begin_state"] = BeginState,
}

active_debug = true

DEBUG = 0
DEBUG_MAX = 100

function initialization()
	Helper:debug_print("\n\nUNIT_TEST ) initialization")
	--Helper:initialization_base(10, 2)
	Coord:init()	
	MapManager:init(100,100)
-- MapManager:activate_vision()
	math.randomseed(os.time())
	-- Coord:init()
	-- MapManager:init(100,100, vision_size)
	Actions:init(10)

	-- StateMachine:init(1, 100
	-- 						10, 100)
	-- MapManager:update()
	-- Helper:debug_print("\n\nUNIT_TEST ) play")
	-- StateMachine:play()

	do
		print("\n\n***** TEST COORD *****\n")
	
		local toto = Coord:new(0,10)
		local titi = Coord:new(1,1)
		local tata = Coord:new(2,2)
		
		print("toto x y ",toto.x,toto.y)
		print("titi x y ",titi.x,titi.y)
		print("tata x y ",tata.x,tata.y)
		print("toto < titi ",(toto < titi))
		print("toto <= titi ",(toto <= titi))
		print("toto > titi ",(toto > titi))
		print("toto >= titi ",(toto >= titi))
		print("titi < tata ",(titi < tata))
		print("titi <= tata ",(titi <= tata))
		print("titi > tata ",(titi > tata))
		print("titi >= tata ",(titi >= tata))
		print("\n\n***** END TEST COORD *****\n")
	end

	-- * LIST *
	do
		print("\n\n***** TEST LIST *****\n")
		
		local test_list = List:new("test_list")
		List:push_back(test_list, "banane")
		List:push_back(test_list, "pomme")
		List:push_back(test_list, "ananas")
		List:push(test_list, "kiwi")
		
		print("iter...")
		for elem in List:iter(test_list) do
			print(elem)
		end
		print("... fin iter")
		
		local head = List:front_and_pop(test_list)
		print("front_and_pop : ", head)
		local head = List:front_and_pop(test_list)
		print("front_and_pop : ", head)
		local tail = List:back_and_pop(test_list)
		print("back_and_pop : ", tail)
		
		print("size : ", List:size(test_list))
		print("empty : ", List:empty(test_list))
		print("is_elem_in_list : ", "banane", List:is_elem_in_list(test_list, "banane"))
		print("is_elem_in_list : ", "pomme", List:is_elem_in_list(test_list, "pomme"))
		print("\n\n***** END TEST LIST *****\n")
	end

	-- * MAP_MANAGER *
	do
		print("\n\n***** TEST MAP_MANAGER *****\n")
		
		print("active : ", MapManager._vision.active)
		MapManager:set_vision(Coord:new(5,5), 2)
		print("iter_ij...")
		for i,j in MapManager:iter_ij() do
			print("i ", i," j ", j)
		end
		print("... fin iter_ij")
		print("iter...")
		for case in MapManager:iter() do
			print("x ", case.x," y ", case.y)
		end
		print("... fin iter")
		print("\n\n***** END TEST MAP_MANAGER *****\n")
	end

	-- * HELPER *
	do
		print("\n\n***** TEST HELPER *****\n")
		
		local coo = Helper:get_my_coord()
		print("my_coord : ", Coord:unpack(coo))
		local idx = MapManager:coord_to_idx(Coord:unpack(coo))
		print("my_idx : ", idx)
		local case = MapManager:get_case(idx)
		print("my_case : ",
				unpack(case))
		print("are_objects_in_case(coo.x,coo.y) : ",
				Helper:are_objects_in_case(coo.x,coo.y))
		print("are_objects_in_case(coo.x,coo.y,\"enemy\") : ",
				Helper:are_objects_in_case(coo.x,coo.y,"enemy"))
		-- print("are_objects_in_case_except(coo.x,coo.y) : ",
		-- 		Helper:are_objects_in_case_except(coo.x,coo.y))
		print("are_objects_in_case_except(coo.x,coo.y,\"enemy\") : ",
				Helper:are_objects_in_case_except(coo.x,coo.y,"enemy"))
		print("are_objects(\"enemy\") : ",
				Helper:are_objects("enemy"))
		print("are_objects_around(\"enemy\",coo.x,coo.y) : ",
				Helper:are_objects_around("enemy",coo.x,coo.y))
		print("are_objects_around(\"enemy\",coo.x,coo.y,3) : ",
				Helper:are_objects_around("enemy",coo.x,coo.y,3))
		print("is_place_safe() : ",
				Helper:is_place_safe())
		print("\n\n***** END TEST HELPER *****\n")
	
	-- -- * PATH *
		print("\n\n***** TEST PATH *****\n")
		print("Path:calc_path(\"dijkstra\", idx, 100) : ")
		Path:calc_path("dijkstra", idx, 100)
		print("Path:calc_path(\"astar\", idx, 100) : ")
		local path = Path:calc_path("astar", idx, 100)
		Helper:debug_print(path)
	end
	
		print("\n\n*****  *****\n\n")

end



function play()
	return nil
end
