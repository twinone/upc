typeError = "type error "
referenceError x = "ReferenceError: " ++ x ++ " is not defined"
emptyStackError = "empty stack"



-- Identifier for a variable
type Ident = String
-- Only used in main
-- Current type used for the values of the program
-- Can be any Num
type Value = Int

--------------------------------------------------------------------------------
--------------------------         PARSING          ----------------------------
--------------------------------------------------------------------------------

data NExpr a
  = Var     Ident
  | Const   a
  | Plus    (NExpr a) (NExpr a)
  | Minus   (NExpr a) (NExpr a)
  | Times   (NExpr a) (NExpr a)
  deriving (Read)

instance (Show a) => Show (NExpr a) where
  show (Var x) = x
  show (Const x) = show x
  show (Plus x y) = show x ++ " + " ++ show y
  show (Minus x y) = show x ++ " - " ++ show y
  show (Times x y) = show x ++ " * " ++ show y


data BExpr a
  = AND   (BExpr a) (BExpr a)
  | OR    (BExpr a) (BExpr a)
  | NOT   (BExpr a)
  | Gt    (NExpr a) (NExpr a)
  | Eq    (NExpr a) (NExpr a)
  deriving (Read)

instance (Show a) => Show (BExpr a) where
  show (AND x y) = show x ++ " AND " ++ show y
  show (OR x y) = show x ++ " OR " ++ show y
  show (NOT x) = "NOT " ++ show x
  show (Gt x y) = show x ++ " > " ++ show y
  show (Eq x y) = show x ++ " = " ++ show y





data Command a
  = Assign  Ident (NExpr a)  -- Assign x y assigns a constant value y to x
  | Print   (NExpr a)        -- Print x prints the value of x to stdout
  | Input   Ident            -- Input x reads a value from stdin into x
  | Empty   Ident            -- Return an empty list
  | Pop     Ident Ident      -- Pop x y pops the top of x to y
  | Push    Ident (NExpr a)  -- Push x y pushes y onto x
  | Size    Ident Ident      -- Size x y assigns the len(x) to y
  | Cond    (BExpr a) (Command a) (Command a) -- Cond x y z executes if x then y else z
  | Loop    (BExpr a) (Command a) -- Loop x y executes y while x
  | Seq     [Command a]
  deriving (Read)

instance (Show a) => Show (Command a) where
  show (Assign i x) = i ++ " := " ++ show x ++ "\n"
  show (Print i)    = "PRINT " ++ show i ++ "\n"
  show (Input i)    = "INPUT " ++ i ++ "\n"
  show (Empty i)    = "EMPTY " ++ i ++ "\n"
  show (Pop i j)    = "POP " ++ i ++ " " ++ j ++ "\n"
  show (Push i j)   = "PUSH " ++ i ++ " " ++ show j ++ "\n"
  show (Size i j)   = "SIZE " ++ i ++ " " ++ j ++ "\n"
  show (Loop c x)   = "WHILE " ++ show c ++ "\nDO\n" ++ show' x ++ "END\n"
  show (Cond c x y) = "IF " ++ show c ++ " THEN\n" ++ iv ++ ev y ++ "END\n"
    where
      iv = show' x
      ev (Seq []) = ""
      ev _ = "ELSE\n" ++ show' y
  show x = unlines $ (map (drop 2)) $ lines $ (show' x)

-- show a sequence
show' :: (Show a) => Command a -> String
show' (Seq x) = unlines (map (rstrip. indent . show) x)
  where
    indent = (unlines . (map ("  "++)) . lines)
    rstrip = reverse . dropWhile (=='\n') . reverse

--------------------------------------------------------------------------------
--------------------------        EVALUATION        ----------------------------
--------------------------------------------------------------------------------

-- utility functions
isLeft :: Either a b -> Bool
isLeft (Left a) = True
isLeft _ = False

isNothing :: Maybe a -> Bool
isNothing Nothing = True
isNothing _ = False

just :: Maybe a -> a
just (Just a) = a

left :: Either a b -> a
left (Left a) = a

right :: Either a b -> b
right (Right b) = b

-- SymTable holds all variables
-- TODO: Make this a RB tree maybe for efficiency
-- We're not allowed to use Haskell's data structures
data Sym a = Sym a | Stack [a] deriving (Show)
data Entry a = Entry Ident (Sym a) deriving (Show)
data SymTable a = SymTable [Entry a] deriving (Show)

isStack :: Sym a -> Bool
isStack (Sym a) = False
isStack _ = True

sym :: Sym a -> a
sym (Sym a) = a

stack :: Sym a -> [a]
stack (Stack a) = a

-- destructuring functions
key :: Entry a -> Ident
key (Entry k _) = k

val :: Entry a -> Sym a
val (Entry _ v) = v

elems :: SymTable a -> [Entry a]
elems (SymTable t) = t

-- manipulation of a symtable
set :: SymTable a -> Ident -> Sym a -> SymTable a
set t k v = SymTable $ (Entry k v):(elems $ del t k)

-- sets adds all the values from the first table to the second
-- overwriting any existing values
setAll :: SymTable a -> SymTable a -> SymTable a
setAll (SymTable []) b = b
setAll (SymTable (x:xs)) b = setAll (SymTable xs) (set b (key x) (val x))


del :: SymTable a -> Ident -> SymTable a
del (SymTable t) k = SymTable r
  where r = filter ((/=k).key) t

get :: SymTable a -> Ident -> Maybe (Sym a)
get (SymTable []) _ = Nothing
get t k
  | k == key hd = Just (val hd)
  | otherwise   = get (SymTable tl) k
  where
   hd = (head . elems) t
   tl = (tail . elems) t

getSym :: SymTable a -> Ident -> Maybe a
getSym (SymTable []) _ = Nothing
getSym t k
  | k == key hd = Just ((sym . val) hd)
  | otherwise   = getSym (SymTable tl) k
  where
   hd = (head . elems) t
   tl = (tail . elems) t

getSymOrErrF :: (Ident -> Maybe a) -> Ident -> Either String a
getSymOrErrF f x
  | isNothing v  = Left (referenceError x)
  | otherwise    = Right (just v)
  where v = f x


getSymOrErr :: SymTable a -> Ident -> Either String a
getSymOrErr t x = getSymOrErrF (getSym t) x


class Evaluable e where
  eval      :: (Num a, Ord a) => (Ident -> Maybe a) -> (e a) -> (Either String a)
  typeCheck :: (Ident -> String) -> (e a) -> Bool


instance Evaluable NExpr where
  eval _ (Const a) = Right a
  eval f (Var x) = getSymOrErrF f x
  eval f (Plus x y)   = evalOp' f (+) x y
  eval f (Minus x y)  = evalOp' f (-) x y
  eval f (Times x y)  = evalOp' f (*) x y

  typeCheck _ (Const _)   = True
  typeCheck f (Var x)     = f x == "sym"
  typeCheck f (Plus x y)  = typeCheck f x && typeCheck f y
  typeCheck f (Minus x y) = typeCheck f x && typeCheck f y
  typeCheck f (Times x y) = typeCheck f x && typeCheck f y


evalOp' f op x y
  | isLeft xv = xv
  | isLeft yv = yv
  | otherwise = Right ((right xv) `op` (right yv))
  where
    xv = eval f x
    yv = eval f y


btoi :: Num a => Bool -> a
btoi True  = 1
btoi False = 0

itob :: (Eq a, Num a) => a -> Bool
itob 0 = False
itob 1 = True

bop :: (Eq a, Num a) => (Bool -> Bool -> Bool) -> a -> a -> a
bop f x y = btoi ((itob x) `f` (itob y))

instance Evaluable BExpr where
  eval f (AND x y)  = evalOp' f (bop (&&)) x y
  eval f (OR x y)   = evalOp' f (bop (||)) x y
  -- I know, I know... ugly hack to avoid rewriting the whole function...
  eval f (NOT x)    = evalOp' f (bop (\x y -> not x)) x x
  eval f (Gt x y)   = evalOp' f (\a b -> btoi (a > b)) x y
  eval f (Eq x y)   = evalOp' f (\a b -> btoi (a == b)) x y

  -- bools always type, because at this stage we passed parsing already
  typeCheck f (AND x y) = typeCheck f x && typeCheck f y
  typeCheck f (OR x y)  = typeCheck f x && typeCheck f y
  typeCheck f (NOT x )  = typeCheck f x
  typeCheck f (Gt x y)  = typeCheck f x && typeCheck f y
  typeCheck f (Eq x y)  = typeCheck f x && typeCheck f y


err :: String -> (Either String [a], SymTable a, [a])
err x = (Left x, SymTable [], [])

interpretCommand :: (Num a, Ord a, Show a) =>
   SymTable a -> [a] -> Command a -> (Either String [a], SymTable a, [a])

-- Seq
interpretCommand t i (Seq []) = (Right [], t, i)
interpretCommand t i (Seq (c:cs))
  | isLeft co = err (left co)
  | isLeft ro = err (left ro)
  | otherwise = (Right ((right co) ++ (right ro)), rt, ri)
  where
    (co, ct, ci) = interpretCommand t i c
    (ro, rt, ri) = interpretCommand ct ci (Seq cs)

-- Assign
interpretCommand t i (Assign k v)
  | isLeft val = err (left val)
  | otherwise  = (Right [], set t k (Sym (right val)), i)
  where
    val = eval (getSym t) v

interpretCommand t i (Print v)
  | isLeft val = err (left val)
  | otherwise  = (Right [right val], t, i)
  where
    val = eval (getSym t) v

interpretCommand t i (Input k) = (Right [], set t k (Sym (head i)), tail i)

interpretCommand t i (Empty k) = (Right [], set t k (Stack []), i)

interpretCommand t i (Pop k v)
  | isNothing mb    = err (referenceError k)
  | not (isStack r) = err (typeError ++ ": "++ k ++ " is not a stack")
  | s == []         = err emptyStackError
  | otherwise       = (Right [], ot, i)
  where
    s = stack r
    r = just mb
    mb = get t k

    h = head s
    t1 = set t k (Stack (tail s)) -- table with new stack
    ot = set t1 v (Sym h) -- table with the output variable set


interpretCommand t i (Push k v)
  | isNothing mb    = err (referenceError k)
  | not (isStack r) = err (typeError ++ ": "++ k ++ " is not a stack")
  | isLeft val      = err (left val)
  | otherwise       = (Right [], ot, i)
  where
    s = stack r
    r = just mb
    mb = get t k
    ot = set t k (Stack (num:s))

    num = right val
    val = eval (getSym t) v


--    | Pop     Ident Ident      -- Pop x y pops the top of x to y
--    | Push    Ident (NExpr a)  -- Push x y pushes y onto x
--    | Size    Ident Ident      -- Size x y assigns the len(x) to y
--    | Cond    (BExpr a) (Command a) (Command a) -- Cond x y z executes if x then y else z
--    | Loop    (BExpr a) (Command a) -- Loop x y executes y while x
--    | Seq     [Command a]
--    deriving (Read)

--   SymTable a -> [a] -> Command a -> (Either String [a], SymTable a, [a])
--   SymTable      Inputs Commands  ->   Err|Outputs, SymTable, Input

interpretCommand t i (Size   k v) = (Left "OK7", t, i)
interpretCommand t i (Cond   k v l) = (Left "OK8", t, i)
interpretCommand t i (Loop   k v) = (Left "OK9", t, i)


-- interpretProgram :: (Num a, Ord a) =>
--   [a] -> Command a -> (Either String [a])



--------------------------------------------------------------------------------
--------------------------           MAIN           ----------------------------
--------------------------------------------------------------------------------

main = do
  input <- getContents
  putStrLn (show (read input :: (Command Value)))
  putStrLn (st (interpretCommand (SymTable []) [1..30] (read input :: (Command Value))))
  where
    st (o, a, x) = show o ++"\n" ++show a ++"\n"++ show x
