myLength :: [Int] -> Int
myLength [] = 0
myLength (x:xs) = 1 + myLength xs

myMaximum :: [Int] -> Int
myMaximum [x] = x
myMaximum (x:xs) = max x (myMaximum xs)


average :: [Int] -> Float
average x = (fromIntegral (sum' x)) / (fromIntegral (myLength x))
  where
    sum' :: [Int] -> Int
    sum' [] = 0
    sum' (x:xs) = x + (sum xs)

buildPalindrome :: [Int] -> [Int]
buildPalindrome [] = []
buildPalindrome x = (reverse' x) ++ x
  where
    reverse' :: [Int] -> [Int]
    reverse' [] = []
    reverse' (x:xs) = (reverse' xs) ++ [x]

flatten :: [[Int]] -> [Int]
flatten [] = []
flatten (x:xs) = x ++ flatten xs


remove :: [Int] -> [Int] -> [Int]
remove [] r = []
remove (x:xs) r = if x `elem` r then remove xs r else [x]++(remove xs r)


oddsNevens :: [Int] -> ([Int],[Int])
oddsNevens x = (filter odd x, filter even x)


-- From P77907
isPrime :: Int -> Bool
isPrime 0 = False
isPrime 1 = False
isPrime n = not (hasDivisors (n-1))
    where
	hasDivisors :: Int -> Bool
	hasDivisors 1 = False
	hasDivisors x = mod n x == 0 || hasDivisors (x-1)

primeDivisors :: Int -> [Int]
primeDivisors a = filter (\x -> isPrime x && a `mod` x == 0) [1..a]
