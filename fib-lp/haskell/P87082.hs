process :: String -> String
process x =
  name ++ ": " ++ (imcStr imc)
  where
    w = words x
    name = w !! 0
    m = read (w !! 1) :: Float
    h = read (w !! 2) :: Float
    imc = m / h / h

    imcStr x
      | x <  18 = "magror"
      | x <= 25 = "corpulencia normal"
      | x <= 30 = "sobrepes"
      | x <= 40 = "obesitat"
      | otherwise = "obesitat morbida"

main = do
  interact (unlines . map process . init . lines)
--main = do
--  s <- getContents
--  let res = map process (lines s)
--  putStrLn (unlines res)
