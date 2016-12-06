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

data Command a
  = Assign  Ident a       -- TODO: Nexpr Assign x y assigns a constant value y to x
  | Print   Ident         -- Print x prints the value of x to stdout
  | Input   Ident         -- Input x reads a value from stdin into x
  | Empty   Ident         -- Return an empty list
  | Pop     Ident Ident     -- Pop x y pops the top of x to y
  | Push    Ident Ident   -- TODO: Nexpr Push x y pushes y onto x
  | Size    Ident Ident   -- Size x y assigns the len(x) to y
  | Cond    (BExpr a) (Seq a) (Seq a) -- Cond x y z executes if x then y else z
  | Loop    (BExpr a) (Seq a) -- Loop x y executes y while x
  deriving (Read, Show)

data Seq a
  = Seq [Command a]
  deriving (Read, Show)

main = do
  input <- getContents
  putStrLn (show (read input :: (Seq Value)))
