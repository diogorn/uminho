module PF_ficha7 where

--1
data ExpInt = Const Int | Simetrico ExpInt | Mais ExpInt ExpInt | Menos ExpInt ExpInt | Mult ExpInt ExpInt

--a
calcula :: ExpInt -> Int
calcula n = case n of
    Const x -> x
    Simetrico x -> - calcula x
    Mais x y -> calcula x + calcula y
    Menos x y -> calcula x + calcula y
    Mult x y -> calcula x * calcula y

--b
infixa :: ExpInt -> String
--infixa (Mais (Const 3) (Menos (Const 2) (Const 5))) -> "(3 + (2 - 5))"
infixa n = case n of
    Const x -> show x
    Simetrico x -> "(" ++ "-" ++ infixa x ++ ")"
    Mais x y -> "(" ++ infixa x ++ "+" ++ infixa y ++ ")"
    Menos x y -> "(" ++ infixa x ++ "+" ++ infixa y ++ ")"
    Mult x y -> "(" ++ infixa x ++ "*" ++ infixa y ++ ")"

--c
posfixa :: ExpInt -> String
posfixa n = case n of
    Const x -> show x
    Simetrico x -> posfixa x ++ " -"
    Mais x y -> posfixa x ++ posfixa y ++ " +"
    Menos x y -> posfixa x ++ posfixa y ++ " -"
    Mult x y -> posfixa x ++ posfixa y ++ " *"


--2
data RTree a = R a [RTree a] deriving Show

rt=R 5 [R 4 [R 3 [], R 2 [], R 7 []], R 10 [] , R 1 [R 8 [], R 12 []]]
{-
      5
    ⁄ |  \
   4  10  1
 / | \   /  \
3  2  7 8    12
-}
--a
soma :: Num a => RTree a -> a 
soma (R x l) = x + sum (map soma l)

--b
altura :: RTree a -> Int
altura (R x []) = 1 
altura (R x l) = 1 + maximum (map altura l)

--c
prune :: Int -> RTree a -> RTree a
prune _ (R x []) = R x []
prune 0 (R x l) = R x []
prune n (R x l) = R x (map (prune (n-1)) l)

--d
mirror :: RTree a -> RTree a 
mirror (R x []) = R x []
mirror (R x l) = R x (map mirror (reverse l))


--3
--data BTree a = Empty | Node a (BTree a) (BTree a)
data LTree a = Tip a | Fork (LTree a) (LTree a)
--a
ltSum :: Num a => LTree a -> a
ltSum (Tip a) = a
ltSum (Fork a b) =  ltSum a + ltSum b

--b
listaLT :: LTree a -> [a]
listaLT (Tip a) = [a]
listaLT (Fork a b) = listaLT a ++ listaLT b

--c
ltHeight :: LTree a -> Int
ltHeight (Tip a) = 1
ltHeight (Fork a b) = 1 + max (ltHeight a) (ltHeight b)
