-- Identifier for a variable
type Ident = String
-- Only used in main
-- Current type used for the values of the program
-- Can be any Number
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


data Seq a
  = Seq [Command a]
  deriving (Read)




data Command a
  = Assign  Ident (NExpr a)  -- Assign x y assigns a constant value y to x
  | Print   Ident            -- Print x prints the value of x to stdout
  | Input   Ident            -- Input x reads a value from stdin into x
  | Empty   Ident            -- Return an empty list
  | Pop     Ident Ident      -- Pop x y pops the top of x to y
  | Push    Ident (NExpr a)  -- Push x y pushes y onto x
  | Size    Ident Ident      -- Size x y assigns the len(x) to y
  | Cond    (BExpr a) (Seq a) (Seq a) -- Cond x y z executes if x then y else z
  | Loop    (BExpr a) (Seq a) -- Loop x y executes y while x
  deriving (Read)

instance (Show a) => Show (Command a) where
  show (Assign i x) = i ++ " := " ++ show x ++ "\n"
  show (Print i)    = "PRINT " ++ i ++ "\n"
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

instance (Show a) => Show (Seq a) where
  show x = unlines $ (map (drop 2)) $ lines $ (show' x)

show' :: (Show a) => Seq a -> String
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

sym :: Sym a -> Maybe a
sym (Sym a) = Just a
sym _ = Nothing

-- destructuring functions
key :: Entry a -> Ident
key (Entry k _) = k

val :: Entry a -> Sym a
val (Entry _ v) = v

elems :: SymTable a -> [Entry a]
elems (SymTable t) = t

-- manipulation of a symtable
setSym :: SymTable a -> Ident -> Sym a -> SymTable a
setSym t k v = SymTable $ (Entry k v):(elems $ delSym t k)

delSym :: SymTable a -> Ident -> SymTable a
delSym (SymTable t) k = SymTable r
  where r = filter ((/=k).key) t

getSym :: SymTable a -> Ident -> Maybe (Sym a)
getSym (SymTable []) _ = Nothing
getSym t k = if k == key hd then Just (val hd) else getSym (SymTable tl) k
 where
   hd = (head . elems) t
   tl = (tail . elems) t


class Evaluable e where
  eval      :: (Num a, Ord a) => (Ident -> Maybe a) -> (e a) -> (Either String a)
  typeCheck :: (Ident -> String) -> (e a) -> Bool


instance Evaluable NExpr where
  eval _ (Const a) = Right a
  eval f (Var x)
    | isNothing v  = Left ("ReferenceError: " ++ x ++ " is not defined")
    | otherwise    = Right (just v)
    where v = f x
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

--------------------------------------------------------------------------------
--------------------------        EVALUATION        ----------------------------
--------------------------------------------------------------------------------




--------------------------------------------------------------------------------
--------------------------           MAIN           ----------------------------
--------------------------------------------------------------------------------

main = do
  input <- getContents
  putStrLn (show (read input :: (Seq Value)))
