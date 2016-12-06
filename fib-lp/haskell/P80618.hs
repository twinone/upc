-- Implementeu cues genèriques utilitzant la definició de dades i les operacions següents:
--  data Queue a = Queue [a] [a]
--      deriving (Show)
--
--  create :: Queue a
--  push :: a -> Queue a -> Queue a
--  pop :: Queue a -> Queue a
--  top :: Queue a -> a
--  empty :: Queue a -> Bool
-- Definiu la igualtat de cues de manera que dues cues siguin iguals si i només si tenen els mateixos elements en el mateix ordre de sortida. Per a fer- ho, indiqueu que les cues són una instàcia de la classe Eq on (==) és l’operació d’igualtat que heu de definir:
--  instance Eq a => Eq (Queue a)
--      where
--          ...
-- Fixeu-vos que cal que el tipus dels elements de la cua també siguin de la classe Eq.
--
data Queue a = Queue [a] [a] deriving (Show)

create :: Queue a
create = Queue [] []

push :: a -> Queue a -> Queue a
push a (Queue x y) = Queue x (a:y)

pop :: Queue a -> Queue a
pop (Queue [] y) = Queue (tail (reverse y)) []
pop (Queue x y) = Queue (tail x) y

top :: Queue a -> a
top (Queue [] x) = last x
top (Queue x _) = head x


empty :: Queue a -> Bool
empty (Queue [] []) = True
empty (Queue _ _) = False


flatq (Queue a b) = a ++ reverse b

instance Eq a => Eq (Queue a) where
  x == y = (flatq x) == (flatq y)
