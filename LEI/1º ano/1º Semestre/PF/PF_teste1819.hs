import Data.Char
--1
--a
elemIndices :: Eq a => a -> [a] -> [Int]
elemIndices _ [] = []
elemIndices n l = elemIndicesAux 0 n l


elemIndicesAux :: Eq a => Int -> a -> [a] -> [Int]
elemIndicesAux _ _ [] = []
elemIndicesAux acc n (h:t) | n == h = acc : elemIndicesAux (acc+1) n t
                           | otherwise = elemIndicesAux (acc+1) n t
--b
isSubsequenceOf :: Eq a => [a] -> [a] -> Bool
isSubsequenceOf [] _ = True
isSubsequenceOf _ [] = False
isSubsequenceOf (x:xs) (y:ys) | x == y = isSubsequenceOf xs ys
                              | otherwise = isSubsequenceOf (x:xs) ys

--2
data BTree a = Empty | Node a (BTree a) (BTree a)
--a
lookupAP :: Ord a => a -> BTree (a,b) -> Maybe b     
lookupAP _ Empty = Nothing 
lookupAP n (Node (a,b) e d) | n == a = Just b
                            | n < a = lookupAP n e
                            | otherwise = lookupAP n d

--b
zipWithBT :: (a->b->c) -> BTree a -> BTree b -> BTree c
zipWithBT _ Empty _ = Empty
zipWithBT _ _ Empty = Empty
zipWithBT f (Node a ea da) (Node b eb db) = (Node (f a b) (zipWithBT f ea eb) (zipWithBT f da db))

--3
digitAlpha3 :: String -> (String,String)
-- isDigit, isAlpha ::  Char -> Bool
digitAlpha3 [] = ([],[])
digitAlpha3 (h:t) | isDigit h = (h:numeros,letras)
                 | otherwise = (numeros,h:letras)
                 where (numeros,letras) = digitAlpha3 t

--4
data Seq a = Nil | Cons a (Seq a) | App (Seq a) (Seq a)

--a

--5
type Mat a = [[a]]

--a

--b
