module PF_ficha5 where

import Data.List

--1
--a
anyA :: (a->Bool)->[a]->Bool
anyA _ [] = False
anyA f (h:t) | f h = True
             | otherwise = anyA f t

--b
zipWithB :: (a->b->c)->[a]->[b]->[c]
zipWithB _ [] _ = []
zipWithB _ _ [] = []
zipWithB f (x:xs) (y:ys) = (f x y) : zipWithB f xs ys

--c
takeWhileC :: (a->Bool) -> [a] -> [a]
takeWhileC _ [] = []
takeWhileC f (h:t) | f h = h : takeWhileC f t
                   | otherwise = []

--d
dropWhileD :: (a->Bool)->[a]->[a]
dropWhileD _ [] = []
dropWhileD f (h:t) | not (f h) = (h:t)
                   | otherwise = dropWhileD f t 

--e
spanE :: (a->Bool)->[a]->([a],[a])
spanE f l = (takeWhileC f l, dropWhileD f l)

--f 
deleteByF :: (a->a->Bool) -> a -> [a] -> [a]
deleteByF _ _ [] = []
deleteByF f x (h:t) | f x h = t
                    | otherwise = h : deleteByF f x t

--g
sortOnG :: Ord b => (a->b)->[a]->[a]
sortOnG _ [] = []
sortOnG f (h:t) = insereSort f h t

insereSort :: Ord b => (a->b)->a->[a]->[a]
insereSort _ x [] = [x]
insereSort f x (h:t) | f x >= f h = h : insereSort f x t
                     | otherwise = x : insereSort f h t 

--2
-- filter -> aplica um filtro a um lista
-- foldl -> aplica uma função a um elemento x e a uma lista de elementos, sendo o resultado um elemento (ex: foldl / 64 [4,2,4] -> 2)
-- map -> aplica uma função a todos os elementos da lista, individualmente  

-- ficha 2
type Polinomio = [Monomio]
type Monomio = (Float,Int) -- (c,e)
--a
selgrau :: Int -> Polinomio -> Polinomio
selgrau _ [] = []
selgrau x p = filter (\n -> snd n == x) p

--b
conta ::  Int -> Polinomio -> Int
conta _ [] = 0
conta n p = length (selgrau n p)
--c
grau :: Polinomio -> Int
grau [] = 0
grau l = foldl(\acc x -> if acc > snd x then acc else snd x ) 0 l 
--d

--e
calcula :: Float -> Polinomio -> Float
calcula _ [] = 0
calcula x l = foldl(\acc (c,e) -> acc + c * (x^e)) 0 l

--f
simp :: Polinomio -> Polinomio
simp [] = []
simp l = filter (\n -> snd n /= 0) l

--g
mult :: Monomio -> Polinomio -> Polinomio
mult (c,e) p = map (\(cp,ep) -> ((c*cp),(e+ep)) ) p

--h 
ordena :: Polinomio -> Polinomio
ordena l = reverse (sortOnG snd l)

--i


--3
type Mat a = [[a]]

--a
dimOk :: Mat a -> Bool
dimOk m = all(\l -> length l == length m) m

--b
dimMat :: Mat a -> (Int,Int)
dimMat (h:t) = (length t+1, length h) 

--c
addMat :: Num a => Mat a ->  Mat a ->  Mat a 
addMat [] [] = []
addMat (h1:m1) (h2:m2) = addLinhas h1 h2 : addMat m1 m2
    where addLinhas [] _ = []
          addLinhas (h1:t1s) (h2:t2s) = (h1 + h2) : addLinhas t1s t2s
