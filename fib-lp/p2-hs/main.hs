data Ident = String
data Command a  = Assign Ident a
                |  Print Ident


main = do
  putStrLn "Hi"
