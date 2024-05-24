-- lETZZZ GOOOOO
import Data.Char
-- 1
myEnumFromTo :: Int -> Int -> [Int]
myEnumFromTo n m | n > m = []
                 | otherwise = n : myEnumFromTo (n+1) m
              -- | otherwise = [n..m]
-- 2
myEnumFromThenTo :: Int -> Int -> Int -> [Int]
myEnumFromThenTo a b c | a > c && b - a > 0 || a < c && b - a < 0 = []
                       | otherwise = a : myEnumFromThenTo b (b+(b-a)) c
-- 3
plusplus :: [a] -> [a] -> [a]
plusplus l [] = l
plusplus [] l = l
plusplus (h:t) a = h : plusplus t a
-- 4
posicao :: [a] -> Int -> a
posicao (h:t) 0 = h
posicao (h:t) n = posicao t (n-1) 
-- 5
myreverse :: [a] -> [a]
myreverse [] = []
myreverse [a] = [a]
myreverse x = last x : myreverse (init x)
-- 6
mytake :: Int -> [a] -> [a]
mytake _ [] = []
mytake x (h:t) | x == 0 = []
               | otherwise = h : mytake (x-1) t 
-- 7
dropa :: Int -> [a] -> [a]
dropa _ [] = []
dropa x (h:t) | x == 0 = (h:t)
               | otherwise = dropa (x-1) t 
-- 8
zipa :: [a] -> [b] -> [(a,b)]
zipa _ [] = []
zipa [] _ = []
zipa (x:xs) (y:ys) = (x,y) : zipa xs ys
-- 9
replica :: Int -> a -> [a]
replica 0 _ = []
replica n x = x : replica (n-1) x
-- 10 
myinterspace :: a -> [a] -> [a]
myinterspace _ [] = []
myinterspace _ [a] = [a]
myinterspace n (h:t) = h : n : myinterspace n t

-- 11 -- fazer de novo
agrupa :: Eq a => [a] -> [[a]]
agrupa [] = [[]]
agrupa [a] = [[a]]
agrupa (x:y:ys) 
  | x == y = (x : groupys) : restGroup
  | otherwise = [x] : (groupys : restGroup)
   where 
    (groupys : restGroup) = agrupa (y:ys)
-- 12
concatena :: [[a]] -> [a]
concatena [[]] = []
concatena [[a]] = [a]
concatena (x:xs) = x ++ concatena xs
-- 13
prefixos :: [a] -> [[a]]
prefixos [] = [[]]
prefixos l = prefixos (init l) ++ [l]
-- 14
caudas :: [a] -> [[a]]
caudas [] = [[]]
caudas (h:t) = (h:t) : caudas (t)
-- 15
cabecas :: [[a]] -> [a]
cabecas [] = []
cabecas ([]:ys) = cabecas ys
cabecas ((x:xs):ys) = x : cabecas ys
-- 16
total :: [[a]] -> Int
total [] = 0
total ([]:xs) = 0 + total xs
total ((x:xs):ys) = 1 + total (xs:ys)
-- 17
fun :: [(a,b,c)] -> [(a,c)]
fun [] = []
fun ((a,b,c):t) = (a,c) : fun t
-- 18 
cola :: [(String,b,c)] -> String 
cola [] = []
cola ((a,b,c):t) = a ++ cola t
-- 19
idade :: Int -> Int -> [(String,Int)] -> [String]
idade _ _ [] = []
idade a i ((p,n):t) | a - n >= i =  p : idade a i t
                      | otherwise = idade a i t
-- 20
powerEnumFrom :: Int ->  Int -> [Int]
powerEnumFrom _ 0 = []
powerEnumFrom n m = powerEnumFrom n (m-1) ++ [n^(m-1)] 
-- 21 -- REFAZER
isPrime ::  Int -> Bool
isPrime n = nDivisores n 2 == 0 

nDivisores :: Int -> Int -> Int
nDivisores n m | m >= n = 0
               | mod n m == 0 = 1
               | otherwise = nDivisores n (m+1)
-- 22
myisPrefixOf:: Eq a => [a] -> [a] -> Bool
myisPrefixOf [] _ = True
myisPrefixOf (x:xs) (y:ys) = x == y && myisPrefixOf xs ys
-- 23
myisSuffixOf:: Eq a => [a] -> [a] -> Bool 
myisSuffixOf [] _ = True
myisSuffixOf _ [] = False
myisSuffixOf x y = last x == last y && myisSuffixOf (init x) (init y)
-- 24
myisSubsequenceOf :: Eq a => [a] -> [a] -> Bool
myisSubsequenceOf [] _ = True
myisSubsequenceOf _ [] = False
myisSubsequenceOf (x:xs) (y:ys) | x == y = myisSubsequenceOf xs ys
                                | otherwise = myisSubsequenceOf (x:xs) ys
-- 25 ??
elemIndices :: Eq a => a -> [a] -> [Int]
elemIndices _ [] = []
elemIndices n (x:xs) | n == x = (p-1) : elemIndices n xs 
                     | otherwise = elemIndices n xs
                     where p = length (x:xs)
-- 26
-- refazer
nub :: Eq a => [a] -> [a]
nub [] = []
nub (x:xs) | elem x xs = nub xs
           | otherwise = x : nub xs 
-- 27
--mydelete :: Eq a => a -> [a] -> [a] -- tem a definição diferente da ficha
mydelete _ [] = []
mydelete x (h:t) | x == 1 = t
                 | otherwise = h : mydelete (x-1) t
-- 28 
barras :: Eq a => [a] -> [a] -> [a]
barras l [] = l 
barras [] _ = [] 
barras (x:xs) (y:ys) | x == y = barras xs ys
                     | otherwise = x : barras xs (y:ys)
-- 29
uniao :: Eq a => [a] -> [a] -> [a]
unia l [] = l
uniao [] l = l
uniao (x:xs) (y:ys) | x == y = x : uniao xs ys
                    | otherwise =  x : (uniao (xs) (y:ys)) 

-- 30
-- funcina MAS o exemplo [1,1,2,3,4] [1,3,1,5] falha
interseta :: Eq a => [a] -> [a] -> [a]
interseta l [] = l
interseta [] l = []
interseta (x:xs) (y:ys) | x == y = x : interseta xs (y:ys)
                        | otherwise = interseta xs ys
-- 31 
insere :: Ord a => a -> [a] -> [a]
insere e [] = [e]
insere e (a:b:t) | e >= a && e <= b = a : e : b : t
                 | otherwise = a : insere e (b:t) 
-- 32
myunwords :: [String] -> String
myunwords [] = []
myunwords (x:xs) = x ++ " " ++ myunwords xs
-- 33
myunlines :: [String] -> String
myunlines [] = []
myunlines (x:xs) = x ++ "\n" ++ myunlines xs
-- -- 34
-- pMaior :: Ord a => [a] -> Int
-- pMaior [] = 0
-- pMaior (x:xs:xss) | x >= xs = 1 + pMaior xs 
-- 35
mylookUp :: Eq a => a -> [(a,b)] -> Maybe b 
mylookUp _ [] = Nothing 
mylookUp c ((a,b):t) | c == a = Just b 
                   | otherwise = mylookUp c t 
-- 36
preCrescente :: Ord a => [a] -> [a]
preCrescente [] = []
preCrescente (x:xs:xss) | x <= xs = x : preCrescente (xs:xss)
                        | otherwise = [x]
-- 37
iSort :: Ord a => [a] -> [a]
iSort [] = []
iSort [x] = [x]
iSort (h:t) = insert h (iSort t) 

insert ::  Ord a => a -> [a] -> [a] -- insere os elementos numa lista ordenada
insert a (h:t) | a <= h = a:h:t
               | otherwise = h : insert a t

-- 38 
menor :: String -> String -> Bool
menor l1 l2 = length l1 < length l2 
-- 39
elemMSet :: Eq a => a -> [(a,Int)] -> Bool
elemMSet _ [] = False
elemMSet c ((c1,a):t) | c == c1 = True
                      | otherwise = elemMSet c t 
-- 40
converteMSet :: [(a,Int)] -> [a]
converteMSet [] = [] 
converteMSet ((a,b):t) | b /= 0 = a : converteMSet ((a,(b-1)):t)
                       | otherwise = converteMSet t 
-- 41
insereMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
insereMSet c [] = [(c,1)]
insereMSet c ((a,b):t) | c == a = ((a,b+1):t)
                       | otherwise = (a,b) : insereMSet c t
-- 42 
removeMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
removeMSet _ [] = []
removeMSet c ((a,b):t) | c == a && b > 1 = ((a,b-1):t)
                       | c == a && b == 1 = t
                       | otherwise = (a,b) : removeMSet c t
-- 43
-- constroiMSet ::Eq a => a -> [(a,Int)]
-- constroiMSet [] = []
-- constroiMSet [c] = [(c,1)]
-- constroiMSet (x:xs:xss) | x /= xs = (x,+1 ) 

-- 44 ??
mypartitionEithers :: [Either a b] -> ([a], [b])
mypartitionEithers [] = ([],[])
mypartitionEithers (h:t) = case h of 
                         Left a ->  ((a:x),y)
                         Right b -> (x,(b:y))
   where (x,y) = mypartitionEithers t

-- 45 
-- catMaybes :: [Maybe a] -> [a]


-- 46
data Movimento = Norte | Sul | Este | Oeste 
               deriving Show
-- inicio x , fim y
caminho :: (Int,Int) -> (Int,Int) -> [Movimento]
caminho (ix,iy) (fx,fy) | iy < fy = Norte : caminho (ix,iy+1) (fx,fy)
                        | iy > fy = Sul : caminho (ix,iy-1) (fx,fy)
                        | ix < fx = Este : caminho (ix+1,iy) (fx,fy)
                        | ix > fx = Oeste : caminho (ix-1,iy) (fx,fy)
                        | otherwise = [] 
-- 47
-- auxPosicao :: (Int,Int) -> [Movimento] -> (Int,Int)
-- auxPosicao a [] = a 
-- auxPosicao (x,y) (a:as) = case a of
--                       Norte -> auxPosicao (x+1,y) as
--                       Sul -> auxPosicao (x-1,y) as
--                       Este -> auxPosicao (x,y-1) as
--                       Oeste -> auxPosicao (x,y-1) as

-- 48
type Ponto = (Float,Float)
data Rectangulo = Rect Ponto Ponto
-- esta a dar erro em 1,1 2,2
contaQuadrados :: [Rectangulo] -> Int 
contaQuadrados [] = 0
contaQuadrados ((Rect (x1,y1) (x2,y2)):t) | sqrt((x2-x1)^2) == sqrt((y2-y1)^2) = 1 + contaQuadrados t
                                          | otherwise = contaQuadrados t
