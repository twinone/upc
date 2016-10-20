eql :: [Int] -> [Int] -> Bool
eql x y = length x == length y &&
  filter (\(x,y) -> x /= y) (zip x y) == []

prod :: [Int] -> Int
prod x = foldl (\x y -> x*y) 1 x

prodOfEvens :: [Int] -> Int
prodOfEvens x = prod (filter even x)


powersOf2 :: [Int]
powersOf2 = iterate (*2) 1

scalarProduct :: [Float] -> [Float] -> Float
scalarProduct x y = foldl (\x y -> x+y) 0 (map (\(x,y) -> x*y) (zip x y))
