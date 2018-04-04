absValue :: Int -> Int
absValue x
	| x < 0		= -x
	| otherwise	= x


power :: Int -> Int -> Int
power x y
	| y == 0	= 1
	| y == 1	= x
	
	| even y	= n * n
	| otherwise	= n * n * x
	where
		n = power x (y `div` 2)


slowFib :: Int -> Int
slowFib n
	| n == 0	= 0
	| n == 1	= 1
	| otherwise	= slowFib (n-1) + slowFib (n-2)




isPrime :: Int -> Bool
isPrime 0 = False
isPrime 1 = False
isPrime n = not (hasDivisors (n-1))
    where
	hasDivisors :: Int -> Bool
	hasDivisors 1 = False
	hasDivisors x = mod n x == 0 || hasDivisors (x-1)

quickFib :: Int -> Int
quickFib n = fst (quickFib' n)
    where
	quickFib' :: Int -> (Int, Int)
	quickFib' 0 = (0, 0)
	quickFib' 1 = (1, 0)
	quickFib' n = (fn1+fn2, fn1)
		where (fn1, fn2) = quickFib' (n-1)
