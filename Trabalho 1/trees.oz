functor
export 
   depth:DepthFirst
   addXY:AddXY

define
   proc {DepthFirst Tree Level LeftLim ?RootX ?RightLim}
      case Tree
      of tree(x:X y:Y left:leaf right:leaf ...) then
         X = RootX = RightLim = LeftLim
         Y = 30 * Level
      
      [] tree(x:X y:Y left:L right:leaf ...) then
         X = RootX
         Y = 30 * Level
         {DepthFirst L Level+1 LeftLim RootX RightLim}
      
      [] tree(x:X y:Y left:leaf right:R ...) then
         X = RootX
         Y = 30 * Level
         {DepthFirst R Level+1 LeftLim RootX RightLim}
      
      [] tree(x:X y:Y left:L right:R ...) then
         LRootX LRightLim RRootX RLeftLim
      in
         Y = 30 * Level
         {DepthFirst L Level+1 LeftLim LRootX LRightLim}
         
         RLeftLim = LRightLim + 30
         {DepthFirst R Level+1 RLeftLim RRootX RightLim}
         X = RootX = (LRootX + RRootX) div 2

      end
   end

   fun {AddXY Tree}
      case Tree
      of tree(left:L right:R ...) then
         {Adjoin Tree tree(x:_ y:_ left:{AddXY L} right:{AddXY R})}
      [] leaf then
         leaf
      end
   end
end