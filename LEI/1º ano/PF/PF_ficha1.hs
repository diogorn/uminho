module PF_ficha1 where

import Data.Char

--1
--a
perimetro1 :: Float -> Float 
perimetro1 r = 2*pi*r

--b
distan :: (Float,Float) -> (Float,Float) -> Float
distan (x1,y1) (x2,y2) = sqrt ((y2-y1)^2 + (x2-x1)^2)

--c
primUIt :: [a] -> (a,a)
primUIt (h:t) = (h, last t)
--d
multiplo :: Int -> Int -> Bool
multiplo m n = mod m n == 0
--e
truncaImpar :: [a] -> [a]
truncaImpar [] = []
truncaImpar (h:t) | mod (length (h:t)) 2 == 0 = (h:t)
                  | otherwise = t

--f
max2 :: Int -> Int -> Int
max2 x y | x >=y = x
         | otherwise = y 
--g
max3 :: Int -> Int -> Int -> Int
max3 x y z = max2 x (max2 y z)

--2
--a
nRaizes :: Int -> Int -> Int -> Int
nRaizes a b c | delta > 0 = 2
              | delta == 0 = 1
              | otherwise = 0
              where delta = b^2 - 4 * a * c 
--b
raizes :: Float -> Float -> Float -> [Float]
raizes a b c | delta /= 0 = []
             | otherwise = [(-b - delta)/2*a,(-b + delta)/2*a]
                where delta = b^2 - 4 * a * c 

--3
type Hora3 = (Int,Int)
-- ex: (0,15) - meia noite e um quarto

--a
horaValida3 :: Hora3 -> Bool
horaValida3 (h,m) = h>=0 && h <24 && m>=0 && m < 60

--b
horaDepoisDeOutra3 :: Hora3 -> Hora3 -> Bool
horaDepoisDeOutra3 (h1,m1) (h2,m2) | h1 > h2 = True
                                   | h1 == h2 &&  m1 > m2 = True
                                   | otherwise = False
--c
horasParaMinutos3 :: Hora3 -> Int
horasParaMinutos3 (h,m) = h * 60 + m

--d
minutosParaHoras3 :: Int -> Hora3
minutosParaHoras3 m = (div m 60 , mod m 60)

--e
diferencaHoras3 :: Hora3 -> Hora3 -> Int
diferencaHoras3 (h1,m1) (h2,m2) =horasParaMinutos3(h2-h1,m2-m1)

--f
addMins3 :: Hora3 -> Int -> Hora3
addMins3 (h,m) add | m+add > 59 = (h+(div (m+add) 60),mod (m+add) 60)
                   | otherwise = (h,m+add)

--4
data Hora = H Int Int deriving (Show,Eq)

--a
horaValida :: Hora -> Bool
horaValida (H h m) =  h>=0 && h <24 && m>=0 && m < 60
--b
horaDepoisDeOutra :: Hora -> Hora -> Bool
horaDepoisDeOutra (H h1 m1) (H h2 m2) | h2 > h1 = True
                                      | h2 == h1 &&  m2 > m1 = True
                                      | otherwise = False

--c
horasParaMinutos :: Hora -> Int
horasParaMinutos (H h m) = h*60+m

--d
minutosParaHoras :: Int -> Hora
minutosParaHoras m = (H (div m 60) (mod m 60) )

--e
diferencaHoras :: Hora -> Hora -> Int
diferencaHoras (H h1 m1) (H h2 m2) = horasParaMinutos (H (h2-h1) (m2-m1))

--f
addMins :: Hora -> Int -> Hora
addMins (H h m) add | m+add > 59 = (H (h+(div (m+add) 60)) (mod (m+add) 60))
                    | otherwise = (H h (m+add))
                    

--5
data Semaforo = Verde | Amarelo | Vermelho deriving (Show,Eq) 
--a
next :: Semaforo -> Semaforo 
next x = case x of
    Vermelho -> Verde
    Amarelo -> Vermelho
    Verde -> Amarelo

--b
stop :: Semaforo -> Bool
stop x = case x of
         Verde -> False
         _ -> True

--c
safe :: Semaforo -> Semaforo -> Bool
safe a b = a == Vermelho || b ==  Vermelho


--6
data Ponto = Cartesiano Double Double | Polar Double Double deriving (Show,Eq)
--a
posx :: Ponto -> Double
posx (Cartesiano x y) = x
posx (Polar r a) = r * cos a 

--b
posy :: Ponto -> Double
posy (Cartesiano x y) = y
posy (Polar r a) = r * sin a

--c
raio :: Ponto -> Double
raio (Cartesiano x y) = sqrt(x^2+y^2)
raio (Polar r a) = r 

--d
angulo :: Ponto -> Double
angulo (Cartesiano x y) = atan y/x
angulo (Polar r a) = a

--e
dist :: Ponto -> Ponto -> Double
dist (Cartesiano x1 y1) (Cartesiano x2 y2) = sqrt((y2-y1)^2+(x2-x1)^2)

--7
data Figura = Circulo Ponto Double | Rectangulo Ponto Ponto | Triangulo Ponto Ponto Ponto deriving (Show,Eq)

--a
poligono :: Figura -> Bool
poligono f = case f of
    Circulo _ _-> False
    _ -> True

--b
vertices :: Figura -> [Ponto]
vertices f = case f of
     Rectangulo a b -> [a,b]
     Triangulo  a b c -> [a,b,c]
     _ -> []

--c
area :: Figura -> Double
area (Triangulo p1 p2 p3) = 
      let a = dist p1 p2
          b = dist p2 p3
          c = dist p3 p1
          s = (a+b+c)/2 -- semi-perimetro
          in sqrt (s*(s-a)*(s-b)*(s-c)) -- formula de Heron
area (Rectangulo p1 p2) = abs (posy p2 - posy p1) * abs (posx p2 - posx p1)
area (Circulo p r) = pi*r^2

--d
perimetro :: Figura -> Double
perimetro (Circulo p r) = 2*pi*r
perimetro (Rectangulo p1 p2) = 2*(abs (posy p2 - posy p1) + abs (posx p2 - posx p1))
perimetro (Triangulo p1 p2 p3) = a + b + c
        where a = dist p1 p2
              b = dist p2 p3
              c = dist p3 p1

--8

-- ord : carcter -> numero da tabela ascci
-- chr : numero da tabela ascci -> carcter

--a
isLowerA :: Char -> Bool
isLowerA c = ord c >=97 && ord c <=122
--b
isDigitB :: Char -> Bool
isDigitB d = ord d >= 48 && ord d <=57
--c
isAlphaC :: Char -> Bool
isAlphaC l = (isLowerA l) || (ord l >=65 && ord l <=90) 
--d
toUpperD :: Char -> Char
toUpperD l = chr((ord l)-32)
--e
intToDigitE :: Int -> Char
intToDigitE i = chr (i + 48)
--f
digitToIntF :: Char -> Int
digitToIntF c = ord (c)-48








 