-- Define a function insert :: [Int] -> Int -> [Int] that, given a sorted list and an element, correctly inserts the new element in the list.

insert :: [Int] -> Int -> [Int]
insert [] e = [e]
insert (x:xs) e = if e < x then e:x:xs else x:(insert xs e)

-- Define a function isort :: [Int] -> [Int] that implements insertion sort using the previous function.
isort :: [Int] -> [Int]
isort [] = []
isort (x:xs) = insert (isort xs) x

-- Define a function remove :: [Int] -> Int -> [Int] that, given a list and an element x, erases the first occurrence of x from the list. You can assume that the element is always in the list.
remove :: [Int] -> Int -> [Int]
remove [] _ = []
remove (x:xs) e = if x == e then xs else x:(remove xs e)

-- Define a function ssort :: [Int] -> [Int] that implements selection sort using the previous function.
ssort :: [Int] -> [Int]
ssort [] = []
ssort x = m:(ssort (remove x m))
  where
    m = minimum x

-- Define a function merge :: [Int] -> [Int] -> [Int] that, given two sorted lists, merges them to get a list with all the elements in sorted order.
merge :: [Int] -> [Int] -> [Int]
merge (x:xs) (y:ys) = if x < y then x:(merge xs (y:ys)) else y:(merge ys (x:xs))
-- if at least one is empty
merge a b = concat [a,b]

-- Define a function msort :: [Int] -> [Int] that implements merge sort using the previous function.
msort :: [Int] -> [Int]
msort [] = []
msort [a] = [a]
msort a = merge (msort x) (msort y)
  where
    (x,y) = splitAt ((length a) `div` 2) a


-- Define a function qsort :: [Int] -> [Int] that implements quick sort.
qsort :: [Int] -> [Int]
qsort [] = []
qsort (x:xs) = (qsort $ filter (<=x) xs) ++ [x] ++ (qsort $ filter (>x) xs)

-- Generalize the previous function into genQsort :: Ord a => [a] -> [a] that sorts elements of any type.
genQsort :: Ord a => [a] -> [a]
genQsort [] = []
genQsort (x:xs) = (genQsort $ filter (<=x) xs) ++ [x] ++ (genQsort $ filter (>x) xs)
