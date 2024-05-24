module PF_ficha2 where

import Data.Char

--2
--a
dobros :: [Float] -> [Float]
dobros [] = []
dobros (h:t) = 2 * h : dobros t 
--b
numOcorre :: Char -> String -> Int
numOcorre _ [] = 0 
numOcorre c (h:t) | c == h = 1 + numOcorre c t
                  | otherwise = numOcorre c t

--c
positivos :: [Int] -> Bool
positivos [] = True
positivos (h:t) = h > -1 && positivos t

--d
soPos :: [Int] -> [Int]
soPos [] = []
soPos (h:t) | h>=0 = h : soPos t
            | otherwise = soPos t

--e
somaNeg :: [Int] -> Int
somaNeg [] = 0
somaNeg (h:t) | h>=0 = somaNeg t 
              | otherwise = h + somaNeg t

--f
tresUlt :: [a] -> [a]
tresUlt [] = []
tresUlt (h:t) | length (h:t) <=3 = (h:t)
              | otherwise = tresUlt t

--g
segundos :: [(a,b)] -> [b]
segundos [] = []
segundos ((a,b):t) = b : segundos t

--h
nosPrimeiros :: (Eq a) => a -> [(a,b)] -> Bool
nosPrimeiros _ [] = False
nosPrimeiros c ((a,b):t) | c == a = True
                         | otherwise = nosPrimeiros c t

--i
sumTriplos :: (Num a, Num b, Num c) => [(a,b,c)] -> (a,b,c)
sumTriplos [] = (0,0,0)
sumTriplos [(a,b,c)] = (a,b,c)
sumTriplos ((a1,b1,c1):(a2,b2,c2):t) = sumTriplos((a1+a2,b1+b2,c1+c2):t)

--3
--a
soDigitos :: [Char] -> [Char]
soDigitos [] = []
soDigitos (h:t) | (ord h >= 65 && ord h <=90) || (ord h>=97 && ord h <= 122) = h : soDigitos t
                | otherwise = soDigitos t 
--b
minusculas :: [Char] -> Int
minusculas [] = 0 
minusculas (h:t) | ord h>=97 && ord h <= 122 = 1 + minusculas t
                 | otherwise = minusculas t 

--c
nums :: String -> [Int]
nums [] = []
nums (h:t) | ord h >= 48 && ord h <= 57 =  (ord h - 48) : nums t
           | otherwise = nums t

--4
type Polinomio = [Monomio]
type Monomio = (Float,Int)

--a
conta :: Int -> Polinomio -> Int
conta _ [] = 0 
conta n ((c,e):ps) | n == e = 1 + conta n ps
                   | otherwise = conta n ps

--b
grau :: Polinomio -> Int 
grau [] = 0 
grau [(c,e)] = e 
grau ((c1,e1):(c2,e2):ps) | e1 >= e2 = grau ((c1,e1):ps)
                          | otherwise = grau ((c2,e2):ps)
--c
selGrau :: Int -> Polinomio -> Polinomio
selGrau _ [] = []
selGrau n ((c,e):ps) | n == e = (c,e) : selGrau n ps
                     | otherwise = selGrau n ps  

--d
deriv :: Polinomio -> Polinomio
deriv [] = []
deriv ((c,e):ps) | e == 1 = deriv ps
                 | otherwise = ((c * (fromIntegral e)),(e-1)) : deriv ps 
--e
calcula :: Float -> Polinomio -> Float
calcula _ [] = 0 
calcula x ((c,e):ps) = c * (x^e) + calcula x ps

--f
simp :: Polinomio -> Polinomio
simp [] = []
simp ((c,e):ps) | e == 0 = simp ps 
                | otherwise = (c,e) : simp ps 

--g
mult :: Monomio -> Polinomio -> Polinomio
mult _ [] = []
mult (mC,mE) ((c,e):ps) = ((mC*c),(mE+e)) : mult (mC,mE) ps


--h
normaliza :: Polinomio -> Polinomio
normaliza [] = []
normaliza ((c,e):ps) | (conta e ps) /= 0 =  ( somaMs ((c,e): (selGrau e ps) ) ) : (normaliza (removeMs e ps))
                     | otherwise = (c,e) : normaliza ps 
                      where somaMs :: Polinomio -> Monomio
                            somaMs [(c,e)] = (c,e)
                            somaMs ((c1,e1):(c2,_):ps) = somaMs (((c1+c2),e1):ps)
                            
                            removeMs :: Int -> Polinomio -> Polinomio
                            removeMs _ [] = []
                            removeMs n ((c,e):ps) | n /= e = (c,e) : removeMs n ps
                                                  | otherwise = removeMs n ps 
 
--i
soma :: Polinomio -> Polinomio -> Polinomio
soma [] l2 = normaliza l2
soma l1 [] = normaliza l1
soma p1 p2 = normaliza (p1 ++ p2)

--j
produto :: Polinomio -> Polinomio -> Polinomio
produto [] _ = []
produto _ [] = []
produto (p:ps) p2 = normaliza ((mult p p2) ++ (produto ps p2))


--k
ordena :: Polinomio -> Polinomio
ordena [] = []
ordena (p1:ps) = reverse (insere p1 ps)

insere :: Monomio -> Polinomio -> Polinomio
insere p [] = [p]
insere (c,e) ((c1,e1):ps) | e >= e1 = (c1,e1) : insere (c,e) ps
                          | otherwise = (c,e) : insere (c1,e1) (ps)

--l
equiv :: Polinomio -> Polinomio -> Bool 
equiv [] [] = True
equiv [] _ = False
equiv _ [] = False
equiv p1 p2 | h1 == h2 = equiv t1 t2
            | otherwise = False
            where (h1:t1) = ordena (normaliza p1)
                  (h2:t2) = ordena (normaliza p2)

 