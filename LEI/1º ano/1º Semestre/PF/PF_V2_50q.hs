-- 1 
enumFromTo1 :: Int -> Int -> [Int]
enumFromTo1 x y | x <= y = x : enumFromTo1 (x+1) y
                | otherwise = []
-- 2
enumFromThenTo2 :: Int -> Int -> Int -> [Int]
enumFromThenTo2 x y z | x > y || y > z = []
                      | otherwise = y : enumFromThenTo2 y (y+limite) z
                      where limite = y-x
-- 3
plusplus3 :: [a] -> [a] -> [a]
plusplus3 l1 [] = l1
plusplus3 [] l2 = l2
plusplus3 (x:xs) l2 = x : plusplus3 xs l2
-- 4
pos4 :: [a] -> Int -> a 
pos4 (h:t) 0 = h
pos4 (h:t) p = pos4 t (p-1)
-- 5
reverse5 :: [a] -> [a] 
reverse5 [] = []
reverse5 (h:t) =  reverse5 t ++ [h]
-- 6
take6 :: Int -> [a] -> [a]
take6 1 (x:xs) = [x]
take6 t (x:xs) = x : take6 (t-1) xs
-- 7
drop7 :: Int -> [a] -> [a]
drop7 _ [] = []
drop7 t (x:xs) | t /= 0 = drop7 (t-1) xs 
              | otherwise = x : drop7 t xs
-- 8
zip8 :: [a] -> [b] -> [(a,b)]
zip8 [] _ = []
zip8 _ [] = []
zip8 (x:xs) (y:ys) = (x,y) : zip8 xs ys
-- 9
replicate9 :: Int -> a -> [a]
replicate9 x n | x == 0 = []
                | otherwise = n : replicate9 (x-1) n 
-- 10
intersperse10 :: a -> [a] -> [a]
intersperse10 _ [] = []
intersperse10 _ [x] = [x]
intersperse10 n (x:xs) = x : n : intersperse10 n xs 
--11
group :: Eq a => [a] -> [[a]]
group [] = []
group [x] = [[x]]
group (h:t)
    | elem h (head r) = (h : (head r)) : tail r
    | otherwise = [h] : r
    where r = group t
-- 12
concat12 :: [[a]] -> [a]
concat12 [[]] = []
concat12 ([]:xs) = concat12 xs
concat12 ((h:t):xs) = h : concat12 ((t):xs)
-- 13
inits13 :: [a] -> [[a]]
inits13 [] = [[]]
inits13 l = inits13 (init l) ++ [l]
-- 14
tails14 :: [a] -> [[a]]
tails14 [] = [[]]
tails14 l = l : tails14 l
-- 15
heads15 :: [[a]] -> [a]
heads15 [[]] = []
heads15 ([]:t) = heads15 t
heads15 ((h:t):xs) = h : heads15 xs
-- 16
total15 :: [[a]] -> Int
total15 [[]] = 0
total15 ([]:xs) = total15 xs
total15 ((x:xs):ys) = 1 + total15 ((xs):ys)
-- 17
fun17 :: [(a,b,c)] -> [(a,c)]
fun17 [] = []
fun17 ((a,b,c):t) = (a,c) : fun17 t 
-- 18
cola18 :: [(String,b,c)] -> String 
cola18 [] = []
cola18 ((a,b,c):t) = a ++ cola18 t
-- 19
idade19 :: Int -> Int -> [(String,Int)] -> [String]
idade19 _ _ [] = []
idade19 ano idd ((n,date):t) | ano - date >= idd = n : idade19 ano idd t
                             | otherwise = idade19 ano idd t 
-- 20
powerEnumFrom20 :: Int -> Int -> [Int]
powerEnumFrom20 n m | m == 0 = [1]
                    | otherwise = powerEnumFrom20 n (m-1) ++ [n^m]
-- 21
isPrime21 ::  Int -> Bool
isPrime21 n = nDivisores21 n 2 == 0 

nDivisores21 :: Int -> Int -> Int
nDivisores21 n m | m >= n = 0
                 | mod n m == 0 = 1
                 | otherwise = nDivisores21 n (m+1)
-- 22
isPrefixOf22 :: Eq a => [a] -> [a] -> Bool
isPrefixOf22 [] _ = True
isPrefixOf22 _ [] = False
isPrefixOf22 (x:xs) (y:ys) | x == y = isPrefixOf22 xs ys
                           | otherwise = isPrefixOf22 (x:xs) ys
-- 23
isSuffixOf23 :: Eq a => [a] -> [a] -> Bool
isSuffixOf23 [] [] = True
isSuffixOf23 _ [] = False
isSuffixOf23 [] _ = False
isSuffixOf23 (x:xs) (y:ys) | x == y = isSuffixOf23 xs ys
                           | otherwise = isSuffixOf23 (x:xs) ys

-- 24
isSubsquenceOf24 :: Eq a => [a] -> [a] -> Bool
isSubsquenceOf24 [] [] = True
isSubsquenceOf24 _ [] = False
isSubsquenceOf24 (x:xs) (y:ys) | x == y = isSubsquenceOf24 xs ys
                               | otherwise = isSubsquenceOf24 (x:xs) ys
-- 25
elemIndices25 :: Eq a => a -> [a] -> [Int]
elemIndices25 n [] = []
elemIndices25 n l = auxElemIndices25 n l 0

auxElemIndices25 :: Eq a => a -> [a] -> Int -> [Int]
auxElemIndices25 _ [] _ = []
auxElemIndices25 n (x:xs) p | n == x = p : auxElemIndices25 n xs (p+1)
                            | otherwise = auxElemIndices25 n xs (p+1)

-- 26
nub26 :: Eq a => [a] -> [a]
nub26 [] = []
nub26 (x:xs) | elem x xs = nub26 xs
             | otherwise = x : nub26 xs

-- 27
delete27 :: Eq a => a -> [a] -> [a]
delete27 n (x:xs) | n == x  = xs
                  | otherwise = x : delete27 n xs 

-- 28
barras28 :: Eq a => [a] -> [a] -> [a]
barras28 [] _ = []
barras28 l [] = l
barras28 (x:xs) (y:ys) | y == x = barras28 xs ys
                       | otherwise = x : barras28 xs (y:ys)
-- 29
union29 :: Eq a => [a] -> [a] -> [a]
union29 [] l = l 
union29 l [] = l 
union29 (x:xs) (y:ys) | x == y = x : union29 xs ys
                      | otherwise = x  : (union29 xs (y:ys))
-- 30 
intersect :: Eq a => [a] -> [a] -> [a]
intersect [] _ = []
intersect (h:t) l
    | h `elem` l = h : intersect t l
    | otherwise = intersect t l
-- 31
insert31 :: Ord a => a -> [a] -> [a]
insert31 n [] = [n]
insert31 n (h:t) | n >= h = h : insert31 n t
                 | otherwise = n : h : t

-- 32
unwords32 :: [String] -> String
unwords32 [] = ""
unwords32 (h:t) = h ++ " " ++ unwords32 t

-- 33
unlines33 :: [String] -> String
unlines33 [] = []
unlines33 (h:t) = h ++ "\n" ++ unlines33 t

-- 34
pMaior :: Ord a => [a] -> Int
pMaior [_] = 0
pMaior (h:t)
    | h >= (t !! x) = 0
    | otherwise = 1 + x
    where x = pMaior t

-- 35
lookup35 :: Eq a => a -> [(a,b)] -> Maybe b
lookup35 _ [] = Nothing
lookup35 c ((l,n):t) | c == l = Just n
                     | otherwise = lookup35 c t

-- 36
preCrescente36 :: Ord a => [a] -> [a]
preCrescente36 [] = []
preCrescente36 (x:xs:t) | x<=xs = x : preCrescente36 (xs:t)
                        | otherwise = [x]
-- 37
iSort37 :: Ord a => [a] -> [a]
iSort37 [] = []
iSort37 (h:t) = insert37 h (iSort37 t)

insert37 :: Ord a => a -> [a] -> [a]
insert37 x [] = [x]
insert37 i (h:t) |i <= h = i:h:t
                 | otherwise = h : insert37 i t

-- 38
menor38 :: String -> String -> Bool -- retorna true quando a 1 < 2
menor38 [] [] = True
menor38 [] l = True
menor38 l [] = False
menor38 (x:xs) (y:ys) | x < y = True
                      | x > y = False
                      | otherwise = menor38 xs ys
-- 39
elemMset39 :: Eq a => a -> [(a,Int)] -> Bool
elemMset39 _ [] = False
elemMset39 c ((a,i):t) | c == a = True
                       | otherwise = elemMset39 c t
-- 40
converteMSet40 :: [(a,Int)] -> [a]
converteMSet40 [] = []
converteMSet40 ((a,i):t) | i /= 0 = [a] ++ converteMSet40 ((a,i-1):t)
                         | otherwise = converteMSet40 t 
-- 41 
insereMSet41 :: Eq a => a -> [(a,Int)] -> [(a,Int)]
insereMSet41 c [] = [(c,1)]
insereMSet41 c ((a,i):t) | c == a = ((a,i+1):t)
                         | otherwise = (a,i) : insereMSet41 c t 
-- 42 
removeMSet42 :: Eq a => a -> [(a,Int)] -> [(a,Int)]
removeMSet42 c ((a,i):t) | c == a && i == 1 = t
                         | c == a = ((a,i-1):t)
                         | otherwise = (a,i) : removeMSet42 c t  
-- 43
constroiMSet' :: Ord a => [a] -> [(a,Int)]
constroiMSet' [] = []
constroiMSet' l = insereMSet41 (last l) (constroiMSet' (init l))

-- 44
partitionEithers44 :: [Either a b] -> ([a],[b])
partitionEithers44 (h:t) = case h of 
                           Left a -> (a:x,y)
                           Right b -> (x,b:y)
                           where (x,y) = partitionEithers44 t
-- 45
catMaybes45 :: [Maybe a] -> [a]
catMaybes45 [] = []
catMaybes45 (h:t) = case h of
                   Just a -> a : catMaybes45 t
                   Nothing -> catMaybes45 t

--46 
--data Movimento = Norte | Sul | Este | Oeste  
--                deriving Show

caminho46 :: (Int,Int) -> (Int,Int) -> [Movimento]
caminho46 (xi,yi) (xf,yf) | yi < yf = Norte : caminho46 (xi,yi+1) (xf,yf)
                          | yi > yf = Sul :  caminho46 (xi,yi-1) (xf,yf)
                          | xi < xf = Este : caminho46 (xi+1,yi) (xf,yf)
                          | xi > xf = Oeste : caminho46 (xi-1,yi) (xf,yf)
                          | otherwise = []
-- 47
data Movimento = Norte | Sul | Este | Oeste deriving Show

posicao :: (Int,Int) -> [Movimento] -> (Int,Int)
posicao p [] = p
posicao (x, y) (m:ms) = posicao (case m of Norte -> (x, y + 1)
                                           Sul -> (x, y - 1)
                                           Este -> (x + 1, y)
                                           Oeste -> (x - 1, y)) ms

hasLoops :: (Int,Int) -> [Movimento] -> Bool
hasLoops _ [] = False
hasLoops pi ms = pi == posicao pi ms || hasLoops pi (init ms)

-- 48
type Ponto = (Float, Float )
data Rectangulo = Rect Ponto Ponto

contaQuadrados48 :: [Rectangulo] -> Int
contaQuadrados48 [] = 0
contaQuadrados48 ((Rect (x1,y1) (x2,y2)):t) | sqrt((x2-x1)^2) == sqrt((y2-y1)^2)= 1 + contaQuadrados48 t
                                            | otherwise = contaQuadrados48 t
-- 49
areaTotal49 :: [Rectangulo] -> Float
areaTotal49 [] = 0
areaTotal49 ((Rect (x1,y1) (x2,y2)):t) = abs(x2-x1) * abs (y2-y1) + areaTotal49 t -- pelo que abs é o módulo da subtração 

-- 50
data Equipamento = Bom | Razoavel | Avariado deriving Show

naoReparar :: [Equipamento] -> Int
naoReparar [] = 0
naoReparar (h:t) = case h of
                   Bom -> 1 + naoReparar t
                   Razoavel -> 1 + naoReparar t
                   Avariado -> naoReparar t



