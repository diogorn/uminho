--1
data BTree a = Empty | Node a (BTree a) (BTree a) deriving Show

--a
altura :: BTree a -> Int 
altura Empty = 0
altura (Node n e d) = 1 + (max (altura e) (altura d))

--b
contaNodos :: BTree a -> Float -- alterei a definição de int->floar para usar no ex 3 e)
contaNodos Empty = 0
contaNodos (Node _ e d) = 1 + contaNodos e + contaNodos d

--c
folhas :: BTree a -> Int
folhas Empty = 0
folhas (Node _ Empty Empty) = 1
folhas (Node n e d) = folhas e + folhas d

--d
prune :: Int -> BTree a -> BTree a
prune 0 t = Empty
prune _ Empty = Empty
prune x (Node n e d) = Node n (prune (x-1) e) (prune (x-1) d)

--e
path :: [Bool] -> BTree a -> [a]
path [] _ = []
path _ (Node r Empty Empty) = []
path (True:bls) (Node r (Node er ee ed) (Node dr de dd))  = dr : path bls (Node dr de dd)
path (False:bls) (Node r (Node er ee ed) (Node dr de dd)) = er : path bls (Node er ee ed)

--f
mirror :: BTree a -> BTree a
mirror Empty = Empty
mirror (Node r e d) = Node r (mirror d) (mirror e)

--g
zipWithBT :: (a->b->c) -> BTree a -> BTree b -> BTree c
zipWithBT  _ Empty Empty = Empty
zipWithBT _ Empty _ = Empty
zipWithBT _ _ Empty = Empty
zipWithBT f (Node ra ea da) (Node rb eb db) = (Node (f ra rb) (zipWithBT f ea eb) (zipWithBT f da db)) 

-- r -> raiz
-- e -> esq
-- d -> dir

--h
unzipBT :: BTree (a,b,c) -> (BTree a, BTree b, BTree c)
unzipBT Empty = (Empty,Empty,Empty)
unzipBT (Node (a,b,c) e d) = ((Node a ea da),(Node b eb db),(Node c ec dc))
 where (ea,eb,ec) = unzipBT e
       (da,db,dc) = unzipBT d

--2
--a
minimo :: Ord a => BTree a -> a
minimo (Node r Empty _ ) = r
minimo (Node r e d) = minimo e

--b
semMinimo :: Ord a => BTree a -> BTree a
semMinimo (Node r Empty  d) = Empty
semMinimo (Node r e d) = Node r (semMinimo e) d

--c
minSmin :: Ord a => BTree a -> (a,BTree a)
minSmin t = (minimo t,semMinimo t)

--d ¿¿??
--remove :: Ord a => a -> BTree a -> BTree a

--3
type Aluno = (Numero,Nome,Regime,Classificacao)
type Numero = Int
type Nome = String
data Regime = ORD | TE | MEL deriving Show
data Classificacao = Aprov Int | Rep | Faltou deriving Show
type Turma = BTree Aluno -- abin de procura (ordenada por numero)
--a
inscNum :: Numero -> Turma -> Bool
inscNum _ Empty = False
inscNum n (Node (num,_,_,_) e d) | n == num = True
                                 | n < num = inscNum n e
                                 | otherwise = inscNum n d

--b
inscNome :: Nome -> Turma -> Bool
inscNome _ Empty = False
inscNome n (Node (_,nome,_,_) e d) | n == nome = True
                                   | otherwise = inscNome n e || inscNome n d


--c
trabEst :: Turma -> [(Numero,Nome)]
trabEst (Node (num,nome,reg,_) e d) = case reg of
                                      TE -> [(num,nome)] ++ trabEst e ++ trabEst d
                                      otherwise -> trabEst e ++ trabEst d

--d
nota :: Numero -> Turma -> Maybe Classificacao
nota _ Empty = Nothing
nota n (Node (num,nome,reg,clas) e d) | n == num = Just clas
                                      | n < num = nota n e
                                      | otherwise = nota n d
--e
percFaltas :: Turma -> Float
percFaltas Empty = 0
percFaltas (Node (_,_,_,clas) e d) = ((falts)/(-1 + contaNodos e + contaNodos d))*100
  where falts = case clas of
                 Faltou -> 1 + percFaltas e + percFaltas d
                 otherwise -> percFaltas e + percFaltas d 
--f
mediaAprov :: Turma -> Float
mediaAprov Empty = 0
mediaAprov t = notas t /alunosAprov t

alunosAprov :: Turma -> Float
alunosAprov Empty = 0
alunosAprov (Node (_,_,_,clas) e d) = case clas of
 Aprov n -> 1 + alunosAprov e + alunosAprov d
 otherwise -> alunosAprov e + alunosAprov d

notas :: Turma -> Float
notas Empty = 0
notas (Node (_,_,_,clas) e d) =  case clas of
 Aprov n -> fromIntegral n + notas e + notas d
 otherwise -> notas e + notas d                                       