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





--------------------------------------------------------------------------------
--------------------------           MAIN           ----------------------------
--------------------------------------------------------------------------------

main = do
  input <- getContents
  putStrLn (show (read input :: (Seq Value)))
