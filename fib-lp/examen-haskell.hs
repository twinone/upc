-- Problema 1
mergelist :: (Ord a) => [[a]] -> [a]
mergelist = foldl merge []
  where
    merge (a:as) (b:bs)
      | a == b    = [a] ++ merge as bs -- no duplicates
      | a < b     = [a] ++ merge as (b:bs)
      | otherwise = [b] ++ merge (a:as) bs
    merge a b = a ++ b -- one is empty

-- Problema 2
mults :: [Integer] -> [Integer]
mults x = mergelist $ [[1]] ++ (map (\x -> iterate (+x) x) x)

-- Problema 3.1
data Procs a
  = End
  | Skip (Procs a)
  | Unary (a -> a) (Procs a)
  | Binary (a -> a -> a) (Procs a)

-- Problema 3.2
exec :: [a] -> (Procs a) -> [a]
exec [] _ = []
exec i End = i
exec (i:is) (Skip n) = [i] ++ exec is n
exec (i:is) (Unary f n) = exec ((f i):is) n
exec (i:[]) (Binary f n) = exec [i,i] (Binary f n)
exec (i:j:is) (Binary f n) = exec ((f i j):is) n

-- Problema 4.1
class Container c where
  emptyC :: c a -> Bool
  lengthC :: c a -> Int
  firstC :: c a -> a -- assumes nonempty
  popC :: c a -> c a -- assumes nonempty

-- Problema 4.2
instance Container [] where
  emptyC = (==0) . lengthC
  lengthC = length
  firstC = (!! 0)
  popC = tail

-- Problem 4.3
data Tree a
  = Empty
  | Node a [Tree a]

-- Problem 4.4
instance Container Tree where
  emptyC Empty = True
  emptyC _ = False
  lengthC Empty = 1
  lengthC (Node _ b) = 1 + (sum $ map lengthC b)
  firstC (Node a _) = a
  popC (Node a []) = Empty
  popC (Node a (Empty:as)) = popC (Node a as)
  popC (Node a (Node b bs:as)) = Node b (bs++as)

-- Problema 4.5
iterator :: Container c => c a -> [a]
iterator c
  | emptyC c  = []
  | otherwise = (firstC c):(iterator $ popC c)
