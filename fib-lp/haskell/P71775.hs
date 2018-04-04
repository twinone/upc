-- Define a function countIf :: (Int -> Bool) -> [Int] -> Int that, given a predicate on integers and a list of integers, returns the number of elements in the list that satify the predicate.
-- Define a function pam :: [Int] -> [Int -> Int] -> [[Int]] that, given a list of integers and a list of functions from integers to integers, returns the list consisting if applying each of the functions in the second list to the elements in the first list.
-- Define a function pam2 :: [Int] -> [Int -> Int] -> [[Int]] that, given a list of integers and a list of functions from integers to integers, returns the list of lists where each list if the result of applying, one after the other, the function in the second list to each element in the first list.
-- Define a function filterFoldl :: (Int -> Bool) -> (Int -> Int -> Int) -> Int -> [Int] -> Int that returns a fold of all the elements that satisfy the given predicate.
-- Define a function insert :: (Int -> Int -> Bool) -> [Int] -> Int -> [Int] that, given a relation between integers, a list and un element, return the list with the inserted element according to the relation.
--Use function insert, in order to define function insertionSort :: (Int -> Int -> Bool) -> [Int] -> [Int] that orders a list according to the given relation.

countIf :: (a -> Bool) -> [a] -> Int
countIf f l = length $ filter f l

pam :: [Int] -> [Int -> Int] -> [[Int]]
pam xs fs =  [ map f xs | f <- fs ]

pam2 :: [Int] -> [Int -> Int] -> [[Int]]
pam2 xs fs = [ map head (pam [x] fs) | x <- xs ]

filterFoldl :: (Int -> Bool) -> (Int -> Int -> Int) -> Int -> [Int] -> Int
filterFoldl p f s l = foldl f s (filter p l)

insert :: (Int -> Int -> Bool) -> [Int] -> Int -> [Int]
insert r l x = h++(x:t)
  where
    h = takeWhile (not . r x) l
    t = dropWhile (not . r x) l

insertionSort :: (Int -> Int -> Bool) -> [Int] -> [Int]
insertionSort r l = foldl (\x y -> insert r x y) [] ls
