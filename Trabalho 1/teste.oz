
functor
import
	Browser
	trees at 'trees.ozf'

	define
		T = tree(key:a val:111 left:leaf right:leaf)
		A =  {trees.addXY T}
		{Browser.browse A}
	end
end