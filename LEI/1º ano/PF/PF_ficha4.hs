
module PF_ficha4 where

import Data.Char


--1
digitAlpha :: String -> (String,String)
digitAlpha [] = ([],[])
digitAlpha (h:t) | isDigit h = (h:letras,numeros)
                 | isAlpha h = (letras,h:numeros)
                 | otherwise = ([],[])
 where (letras,numeros) = digitAlpha t

--2
nzp :: [Int] -> [(Int,Int,Int)]
nzp [] = [(0,0,0)]
nzp (h:t) | h < 0 = [(1+n,z,p)]
          | h == 0 = [(n,1+z,p)]
          | h > 0 = [(n,z,1+p)]
 where [(n,z,p)] = nzp t 

--3

--4
fromDigits :: [Int] -> Int
fromDigits [] = 0
fromDigits (h:t) = h*10^(length t) + fromDigits t

fromDigits2 :: [Int] -> Int 
fromDigits2 [] = 0
fromDigits2 l = fDAcc ((length l)-1) l

fDAcc :: Int -> [Int] -> Int
fDAcc acc [] = 0
fDAcc acc (h:t) = (10^acc)*h + fDAcc (acc-1) t 

--5
--maxSumInit :: (Num a,Ord a) => [a] -> a 
--maxSumInit l = maximum [sum m | m <- init l]

--6
fib :: Int -> Int
fib 0 = 0
fib 1 = 1
fib n = fib (n-1) + fib (n-2)




