functor
	import
	Browser
	Gates at 'Gates.ozf'

define

	local
	   fun {Result Zs}
	      case Zs
	      of nil then true 
	      [] Z|Zr then
		 if Z == 1 then false else {Result Zr} end
	      else true end
	   end
	in
	   fun {Comp X Y}
	      {Result {Gates.xorG X Y}}
	   end
	end

	{Browser.browse {Comp 0|0|0|0 1|1|1|0 }}

	{Browser.browse {Comp 1|1|1|0 1|1|1|0 }}

	{Browser.browse {Comp 1|1|0|1 1|1|0|1 }}

	{Browser.browse {Comp 0|1|0|1|1|nil 0|1|0|1|1|nil }}
	

end