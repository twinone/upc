greet :: String -> String
greet a = "Hola mac" ++ [c] ++ "!"
  where c =
    if a /= [] && (last a == 'a' || last a == 'A')
    then 'a'
    else 'o'

main = do
  name <- getLine
  putStrLn $ greet name
