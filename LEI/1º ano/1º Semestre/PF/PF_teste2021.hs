--1
barra :: Eq a => [a] -> [a] -> [a]
--barra [1,2,3,4,5,1,2] [2,3,4,1,2] == [5,1] 
barra [] _ = []
barra l [] = l
barra (x:xs)  (y:ys) | x == y = barra xs ys
                     | otherwise = x : barra xs (y:ys)

--2
type MSet a = [(a,Int)]
--a
removeMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
removeMSet _ [] = []
removeMSet l ((a,i):t) | l == a && i == 1 = t
                       | l == a = ((a,(i-1)):t)
                       | otherwise = (a,i) : removeMSet l t

--b
-- calcula :: MSet a -> ([a],Int)
-- --calcula [] = ([],0)
-- calcula ((a,i):t) = map (letras)

--3
-- partes :: String -> Char -> [String]
-- partes [] _ = []
-- partes (x:xs) c | x == c = partes xs c
--                 | otherwise = ([x] ++ partes xs c)

--4
data BTree a = Empty | Node a (BTree a) (BTree a) deriving Show

--a
a1 = Node 5 (Node 3 Empty Empty)
            (Node 7 Empty (Node 9 Empty Empty ))
removeBT :: Ord a => a -> BTree a -> BTree a
removeBT _ Empty = Empty
removeBT x (Node r e d) | x == r = Empty
                        | otherwise = (Node r (removeBT x e) (removeBT x d))

--b

--5
sortOn5 :: Ord b => (a->b) -> [a] -> [a]
sortOn5 _ [] = []
sortOn5 f l = map (\f (x:xs) -> if f x <= head f xs then x else x : f xs ) l