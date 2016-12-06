myMap :: (a -> b) -> [a] -> [b]
myMap f x = [ f e | e <- x ]

myFilter :: (a -> Bool) -> [a] -> [a]
myFilter a b = [ x | x <- b, a x ]

myZipWith :: (a -> b -> c) -> [a] -> [b] -> [c]
myZipWith f a b = [ f x y | (x,y) <- zip a b ]

thingify :: [Int] -> [Int] -> [(Int, Int)]
thingify a b = [ (x,y) | x <- a, y <- b , x `mod` y == 0 ]

factors :: Int -> [Int]
factors n = [ y | (x,y) <- thingify [n] [1..n] ]
