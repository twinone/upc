-- Identifier for a variable
type Ident = String
-- Only used in main
-- Current type used for the values of the program
-- Can be any Number
type Value = Int


data NExpr a
  = Var     Ident
  | Const   a -- TODO parameterize
  | Plus    (NExpr a) (NExpr a)
  | Minus   (NExpr a) (NExpr a)
  | Times   (NExpr a) (NExpr a)
  deriving (Read, Show)

data BExpr a
  = AND   (BExpr a) (BExpr a)
  | OR    (BExpr a) (BExpr a)
  | NOT   (BExpr a)
  | Gt    (NExpr a) (NExpr a)
  | Eq    (NExpr a) (NExpr a)
  deriving (Read, Show)

data Seq a
  = Seq [Command a]
  deriving (Read, Show)

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
  show (Cond c x y) = "IF " ++ show c ++ " THEN\n" ++ nest x ++ elseVal y ++ "END\n"
    where
      elseVal (Seq []) = ""
      elseVal _ = "ELSE\n" ++ nest y
  show (Loop c x)   = "WHILE " ++ show c ++ "\nDO\n" ++ nest x ++ "END\n"

-- nest handles the recursive calls to show
nest :: (Show a) => Seq a -> String
nest (Seq x) = unlines (map (("  "++).show) x)

main = do
  input <- getContents
  putStrLn (show (read input :: (Seq Value)))
