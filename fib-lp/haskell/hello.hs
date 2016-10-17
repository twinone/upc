factorial :: Integer -> Integer
factorial 0 = 1
factorial n = n * factorial (n-1)

len :: [a] -> Int
len [] = 0
len (_:t) = 1 + len t
