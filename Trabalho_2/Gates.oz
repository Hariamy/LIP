functor
export 
   notG:NotG
   andG:AndG
   orG:OrG
   nandG:NandG
   norG:NorG
   xorG:XorG

define
   fun {GateMaker F}
      fun {$ Xs Ys}
         fun {GateLoop Xs Ys}
            case Xs#Ys 
            of (X|Xr)#(Y|Yr) then
               {F X Y}|{GateLoop Xr Yr}
            else nil
            end
         end
      in
         thread {GateLoop Xs Ys} end
      end
   end

   fun {NotMaker F}
      fun {$ Xs}
         fun {NotLoop Xs}
            case Xs of X|Xr then 
               {F X}|{NotLoop Xr} 
            end
         end
      in
         thread {NotLoop Xs} end
      end
   end

   AndG = {GateMaker fun {$ Xs Ys} Xs * Ys end}
   OrG = {GateMaker fun {$ Xs Ys} Xs + Ys - Xs * Ys end}
   NandG = {GateMaker fun {$ Xs Ys} 1 - Xs * Ys end}
   NorG = {GateMaker fun {$ Xs Ys} 1 - Xs + Ys - Xs * Ys end}
   XorG = {GateMaker fun {$ Xs Ys} Xs + Ys - 2 * Xs * Ys end}
   NotG = {NotMaker fun {$ Xs} 1 - Xs end}

end