flatten :: [[Int]] -> [Int]
flatten l = foldl (\x y -> x ++ y) [] l

myLength :: String -> Int
myLength s = foldl (\x _ -> x+1) 0 s

myReverse :: [Int] -> [Int]
myReverse x = map (\i -> x !! (l-i-1)) [0..(l-1)]
  where l = length x

countIn :: [[Int]] -> Int -> [Int]
countIn l x = map (\y -> count x y ) l
  where
    count :: Int -> [Int] -> Int
    count n = length . filter (==n)

firstWord :: String -> String
firstWord x = takeWhile (/=' ') (dropWhile (==' ') x)
