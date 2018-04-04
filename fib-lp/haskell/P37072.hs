data Tree a = Node a (Tree a) (Tree a)
  | Empty
  deriving (Show)

-- Feu una funció size :: Tree a -> Int que, donat un arbre, retorni la seva talla, és a dir, el nombre de nodes que conté.
size :: Tree a -> Int
size Empty = 0
size (Node x y z) = 1 + (size y) + (size z)

-- Feu una funció height :: Tree a -> Int que, donat un arbre, retorni la seva alçada, assumint que els arbres buits tenen alçada zero.
height :: Tree a -> Int
height Empty = 0
height (Node _ x y) = 1 + max (height x) (height y)

-- Feu una funció equal :: Eq a => Tree a -> Tree a -> Bool que, donat dos arbres, indiqui si són el mateix.
equal :: Eq a => Tree a -> Tree a -> Bool
equal Empty Empty = True
equal (Node a b c) (Node d e f) = a == d && equal b e && equal c f
equal _ _ = False

-- Feu una funció isomorphic :: Eq a => Tree a -> Tree a -> Bool que, donat un arbres, indiqui si són el isomorfs, és a dir, si es pot obtenir l’un de l’altre tot girant algun dels seus fills.
isomorphic :: Eq a => Tree a -> Tree a -> Bool
isomorphic Empty Empty = True
isomorphic (Node a b c) (Node d e f) = a == d && (isomorphic b e && isomorphic c f
  || isomorphic b f && isomorphic c e)
isomorphic _ _ = False

-- Feu una funció preOrder :: Tree a -> [a] que, donat un arbre, retorni el seu recorregut en pre-ordre.
preOrder :: Tree a -> [a]
preOrder Empty = []
preOrder (Node a b c) = [a]++(preOrder b)++(preOrder c)
-- Feu una funció postOrder :: Tree a -> [a] que, donat un arbre, retorni el seu recorregut en post-ordre.
postOrder :: Tree a -> [a]
postOrder Empty = []
postOrder (Node a b c) = (postOrder b)++(postOrder c)++[a]
-- Feu una funció inOrder :: Tree a -> [a] que, donat un arbre, retorni el seu recorregut en in-ordre.
inOrder :: Tree a -> [a]
inOrder Empty = []
inOrder (Node a b c) = (inOrder b)++[a]++(inOrder c)

-- Feu una funció breadthFirst :: Tree a -> [a] que, donat un arbre, retorni el seu recorregut per nivells.
breadthFirst :: Tree a -> [a]
breadthFirst x = bfs [x]
  where
    bfs :: [Tree a] -> [a]
    bfs [] = []
    bfs l = [ x | (Node x _ _) <- l ] ++ bfs (children l)

    children :: [Tree a] -> [Tree a]
    children [] = []
    children (Empty:xs) = children xs
    children ((Node a b c):xs) = (f b) ++ (f c) ++ children xs
    -- Use f to remove empty nodes is more beautiful (and maintainable) than
    -- using a different case for each empty node
    f :: Tree a -> [Tree a]
    f Empty = []
    f x = [x]


bfs :: Tree -> [Int]

-- Feu una funció build :: Eq a => [a] -> [a] -> Tree a que, donat el recorregut en pre-ordre d’un arbre i el recorregut en in-ordre del mateix arbre, retorni l’arbre original. Assumiu que l’arbre no té elements repetits.
build [] [] = Empty
build pre ino = Node r a1 a2
  where r = head pre
        a1 = build b1 b2
        a2 = build c1 c2
        b1 = tail (take (1+length b2) pre)
        b2 = takeWhile (/=r) ino
        c1 = drop (1+length b1) pre
        c2 = tail (dropWhile (/= r) ino)


-- Feu una funció overlap :: (a -> a -> a) -> Tree a -> Tree a -> Tree a que, donats dos arbres, retorni la seva superposició utilitzant una funció. Superposar dos arbres amb una funció consisteix en posar els dos arbres l’un damunt de l’altre i combinar els nodes doble resultants amb la funció donada o deixant els nodes simples tal qual.
overlap :: (a -> a -> a) -> Tree a -> Tree a -> Tree a
overlap f Empty Empty = Empty
overlap f Empty (Node a b c) = Node a (overlap f b Empty) (overlap f c Empty)
overlap f (Node a b c) Empty = Node a (overlap f b Empty) (overlap f c Empty)
overlap f (Node a b c) (Node d e ff) = Node (f a d) (overlap f b e) (overlap f c ff)
