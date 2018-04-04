myFoldl :: (a -> b -> a) -> a -> [b] -> a
myFoldl f s [] = s
myFoldl f s (x:xs) = myFoldl f (f s x) xs

myFoldr :: (a -> b -> b) -> b -> [a] -> b
myFoldr f s [] = s
myFoldr f s (x:xs) = f x $ myFoldr f s xs

myIterate :: (a -> a) -> a -> [a]
myIterate f a = a:(myIterate f $ f a)

myUntil :: (a -> Bool) -> (a -> a) -> a -> a
myUntil p f a = if p a then a else myUntil p f $ f a

myMap :: (a -> b) -> [a] -> [b]
myMap f as = [ f x | x <- as ]

myFilter :: (a -> Bool) -> [a] -> [a]
myFilter p as = [ x | x <- as, p x ]

myAll :: Eq a => (a -> Bool) -> [a] -> Bool
myAll f as = as == (takeWhile f as)

myAny :: Eq a => (a -> Bool) -> [a] -> Bool
myAny f as = dropWhile (not . f) as /= []


myZip :: [a] -> [b] -> [(a, b)]
myZip (a:as) (b:bs) = (a,b):(myZip as bs)
myZip _ _ = []

myZipWith :: (a -> b -> c) -> [a] -> [b] -> [c]
myZipWith f a b = map (uncurry f) $ zip a b
