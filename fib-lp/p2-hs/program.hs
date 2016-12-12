-- Author: Twinone (Luuk W.)
-- Code commented with love for a correction with love

import System.Random


--------------------------------------------------------------------------------
---------------------------    CONSTANTS    ------------------------------------
--------------------------------------------------------------------------------

-- errors
typeError = "type error"
referenceError = "undefined variable"
emptyStackError = "empty stack"

-- types
typeNil = "nil"
typeStack = "stack"
typeSym = "sym"

file = "programhs.txt"

-- Identifier for a variable
type Ident = String

--------------------------------------------------------------------------------
-------------------------  DATA STRUCTURES & SHOW   ----------------------------
--------------------------------------------------------------------------------

------------------------------   NExpr    --------------------------------------

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

------------------------------   BExpr    --------------------------------------

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

------------------------------   Command    ------------------------------------

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
  | Seq     [Command a]       -- A sequence of commands
  deriving (Read)

instance (Show a) => Show (Command a) where
  show (Assign i x) = i ++ " := " ++ show x ++ "\n"
  show (Print i)    = "PRINT " ++ show i ++ "\n"
  show (Input i)    = "INPUT " ++ i ++ "\n"
  show (Empty i)    = "EMPTY " ++ i ++ "\n"
  show (Pop i j)    = "POP " ++ i ++ " " ++ j ++ "\n"
  show (Push i j)   = "PUSH " ++ i ++ " " ++ show j ++ "\n"
  show (Size i j)   = "SIZE " ++ i ++ " " ++ j ++ "\n"
  show (Loop c x)   = "WHILE " ++ show c ++ "\nDO\n" ++ indent x ++ "END\n"
  show (Cond c x y) = "IF " ++ show c ++ " THEN\n" ++ iv ++ ev y ++ "END\n"
    -- only show else part when needed
    where
      iv = indent x
      ev (Seq []) = ""
      ev _ = "ELSE\n" ++ indent y
  show x = unlines $ (map (drop 2)) $ lines $ (indent x)

-- show a sequence indented
indent :: (Show a) => Command a -> String
indent (Seq x) = unlines (map (rstrip. indent . show) x)
  where
    indent = (unlines . (map ("  "++)) . lines)
    rstrip = reverse . dropWhile (=='\n') . reverse


--------------------------------------------------------------------------------
--------------------------         SYMTABLE         ----------------------------
--------------------------------------------------------------------------------


-- We're explicitly not allowed to use any imports for this part.
-- Implementing an efficient data structure like a map is a solved problem
-- So I'm not going to waste time reinventing the wheel as this is not a
-- data structures subject :)
data SymTable a = SymTable [Entry a] deriving (Show)
data Entry a = Entry Ident (Sym a) deriving (Show)
data Sym a = Sym a | Stack [a] deriving (Show)

---------------------  BASIC OPERATIONS: set, del, get -------------------------
set :: SymTable a -> Ident -> Sym a -> SymTable a
set t k v = SymTable $ (Entry k v):(elems $ del t k)

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


--------------------------------------------------------------------------------
--------------   UTILITY FUNCTIONS -- WARNING: BORING   ------------------------
--------------------------------------------------------------------------------

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

showEither :: (Show a, Show b) => Either a b -> String
showEither (Left a)  = show a
showEither (Right a) = show a

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

-- type of a symbol
typeOf :: SymTable a -> Ident -> String
typeOf t k
  | isNothing mb  = typeNil
  | isStack val   = typeStack
  | otherwise     = typeSym
  where
    val = just mb
    mb = get t k

-- string to int
stoi :: String -> Int
stoi x = read x :: Int

-- bool to int
btoi :: Num a => Bool -> a
btoi True  = 1
btoi False = 0

-- int to bool
itob :: (Eq a, Num a) => a -> Bool
itob 0 = False
itob 1 = True

-- boolean operation with ints, converts 1->True, 0->False and returns the
-- result as an int
bop :: (Eq a, Num a) => (Bool -> Bool -> Bool) -> a -> a -> a
bop f x y = btoi ((itob x) `f` (itob y))


--------------------------------------------------------------------------------
--------------------------         EVALUABLE         ---------------------------
--------------------------------------------------------------------------------


class Evaluable e where
  eval      :: (Num a, Ord a) => (Ident -> Maybe a) -> (e a) -> (Either String a)
  typeCheck :: (Ident -> String) -> (e a) -> Bool

instance Evaluable NExpr where
  eval _ (Const a) = Right a
  eval f (Var x)
    | isNothing v  = Left referenceError
    | otherwise    = Right (just v)
    where v = f x
  eval f (Plus x y)   = evalOp' f (+) x y
  eval f (Minus x y)  = evalOp' f (-) x y
  eval f (Times x y)  = evalOp' f (*) x y

  typeCheck _ (Const _)   = True
  typeCheck f (Var x)     = f x == typeSym
  typeCheck f (Plus x y)  = typeCheck f x && typeCheck f y
  typeCheck f (Minus x y) = typeCheck f x && typeCheck f y
  typeCheck f (Times x y) = typeCheck f x && typeCheck f y


instance Evaluable BExpr where
  eval f (AND x y)  = evalOp' f (bop (&&)) x y
  eval f (OR x y)   = evalOp' f (bop (||)) x y
  -- I know, I know... ugly hack to avoid rewriting the whole function...
  eval f (NOT x)    = evalOp' f (bop (\x y -> not x)) x x
  eval f (Gt x y)   = evalOp' f (\a b -> btoi (a > b)) x y
  eval f (Eq x y)   = evalOp' f (\a b -> btoi (a == b)) x y

  typeCheck f (AND x y) = typeCheck f x && typeCheck f y
  typeCheck f (OR x y)  = typeCheck f x && typeCheck f y
  typeCheck f (NOT x )  = typeCheck f x
  typeCheck f (Gt x y)  = typeCheck f x && typeCheck f y
  typeCheck f (Eq x y)  = typeCheck f x && typeCheck f y


-- utility function
evalOp' f op x y
  | isLeft xv = xv
  | isLeft yv = yv
  | otherwise = Right ((right xv) `op` (right yv))
  where
    xv = eval f x
    yv = eval f y


-- the function for eval (Ident -> Maybe a) (we'll apply the SymTable to it)
getSym :: SymTable a -> Ident -> Maybe a
getSym (SymTable []) _ = Nothing
getSym t k
  | k == key hd = Just $ (sym . val) hd
  | otherwise   = getSym (SymTable $ (tail . elems) t) k
  where
   hd = (head . elems) t



--------------------------------------------------------------------------------
------------------------         INTERPRETER         ---------------------------
--------------------------------------------------------------------------------

interpretProgram :: (Num a, Ord a) => [a] -> Command a -> (Either String [a])
interpretProgram i c = res
  where
    (res, _, _) = interpretCommand (SymTable []) i c

--------------------------------------------------------------------------------

interpretCommand :: (Num a, Ord a) =>
   SymTable a -> [a] -> Command a -> (Either String [a], SymTable a, [a])

-- Seq
interpretCommand t i (Seq []) = (Right [], t, i)
interpretCommand t i (Seq (c:cs))
  | isLeft co = err $ left co
  | isLeft ro = err $ left ro
  | otherwise = (Right ((right co) ++ (right ro)), rt, ri)
  where
    (co, ct, ci) = interpretCommand t i c
    (ro, rt, ri) = interpretCommand ct ci (Seq cs)


-- Assign
interpretCommand t i (Assign k v)
  | isLeft val    = err $ left val
  | not (tc t v)  = err $ typeError
  | otherwise     = (Right (cc "Assign"), set t k (Sym (right val)), i)
  where
    val = eval (getSym t) v

interpretCommand t i (Print v)
  | isLeft val    = err $ left val
  | not (tc t v)  = err $ typeError
  | otherwise     = (Right ([1,right val]++(cc "Print")), t, i)
  where
    val = eval (getSym t) v

interpretCommand t i (Input k) = (Right ([0,(head i)]++(cc "Input")), set t k (Sym (head i)), tail i)

interpretCommand t i (Empty k) = (Right (cc "Empty"), set t k (Stack []), i)

interpretCommand t i (Pop k v)
  | isNothing mb    = err $ referenceError
  | not (isStack r) = err $ typeError
  | s == []         = err emptyStackError
  | otherwise       = (Right (cc "Pop"), ot, i)
  where
    s = stack r
    r = just mb
    mb = get t k

    h = head s
    t1 = set t k (Stack (tail s)) -- table with new stack
    ot = set t1 v (Sym h) -- table with the output variable set


interpretCommand t i (Push k v)
  | isNothing mb    = err $ referenceError
  | not (tc t v)    = err $ typeError
  | not (isStack r) = err $ typeError
  | isLeft val      = err $ left val
  | otherwise       = (Right (cc "Push"), ot, i)
  where
    s   = stack r
    r   = just mb
    mb  = get t k
    ot  = set t k (Stack (num:s))
    num = right val
    val = eval (getSym t) v


interpretCommand t i (Size k v)
  | isNothing mb    = err $ referenceError
  | not (isStack r) = err $ typeError
  | otherwise       = (Right (cc "Size"), ot, i)
  where
    s   = stack r
    r   = just mb
    mb  = get t k
    h   = fromIntegral $ length s
    ot  = set t v (Sym h)


interpretCommand t i (Cond c x y)
  | not (tc t c)  = err $ typeError
  | isLeft val    = err $ left val
  | bval          = interpretCommand t i x
  | otherwise     = interpretCommand t i y
  where
    bval    = itob intval
    intval  = right val
    val     = eval (getSym t) c


interpretCommand t i (Loop c x)
  | not (tc t c)  = err $ typeError
  | isLeft val    = err $ left val
  | bval          = interpretCommand t i (Seq [x,Loop c x])
  | otherwise     = (Right [], t, i)
  where
    bval    = itob intval
    intval  = right val
    val     = eval (getSym t) c

-- utility functions
err :: String -> (Either String [a], SymTable a, [a])
err x = (Left x, SymTable [], [])

tc :: (Evaluable e) => SymTable a -> (e a) -> Bool
tc t x = typeCheck (typeOf t) x

cc :: (Num a, Eq a) => String -> [a]
cc x = [nb x, 1]

nb :: (Num a, Eq a) => String -> a
nb x = case x of
  "Assign"  -> 2
  "Print"   -> 3
  "Input"   -> 4
  "Empty"   -> 5
  "Pop"     -> 6
  "Push"    -> 7
  "Size"    -> 8

txt :: (Eq a, Num a) => a -> String
txt x = case x of
  2 -> "Assign"
  3 -> "Print"
  4 -> "Input"
  5 -> "Empty"
  6 -> "Pop"
  7 -> "Push"
  8 -> "Size"

--------------------------------------------------------------------------------
--------------------------           MAIN           ----------------------------
--------------------------------------------------------------------------------

csep = "=======================================\n"
lsep = "---------------------------------------\n"

rund :: [Double] -> String -> (Either String [Double])
rund i c = interpretProgram i (read c :: (Command Double))

runi :: [Int] -> String -> (Either String [Int])
runi i c = interpretProgram i (read c :: (Command Int))

genInput :: (Read a, Random a) => String -> (a, a) -> Int -> [a]
genInput i rg s = ins ++ rands
  where
    --ins   = map read (words i)
    ins   = read (i)
    rands = randomRs rg (mkStdGen s)

run :: (Eq a, Num a) => String -> a -> String -> Int -> String
run prog mode is s
  | mode == 0 = out runi (-1000) 1000
  | mode == 1 = out rund (-1000) 1000
  where
    out f a b = show' $ f (genInput is (a, b) s) prog
    show' (Left x) = x
    show' (Right x) = i ++ o ++ n ++ a
      where
        i = "------- INPUTS ----------\n" ++ show xi ++ "\n"
        o = "------- OUTPUTS ---------\n" ++ show xo ++ "\n"
        n = "----- INSTRUCTIONS ------\n" ++      xn ++ "\n"
        a = "ALL:" ++ show x ++ "\n"
        (xi, xo) = inout x
        xn = instrs x

----------------------INOUT HACK -----------------------------------------------
pairs :: [a] -> [(a,a)]
pairs [] = []
pairs (x:y:xs) = (x,y):(pairs xs)


inout :: (Eq a, Num a) => [a] -> ([a], [a])
inout x = (ins, outs)
  where
    ins = map sec $ filter (\(x,y) -> x==0) (pairs x)
    outs = map sec $ filter (\(x,y) -> x==1) (pairs x)
    sec (a,b) = b

instrs :: (Enum a, Eq a, Num a, Show a, Ord a) => [a] -> String
instrs x = init $ tot++inst -- init to remove the trailing \n
  where
    tot = "Total:     " ++ show (cnt (>=2)) ++ "\n"
    inst = unlines $ map (\x -> n x) [2..8]
    n t = (txt t) ++ ":" ++ (replicate (10 - (length $ txt t)) ' ') ++ show (cnt (==t))
    cnt f = toint $ sum $ map sec $ filter (\(x,y) -> f x) $ pairs x
    sec (a,b) = b
    toint x = floor (read (show x) :: Double)


main = do
  prog <- readFile file

  putStrLn "Select Variable type:"
  putStrLn "  0: Int"
  putStrLn "  1: Double"
  t <- getLine

  putStrLn "Select execution mode:"
  putStrLn "  0: Manual"
  putStrLn "  1: Single Test"
  putStrLn "  2: Multiple Test"
  m <- getLine

  case read m of
    0 -> do
      input <- getContents
      putStrLn (run prog (stoi t) input 42)
    1 -> do
      putStrLn (run prog (stoi t) "" 42)
    2 -> do
      putStrLn ("Enter number of test cases:")
      n <- getLine
      putStr $ unlines $ map (\x -> p x) [1..(stoi n)]
        where p x = "============= Case #" ++ show x ++ " =============\n" ++ run prog (stoi t) "" (42+x)
