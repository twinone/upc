ones :: [Integer]
ones = 1:ones

nats :: [Integer]
nats = iterate (+1) 0

ints :: [Integer]
ints = 0:(ints' 0)
  where
    ints' x
      | x > 0     = -x:(ints' (-x))
      | otherwise = -x+1:(ints' (-x+1))

triangulars :: [Integer]
triangulars = t' 0 1
  where
    t' x y = x:(t' (x+y) (y+1))

factorials :: [Integer]
factorials = 1:(f' 1 2)
  where
    f' x y = x:(f' (x*y) (y+1))

fibs :: [Integer]
fibs = f' 0 1
  where
    f' x y = x:(f' y (x+y))

primes :: [Integer]
primes = filter isPrime $ tail nats
  where
    isPrime :: Integer -> Bool
    isPrime 0 = False
    isPrime 1 = False
    isPrime n = not (hasDivisors (n-1) n)

    hasDivisors :: Integer -> Integer -> Bool
    hasDivisors 1 _ = False
    hasDivisors x n = mod n x == 0 || hasDivisors (x-1) n


hammings :: [Integer]
hammings = h' 1
  where
    h' 1 =
    h' x =
