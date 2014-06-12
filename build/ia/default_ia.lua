i = 0;

function initialization()
end

function play()
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
