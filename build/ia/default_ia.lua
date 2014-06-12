i = 0;

function initialization()
end

function play()
   x, y = me:getPosition()
   print("[IA] position (".. x ..", ".. y ..")")
   if i > 11 then
      i = 0
   end
   if i >= 0 and i <= 5 then
      me:moveUp()
   elseif i > 5 and i <= 11 then
      me:moveDown()
   end
   i = i + 1;
end
