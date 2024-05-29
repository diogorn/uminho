--1
data Frac = F Integer Integer
--b
instance Eq Frac where
     (F x y) == (F x1 y1) = x*y1 == y*x1

--c
instance Ord Frac where
     -- LT -> menor
     -- EQ -> igual
     -- GT -> maior

    compare (F x1 y1) (F x2 y2)
      | f1 <  f2 = LT
      | f1 == f2 = EQ
      | f1 >  f2 = GT
      where f1 = (fromIntegral x1) / (fromIntegral y1)
            f2 = (fromIntegral x2) / (fromIntegral y2)

--d
instance Show Frac where
	show (F x y) = show x ++ "/" ++ show y

--e
instance Num Frac where
     (F x1 y1) + (F x2 y2) | y1 == y2 = F (x1+x2) y1
                           | F (x1*y1 + x2*y2) (y1*y2)

-- ficha 9
--1
bingo :: IO()
bingo = do geraNumeros [1..90]

geraNumeros :: [Int] -> IO()
geraNumeros (h:t) = do
     = putStr ("acabou")
     x <- randomRIO [1..90]
     if (elem x (h:t)) 
          putStr (x)
          geraNumeros (delete x (h:t))
     else geraNumeros (h:t)
