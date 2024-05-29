--1
intersect :: Eq a => [a] -> [a] -> [a]
intersect [] _ = []
intersect l [] = l
intersect (x:xs) ys| elem x ys = x : intersect xs ys
                   | otherwise = intersect xs ys
--2
tails :: [a] -> [[a]]
tails [] = [[]]
tails (h:t) = (h:t) : tails t

--3
type ConjInt = [Intervalo]
type Intervalo = (Int,Int)

--a
elems :: ConjInt -> [Int]
elems [] = []
elems ((i,f):t) = [i..f] ++ elems t 
--b
--geraConj :: [Int] -> ConjInt
--geraConj [] = []
--geraConj (x0:x:xs) | x0 == (x-1) = [geraConjA 1 x0 (x:xs)] 
--                   | otherwise = geraConj (x:xs)
--
--geraConjA :: Int -> Int -> [Int] -> ConjInt
--geraConjA acc n (x0:x:xs) | 1 == (x-x0) = geraConjA (acc+1) n (x:xs)
--                          | otherwise = [(n,(x0))] 

data Contacto = Casa Integer | Trab Integer | Tlm Integer | Email String deriving (Show)
type Nome = String
type Agenda = [(Nome,[Contacto])]

--a
acrescEmail :: Nome -> String -> Agenda -> Agenda
acrescEmail n m l = l ++ [(n,[Email m])]
--b
verEmails :: Nome -> Agenda -> Maybe [String]
verEmails _ [] = Nothing
verEmails nome ((n,c):t) | nome == nome = Just (map (\x -> case x of Email x -> x) c)
                         | otherwise = verEmails nome t
--c
consulta :: [Contacto] -> ([Integer],[String])
consulta [] = ([],[])
consulta (c:cts) = case c of
                   Email c -> (phones,c:mails)
                   Casa c -> (c:phones,mails)
                   Tlm c -> (c:phones,mails)
                   Trab c -> (c:phones,mails)
  where (phones,mails) = consulta cts

--d
--4
data RTree a = R a [RTree a] deriving (Show, Eq)
--a
paths :: RTree a -> [[a]]
--paths Empty = []
paths (R a []) = []
paths (R a rs) = [a] ++ paths rs