functor
export 
   notG:NotG
   andG:AndG
   orG:OrG
   nandG:NandG
   norG:NorG
   xorG:XorG
   fullAdder:FullAdder

define
   fun {GateMaker F}
      fun {$ Xs Ys}
         fun {GateLoop Xs Ys}
            case Xs#Ys of (X|Xr)#(Y|Yr) then
               {F X Y}|{GateLoop Xr Yr}
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

   proc {FullAdder X Y Z ?C ?S}
      K L M
   in
      K = {AndG X Y}
      L = {AndG Y Z}
      M = {AndG X Z}
      C = {OrG K {OrG L M}}
      S = {XorG Z {XorG X Y}}
   end

end