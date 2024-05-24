-- TESTE 2 PF
import Data.Char
import Data.List
import System.Random
--------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------
-- 50 questoões

--1
enumFromTo1 :: Int -> Int -> [Int]
enumFromTo1 x y = [x..y]
--2
enumFromThenTo2 :: Int -> Int-> Int -> [Int]
enumFromThenTo2 x y z | x < z = x : enumFromThenTo2 y (y+(y-x)) z
                      | otherwise = [] 

--3
plusplus :: [a] -> [a] -> [a]
plusplus [] l = l
plusplus l [] = l
plusplus l1 l2 = l1 ++ l2
--4
posElem :: [a] -> Int -> a
posElem (h:t) n | n == 0 = h
                | otherwise = posElem t (n-1)

--5
reverse5 :: [a] -> [a]
reverse5 [] = []
reverse5 (h:t) = reverse5 t ++ [h]

--6
take6 :: Int -> [a] -> [a]
take6 _ [] = []
take6 0 l = l
take6 n (h:t) = take6 (n-1) t

--7
drop7 :: Int -> [a] -> [a]
drop7 _ [] = []
drop7 0 l = []
drop7 n (h:t) = h : drop7 (n-1) t  

--8
zip8 :: [a] -> [b] -> [(a,b)]
zip8 [] _ = []
zip8 _ [] = []
zip8 (x:xs) (y:ys) = (x,y) : zip8 xs ys 

--9
replicate9 :: Int -> a -> [a]
replicate9 0 _ = []
replicate9 n e = e : replicate9 (n-1) e

--10
intersperse10 :: a -> [a] -> [a]
intersperse10 _ [] = []
intersperse10 n [h] = [h]
intersperse10 n (h:t) = h : n : intersperse10 n t

--11
group :: Eq a => [a] -> [[a]]
group [] = []
group l = groupAcc 1 l

groupAcc  :: Eq a => Int -> [a] -> [[a]]
groupAcc _ [] = []
groupAcc acc [h] = [[h]]
groupAcc acc (h0:h1:t) | h0 == h1 = groupAcc (acc+1) (h1:t)
                       | otherwise = replicate9 acc h0 : groupAcc 1 (h1:t)
--12
concat12 :: [[a]] -> [a]
concat12 [[]] = []
concat12 ([]:t) = concat12 t
concat12 ((x:xs):t) = x : concat12 ((xs:t))

--13
--inits13 :: [[a]] -> [a]
--inits13 [[]] = []
--inits13 l = inits13 (init l) ++ [l]

--14
tails14 :: [a] -> [[a]]
tails14 [] = [[]]
tails14 (h:t) = (h:t) : tails14 t

--15
heads :: [[a]] -> [a]
heads [[]] = []
heads ((h:t):[]) = [h]
heads ([]:t) = heads t
heads ((x:_):t) = x : heads t 

--16
total  :: [[a]] -> Int
total [[]] = 0 
total ([]:t) = total t
total ((x:xs):t) = 1 + total ((xs):t)

--17
fun :: [(a,b,c)] -> [(a,c)]
fun [] = []
fun ((a,_,c):t) = (a,c) : fun t 

--18
cola :: [(String,b,c)] -> String
cola [] = []
cola ((a,_,_):t) = a ++ cola t

--19
idade ::  Int -> Int -> [(String,Int)] -> [String]
idade _ _ [] = []
idade dAtual age ((nome,dNas):t) | (dAtual-age) >= dNas = nome : idade dAtual age t
                                 | otherwise = idade dAtual age t

--20
powerEnumFrom :: Int -> Int -> [Int]
powerEnumFrom n m = [(n^0)..(n^(m-1))]

--22
isPrefixOf22 :: Eq a => [a] -> [a] -> Bool
isPrefixOf22 [] _ = True
isPrefixOf22 _ [] = False
isPrefixOf22 (x:xs) (y:ys) | x == y = isPrefixOf22 xs ys
                           | otherwise = False

--23
isSufixOf23 :: Eq a => [a] -> [a] -> Bool
isSufixOf23 l1 l2 = isPrefixOf22 (reverse5 l1) (reverse5 l2)

--24
isSubsequenceOf24 :: Eq a => [a] -> [a] -> Bool
isSubsequenceOf24 [] [] = True
isSubsequenceOf24 [] _ = True
isSubsequenceOf24 _ [] = False
isSubsequenceOf24 (x:xs) (y:ys) | x == y = isSubsequenceOf24 xs ys 
                                | otherwise = isSubsequenceOf24 (x:xs) ys
 
--25
elemIndices ::  Eq a => a -> [a] -> [Int]
elemIndices n l = elemIndicesAux 0 n l

elemIndicesAux  ::  Eq a => Int -> a -> [a] -> [Int]
elemIndicesAux _ _ [] = []
elemIndicesAux acc n (h:t) | n == h = acc : elemIndicesAux (acc+1) n t
                           | otherwise = elemIndicesAux (acc+1) n t

--26
nub26 :: Eq a => [a] -> [a]
nub26 [] = []
nub26 (h:t) | elem h t = nub26 t
            | otherwise = h : nub26 t 

--27
delete27 :: Eq a => a -> [a] -> [a] 
delete27 _ [] = []
delete27 n (h:t) | n == h = t 
                 | otherwise = h : delete27 n t

--28
barras :: Eq a => [a] -> [a] -> [a]
barras [] _ = []
barras l [] = l
barras (x:xs) (y:ys) | x == y = barras xs ys
                     | otherwise =  x : barras xs (y:ys)

--29
union29 :: Eq a => [a] -> [a] -> [a]
union29 [] l = []
union29 l [] = l
union29 l (x:xs) | elem x l = union29 l xs
                 | otherwise = (union29 l xs) ++ [x]

--30
intersect30 :: Eq a => [a] -> [a] -> [a]
intersect30 [] _ = []
intersect30 _ [] = []
intersect30 (x:xs) ys | elem x ys = x : intersect30 xs ys
                      | otherwise = intersect30 xs ys
--31
insert31 :: Ord a => a -> [a] -> [a]
insert31 n [] = []
insert31 n (h:t) | n > h = h : insert31 n t
                 | otherwise =  n : h : t
--32
unwords32  :: [String] -> String
unwords32 [] = []
unwords32 (h:t) = h ++ " " ++ unwords32 t

--33
unlines33 :: [String] -> String
unlines33 [] = []
unlines33 (h:t) = h ++ "\n" ++ unlines33 t

--34
pMaior :: Ord a => [a] -> Int
pMaior l = pos(maior l) l 0
    where maior [h] = h
          maior (h0:h1:t) | h0 > h1 = maior (h0:t)
                          | otherwise = maior (h1:t)
          pos _ [] n = n
          pos m (h:t) n | h == m = n
                        | otherwise = pos m t (n+1)

--35
lookup35 :: Eq a => a -> [(a,b)] -> Maybe b
lookup35 _ [] = Nothing
lookup35 m ((a,b):t) | m == a = Just b
                     | otherwise = lookup35 m t 

--36
preCrescente :: Ord a => [a] -> [a]
preCrescente [] = []
preCrescente (h0:h1:t) | h0 > h1 = [h0]
                       | otherwise = h0 : preCrescente (h1:t)

--37
iSort :: Ord a => [a] -> [a]
iSort [] = []
iSort (h:t) = insert37 h t

insert37 :: Ord a => a -> [a] -> [a] 
insert37 x [] = [x]
insert37 x (h:t) | x > h = h : insert37 x t
                 | otherwise = x : insert37 h t
--38
menor :: String -> String -> Bool 
menor [] [] = True
menor [] _ = True
menor _ [] = False
menor (x:xs) (y:ys) | x < y = True
                    | x > y = False
                    | otherwise = menor xs ys 

--39
elemMSet :: Eq a => a -> [(a,Int)] -> Bool
elemMSet _ [] = False
elemMSet n ((a,i):t) | n == a = True
                     | otherwise = elemMSet n t
--40
converteMSet :: [(a,Int)] -> [a]
converteMSet [] = []
converteMSet ((a,0):t) = converteMSet t
converteMSet ((a,i):t) = a : converteMSet ((a,(i-1)):t)

--41
insereMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
insereMSet c [] = [(c,1)]
insereMSet c ((a,i):t) | c == a = ((a,(i+1)):t)
                       | otherwise = (a,i) : insereMSet c t

--42
removeMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
removeMSet _ [] = []
removeMSet c ((a,i):t) | a == c && i <=1 = t
                       | a == c = (a,(i-1)):t
                       | otherwise = (a,i) : removeMSet c t 
--43

--44
partitionEithers44 :: [Either a b] -> ([a],[b])
partitionEithers44 [] = ([],[])
partitionEithers44 (h:t) = case h of 
                         Left a -> ((a:as),bs)
                         Right b -> (as,(b:bs))
                         where (as,bs) = partitionEithers44 t
--45
catMaybes45 :: [Maybe a] -> [a]
catMaybes45 [] = []
catMaybes45 (h:t) = case h of
    Just h -> h : catMaybes45 t
    Nothing -> catMaybes45 t

--46
data Movimento = Norte | Sul | Este | Oeste deriving Show


caminho :: (Int,Int) -> (Int,Int) -> [Movimento]
caminho (x,y) (a,b) | x < a = Este : caminho ((x+1),y) (a,b)
                    | x > a = Oeste : caminho ((x-1),y) (a,b)
                    | y < b = Norte : caminho (x,(y+1)) (a,b)
                    | y > b = Sul : caminho (x,(y-1)) (a,b)
                    | otherwise = []


--------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------

-- PF - Ficha 5 - Funções de ordem superior

--1
--a
any1 :: (a -> Bool) ->  [a] -> Bool
any1 _ [] = True
any1 f (h:t) = f h && any1 f t

--b
zipWith1 :: (a->b->c) -> [a] -> [b] -> [c]
zipWith1 _ [] _ = []
zipWith1 _ _ [] = []
zipWith1 f (h1:t1) (h2:t2) = (f h1 h2) : zipWith1 f t1 t2

--c
takeWhile1 :: (a -> Bool) -> [a] -> [a]
takeWhile1 _ [] = [] 
takeWhile1 f (h:t) | f h = h : takeWhile1 f t
                   | otherwise = []
--d
dropWhile1 :: (a->Bool) -> [a] -> [a]
dropWhile1 _ [] = []
dropWhile1 f (h:t) | f h = dropWhile1 f t
                   | otherwise = h : t 

--e
span1 :: (a->Bool) -> [a] -> ([a],[a])
span1 _ [] = ([],[])
--span1 f l = ((takeWhile1 f l),(dropWhile1 f l))
span1 f (h:t) | f h = (h:takes,drops) -- esta errado
              | otherwise = (takes,h:drops)
              where (takes,drops) = span1 f t  


--f
deleteByF :: (a -> a -> Bool) -> a -> [a] -> [a]
deleteByF _ _ [] = []
deleteByF f a (h:t) | f a h = t
                    | otherwise = h : deleteByF f a t

--g
sortOn1 :: Ord b => (a -> b) -> [a] -> [a]
sortOn1 _ [] = []
sortOn1 f (h:t) = insere f h t

insere :: Ord b => (a -> b) -> a -> [a] -> [a]
insere _ h [] = [h]
insere f x (h:t) | f x > f h = h : insere f x t
                 | otherwise = x : insere f h t 

--2
type Polinomio = [Monomio]
type Monomio = (Float,Int)

--a
selgrau :: Int -> Polinomio -> Polinomio
selgrau _ [] = []
selgrau i l = filter (\h -> snd h == i) l 

--b
conta :: Int -> Polinomio -> Int
conta _ [] = 0
conta n l = length (selgrau n l)

--c
grau :: Polinomio -> Int
grau l = maximum $ map (\h -> snd h) l 

--d
deriv :: Polinomio -> Polinomio 
deriv [] = []
deriv l = filter (\h -> fst h /= 0 && snd h /= 0) $ map (\(c,e) -> (c* fromIntegral e, (e-1) )) l

--e
calcula :: Float -> Polinomio -> Float
calcula _ [] = 0
calcula x l = sum (map(\(c,e) -> (x^e)*c) l)
-- ou calcula x l = foldl(\acc (c,e) -> acc + c * (x^e)) 0 l  

--f
simp :: Polinomio -> Polinomio
simp [] = []
simp l = filter (\ h -> fst h /= 0) l

--g
mult :: Monomio -> Polinomio -> Polinomio
mult (f,i) l = map (\ (c,e) -> ((c*f),(e+i))) l

--h
ordena :: Polinomio -> Polinomio
ordena [] = []
ordena l = reverse $ (sortOn1 snd l)

--i ---- NAO SEI 
-- normaliza :: Polinomio -> Polinomio
-- normaliza [] = []
-- normaliza l = 
normaliza :: Polinomio -> Polinomio
normaliza [] = []
normaliza ((c,e):ps) | (conta e ps) /= 0 =  ( somaMs ((c,e): (selgrau e ps) ) ) : (normaliza (removeMs e ps))
                     | otherwise = (c,e) : normaliza ps 
                      where somaMs :: Polinomio -> Monomio
                            somaMs [(c,e)] = (c,e)
                            somaMs ((c1,e1):(c2,_):ps) = somaMs (((c1+c2),e1):ps)
                            
                            removeMs :: Int -> Polinomio -> Polinomio
                            removeMs _ [] = []
                            removeMs n ((c,e):ps) | n /= e = (c,e) : removeMs n ps
                                                  | otherwise = removeMs n ps 
--j
soma :: Polinomio -> Polinomio -> Polinomio
soma l1 l2 = normaliza l1++l2

--k
produto :: Polinomio -> Polinomio -> Polinomio
produto [] _ = []
produto _ [] = []
produto l1 l2 = foldl(\ acc (c,e) -> soma (mult (c,e) l2) acc ) [] l1

--l
equiv :: Polinomio -> Polinomio -> Bool
equiv l1 l2 = (normaliza l1) == (normaliza l2)

--2
type Mat a = [[a]]

--a
dimOk :: Mat a -> Bool
dimOk [] = True
dimOk l = all (\h -> length h == length l) l 

--b
dimMat :: Mat a -> (Int,Int)
dimMat [] = (0,0)
dimMat (h:t) = (length (h:t),length h)

--c
addMat :: Num a => Mat a -> Mat a -> Mat a 
addMat [] [] = []
addMat l [] = l
addMat [] l = l
addMat (h1:t1) (h2:t2) = (zipWith1 (+) h1 h2 ): addMat t1 t2 

--d
transpose :: Mat a -> Mat a
transpose [] = []
transpose l = reverse l


--------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------

-- PF -  ficha 6 - Árvores binárias

--1
--a
data BTree a = Empty | Node a (BTree a) (BTree a) deriving Show

a1 = (Node 6 (Node 2 (Node 1 Empty Empty) Empty) (Node 4 (Node 3 Empty Empty) (Node 5 Empty Empty)))

{--
          6
        /   \
       2      4
      /      /  \
    1       3    5


--}

--a
altura :: BTree a -> Int
altura Empty = 0
altura (Node r e d) = 1 + maximum(altura e,altura d) 

--b
contaNodos :: BTree a -> Int
contaNodos Empty = 0
contaNodos (Node r e d) = 1 + contaNodos e + contaNodos d

--c
folhas :: BTree a -> Int
folhas Empty = 0
folhas (Node e Empty Empty) = 1
folhas (Node r e d) = folhas e + folhas d

--d
prune :: Int -> BTree a -> BTree a
prune _ Empty = Empty
prune 0 t = Empty
prune n (Node r e d) = (Node r (prune (n-1) e) (prune (n-1) d) )

--e
path :: [Bool] -> BTree a -> [a]
-- false - esquerda
-- true -  direita
path _ Empty = []
path ((b:[])) (Node r e d) | b = [r] ++ getNextNode d
                           | otherwise = [r] ++ getNextNode e
                           where getNextNode (Node ed _ _) = [ed]
path (b:bls) (Node r e d) | b = r : path bls d
                          | otherwise = r : path bls e

--f
mirror :: BTree a -> BTree a
mirror Empty = Empty
mirror (Node r e d) = (Node r (mirror d) (mirror e))

--g
zipWithBT :: (a -> b -> c) -> BTree a -> BTree b -> BTree c 
zipWithBT _ Empty _ = Empty
zipWithBT _ _ Empty = Empty
zipWithBT f (Node r1 e1 d1) (Node r2 e2 d2) = (Node (f r1 r2) (zipWithBT f e1 e2) (zipWithBT f d1 d2))

--h
unzipBT :: BTree (a,b,c) -> (BTree a,BTree b,BTree c)
unzipBT Empty = (Empty,Empty,Empty)
unzipBT (Node (r1,r2,r3) e d) = ( (Node r1 es1 dr1) , (Node r2 es2 dr2) , (Node r3 es3 dr3) )
                                where (es1,es2,es3) = unzipBT e
                                      (dr1,dr2,dr3) = unzipBT d

--2
--a
minimo :: Ord a => BTree a -> a 
minimo (Node m Empty _) = m
minimo (Node r e d) = minimo e 

--b
semMinimo :: Ord a => BTree a -> BTree a 
semMinimo Empty = Empty
semMinimo (Node m Empty d) = d
semMinimo (Node r e d) = (Node r (semMinimo e) d)    

--c
minSmin :: Ord a => BTree a -> (a,BTree a)
minSmin (Node r Empty d) = (r,Empty)
minSmin (Node r e d) = (a, Node r b d)
 where (a,b) = minSmin e



--3

type Aluno = (Numero,Nome,Regime,Classificacao)
type Numero = Int
type Nome = String
data Regime = ORD | TE | MEL  deriving Show
data Classificacao = Aprov Int | Rep | Faltou deriving Show
type Turma = BTree Aluno --  ́arvore binaria de procura (ordenada por numero)

--a
inscNum :: Numero -> Turma -> Bool
inscNum _ Empty = False
inscNum a (Node (n,_,_,_) e d) | a == n = True
                              | a < n = inscNum a e
                              | otherwise = inscNum a d
--b
inscNome :: Nome -> Turma -> Bool
inscNome _ Empty = False
inscNome a (Node (_,n,_,_) e d) | a == n = True
                                | otherwise = (inscNome a e) || (inscNome a d)

--c
trabEst :: Turma -> [(Numero,Nome)]
trabEst Empty = []
trabEst (Node (a,n,r,_) e d) = case r of
                               TE -> [(a,n)] ++ trabEst e ++ trabEst d
                               otherwise ->  trabEst e ++ trabEst d

--d
nota :: Numero -> Turma -> Maybe Classificacao
nota _ Empty = Nothing
nota a (Node (n,_,_,c) e d) | a == n = Just c
                            | a < n = nota a e
                            | otherwise = nota a d


--e
percFaltas :: Turma -> Float
percFaltas Empty = 0 
percFaltas (Node (_,_,_,c) e d) = case c of 
  Faltou -> 1 + percFaltas e + percFaltas d
  otherwise -> percFaltas e + percFaltas d


--f
mediaAprov :: Turma -> Float
mediaAprov Empty = 0
mediaAprov t = somaNotas t / contaAprovs t 

somaNotas :: Turma -> Float
somaNotas Empty = 0
somaNotas (Node (_,_,_,c) e d) = case c of 
  Aprov x ->  fromIntegral x + somaNotas e + somaNotas d
  _ -> somaNotas e + somaNotas d

contaAprovs :: Turma -> Float
contaAprovs (Node (_,_,_,c) e d) = case c of 
  Aprov x -> 1 + contaAprovs e + contaAprovs d
  _ -> contaAprovs e + contaAprovs d


--g
-- aprovAv :: Turma -> Float
-- aprovAv Empty = 0
-- aprovAv t = aprovados t / avaliados t

-- aprovados :: Turma -> Float
-- aprovados Empty = 0 
-- aprovados (Node (_,_,_,c) e d) = case c of
--                                Aprov -> 1 + aprovados e + aprovados d 
--                                _ -> aprovados e + aprovados d
--                                
-- avaliados :: Turma -> Float
-- avaliados Empty = 0 
-- avaliados (Node (_,_,_,c) e d) = case c of 
--                                Aprov = 1 + avaliados e + avaliados d 
--                                Rep = 1 + avaliados e + avaliados d 
--                                _ -> avaliados e + avaliados d 

--------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------

-- PF -  ficha 7 - Outros tipos de árvores
{-
data ExpInt = Const Int | Simetrico ExpInt | Mais ExpInt ExpInt | Menos ExpInt ExpInt | Mult ExpInt ExpInt

--1
--a
calcula7 :: ExpInt -> Int 
calcula7 t = case t of 
     Const x -> x
     Simetrico x -> - calcula7 x
     Mais a b -> calcula7 a + calcula7 b
     Menos a b -> calcula7 a - calcula7 b
     Mult a b -> calcula7 a * calcula7 b

--b
infixa :: ExpInt -> String
infixa t = case t of 
  Const x -> show x
  Simetrico a -> " - " ++ infixa a
  Mais a b -> "(" ++ infixa a ++ " + " ++ infixa b ++ ")"
  Menos a b -> "(" ++ infixa a ++ " - " ++ infixa b ++ ")"
  Mult a b -> "(" ++ infixa a ++ " * " ++ infixa b ++ ")"


--c
posfixa :: ExpInt -> String
posfixa t = case t of 
  Const x -> show x
  Simetrico a -> " -" ++ posfixa a
  Mais a b -> posfixa a ++ " " ++ posfixa b ++ " +"
  Menos a b -> posfixa a ++ " " ++ posfixa b ++ " -"
  Mult a b -> posfixa a ++ " " ++ posfixa b ++ " *"


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
soma7 :: Num a => RTree a -> a 
soma7 (R r rt) = r + sum (map soma7 rt)

--b
altura7 :: RTree a -> Int 
altura7 (R _ []) = 1
altura7 (R r rt) = length rt 

--c
prune7 :: Int -> RTree a -> RTree a
prune7 _ (R x []) = R x []
prune7 0 (R x l) = R x []
prune7 n (R x l) = R x (map (prune7 (n-1)) l)

--d
mirror7 :: RTree a -> RTree a 
mirror7 (R r []) = (R r [])
mirror7 (R r rt) = R r (map mirror7 (reverse rt ))

--e
-- Travessia postorder: visitar árvore esquerda, depois árvore direita, e a seguir a raiz..

--3

-- data BTree a = Empty | Node a (BTree a) (BTree a)


data LTree a = Tip a | Fork (LTree a) (LTree a)

--a
ltSum :: Num a => LTree a -> a 
ltSum (Tip a) = a
ltSum (Fork a b) = ltSum a + ltSum b 


--b
listaLT :: LTree a -> [a]
listaLT (Tip a) = [a]
listaLT (Fork a b) = (listaLT b) ++ (listaLT a)

--c
ltHeight :: LTree a -> Int 
ltHeight (Tip a) = 1
ltHeight (Fork a b) = 1 + maximum ((ltHeight a),(ltHeight b))

-}
--------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------

-- PF -  ficha 8 - classe de tipos

data Frac = F Integer Integer

--1
--a
normaliza8 :: Frac -> Frac
normaliza8 (F x y) = F (div x m) (div y m)
  where m = mdc x y  


mdc :: Integer -> Integer -> Integer
mdc x y = mdc y (mod x y)

--b
--eq
instance Eq Frac where 
  (F x1 y1) == (F x2 y2) = (x1*y2) == (y1*x2) 
--b
--ord
instance Ord Frac where
 compare (F x1 y1) (F x2 y2) 
  | f1 < f1 = LT -- less than
  | f1 == f2 = EQ -- equal 
  | f1 > f2 = GT  -- grater than
   where f1 = (fromIntegral x1) / (fromIntegral y1)
         f2 = (fromIntegral x2) / (fromIntegral y2) 

--c
--instance Show Frac where
--  (F x y) = show x ++ "/" ++ show y  ??????????

--2
data Exp2 a = Const2 a  | Simetrico2 (Exp2 a) | Mais2 (Exp2 a) (Exp2 a) | Menos2 (Exp2 a) (Exp2 a) | Mult2 (Exp2 a) (Exp2 a)

--a
{-
instance  Show (Exp2 a) where
 show Exp2 x  = case x of 
       Const2 a -> show a
       Simetrico2 a -> "-" ++ (Exp2 a)
       Mais2 a b -> Exp2 a ++ "+" ++ Exp2 b
       Menos2 a b -> Exp2 a ++ "-" ++ Exp2 b
       Mult2 a b -> Exp2 a ++ "*" ++ Exp2 b

-}
--3
data Movimento3 = Credito Float | Debito Float
data Data = D Int Int Int
data Extrato = Ext Float [(Data,String,Movimento3)]

--a
instance Eq Data where
  (D d1 m1 a1) == (D d2 m2 a2) = a2 == a1 && m2 == m1 && d2 == d1 

instance Ord Data where
  compare (D d1 m1 a1) (D d2 m2 a2) | a2 == a1 && m2 == m1 && d2 == d1 = EQ
                                    | a2 < a1 || m2 < m1 || d2 < d1 = LT
                                    | otherwise = GT

--b
instance Show Data where
  show (D d m a) = "Dia " ++ (show d) ++ " mes " ++ (show m) ++ " ano " ++(show a)

--c
ordenaExt :: Extrato -> Extrato
ordenaExt (Ext f []) = (Ext f [])
ordenaExt (Ext n l) = (Ext n (sortBy (\(data1,_,_) (data2,_,_) -> compare data1 data2) l ))

--d
{-
instance Show Extrato where
  show (Ext n ((d,s,m):mvs) = "Saldo anterior: " ++ (show n) ++
                   "\n---------------------------------------" ++
                   "\nData       Descricao   Credito   Debito" ++
                   "\n---------------------------------------\n" ++
                   (show d) ++   (show s) ++ case m of Credito c -> (show c) ++ "       "
                                                       Debito d -> "       " ++ (show d)

-}

--------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------

-- PF - teste 2020 / 2021

--1

barrasT :: Eq a => [a] -> [a] -> [a] 
barrasT [] _ = []
barrasT l [] = l
-- [1,2,3,4,5,1,2] [2,3,4,1,2] == [5,1].
barrasT l (y:ys) = barrasT (delete y l) ys

--2
type MSet a = [(a,Int)]

--a
removeMSetT :: Eq a => a -> [(a,Int)] -> [(a,Int)]
removeMSetT _ [] = []
removeMSetT n ((c,i):t) | n == c && i <= 1 = t
                        | n == c = (c,i-1) : t
                        | otherwise = (c,i) : removeMSetT n t 
                  
--b
calculaT :: MSet a -> ([a],Int) 
calculaT [] = ([],0)
calculaT ((c,i):t) = (c:letras,i+numeros)
  where (letras,numeros) = calculaT t

--3
{-
partes :: String -> Char -> [String]
partes [] _ = []
partes (h:t) c | h == c = [c] : partes t c
               | otherwise = (strchr h) : partes t c

-}

--4
--data BTree a = Empty | Node a (BTree a) (BTree a)

a1t = (Node 5 (Node 3 Empty Empty) (Node 7 Empty (Node 9 Empty Empty))) 
--a
remove :: Ord a => a -> BTree a -> BTree a
remove _ Empty = Empty
remove n (Node r e d) | n < r = (Node r (remove n e) d)  
                      | n > r = (Node r e (remove n d))
                      | otherwise = Empty

--b
-- esta em comentário mas está certo 
{-
instance (Show a) => Show (BTree a) where
  show Empty = "*"
  show (Node r e d) = "(" ++ (show e) ++ "<-" ++ (show r) ++ "->" ++ (show d) ++ ")"
-}

--5


--6
data FileSystem = File Nome | Dir Nome [FileSystem]
--type Nome = String -- definido em 529

fs1 = Dir "usr" [Dir "xxx" [File "abc.txt", File "readme", Dir "PF" [File "exemplo.hs"]],
                   Dir "yyy" [],  Dir "zzz" [Dir "tmp" [], File "teste.c"] ]

--a


--------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------

-- PF - teste 2019 / 2020

--1

--a

intersectT :: Eq a => [a] -> [a] -> [a]
intersectT [] _ = []
intersectT l [] = l
intersectT (x:xs) l | elem x l = x : intersectT xs l
                    | otherwise = intersectT xs l

--b
tailsT :: [a] -> [[a]] 
tailsT [] = [[]]
tailsT (h:t) = (h:t) : tailsT t 

--2
type ConjInt = [Intervalo]
type Intervalo = (Int,Int)

--a
elemsT :: ConjInt -> [Int]
elemsT [] = []
elemsT ((i,f):t) = [i..f] ++ elemsT t

--b

data Contacto = Casa Integer | Trab Integer | Tlm Integer | Email String deriving (Show)
--type Nome = String
type Agenda = [(Nome, [Contacto])]


--3
--a
acrescEmail:: Nome -> String -> Agenda -> Agenda
acrescEmail n m [] = [(n,[Email m])]
acrescEmail n m l = (n,[Email m]) : l

--b
verEmails :: Nome -> Agenda -> Maybe [String] 
verEmails _ [] = Nothing
verEmails n ((nome,c):t) | n == nome = Just (returnEmails c)
                         | otherwise = verEmails n t 
                         where returnEmails :: [Contacto] -> [String]
                               returnEmails [] = []
                               returnEmails (c:cts) = case c of 
                                                      Email m -> m : returnEmails cts
                                                      _ -> returnEmails cts

--c
consulta :: [Contacto] -> ([Integer],[String])
consulta [] = ([],[])
consulta (c:cts) = case c of
       Email c -> (telems,c:mails)
       Casa c -> (c:telems,mails)  
       Trab c -> (c:telems,mails) 
       Tlm c -> (c:telems,mails) 
     where (telems,mails) = consulta cts                                  

--d
consultaIO :: Agenda -> IO ()
consultaIO ((n,c):xs) = do x <- getLine
                           let contactos = aux x ((n,c):xs)
                           putStr (concat [show x ++ "\n" | x <- contactos]) 

                           where aux _ [] = []
                                 aux x ((n,c):xs) = if x == n then c
                                                    else aux x xs

--4
data RTree a = R a [RTree a] deriving (Show, Eq)

--1

--------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------

-- PF - teste 2018 / 2019

--1
--a
elemIndicesT :: Eq a => a -> [a] -> [Int]
elemIndicesT _ [] = []
elemIndicesT n l = elemIndicesAuxT 0 n l

elemIndicesAuxT :: Eq a => Int -> a -> [a] -> [Int]
elemIndicesAuxT _ _ [] = []
elemIndicesAuxT p n (h:t) | n == h = p : elemIndicesAuxT (p+1) n t
                          | otherwise = elemIndicesAuxT (p+1) n t

--b
isSubsequenceOfT :: Eq a => [a] -> [a] -> Bool 
isSubsequenceOfT [] _ = True 
isSubsequenceOfT _ [] = False
isSubsequenceOfT (x:xs) (y:ys) | x == y = isSubsequenceOfT xs ys 
                               | otherwise = False 

--2
--data BTree a = Empty | Node a (BTree a) (BTree a)
--a
lookupAP :: Ord a => a -> BTree (a,b) -> Maybe b
lookupAP _ Empty = Nothing
lookupAP x (Node (ra,rb) e d) | x == ra = Just rb
                              | x < ra = lookupAP x e 
                              | otherwise = lookupAP x d
--b
zipWithBTT :: (a -> b -> c) -> BTree a -> BTree b -> BTree c 
zipWithBTT _ Empty _ = Empty
zipWithBTT _ _ Empty = Empty
zipWithBTT f (Node ra ea da) (Node rb eb db) = (Node (f ra rb) (zipWithBTT f ea eb) (zipWithBTT f da db))


--3
digitAlphaT :: String -> (String,String)
digitAlphaT [] = ([],[])
digitAlphaT (h:t) | isDigit h = (h:numeros,letras)
                  | otherwise = (numeros,h:letras)
                  where (numeros,letras) = digitAlphaT t

--4
data Seq a = Nil | Cons a (Seq a) | App (Seq a) (Seq a)

--a
firstSeq :: Seq a -> a
firstSeq (Cons a _) = a
firstSeq (App Nil b) = firstSeq b
firstSeq (App a _) = firstSeq a 

--b
{-
dropSeq :: Int -> Seq a -> Seq a
dropSeq 0 s = s
dropSeq _ Nil = Nil
dropSeq n (Cons a b) = dropSeq (n-1) b
dropSeq n (App a b) | n > 
-}

--c
instance (Show a) => Show (Seq a ) where

-- > App (Cons 1 Nil) (App (Cons 7 (Cons 5 Nil)) (Cons 3 Nil))
--        <<1,7,5,3>>
  show a = "<<" ++ showw a ++ ">>"

showw :: Show a => Seq a -> String
showw Nil = ""
showw (Cons a Nil) = show a
showw (Cons a b) = show a ++ showw b
showw (App a b) = showw a ++ showw b



