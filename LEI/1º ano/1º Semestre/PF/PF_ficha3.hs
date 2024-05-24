module PF_ficha3 where

import PF_ficha1

-- data Hora = H Int Int deriving Show

type Etapa = (Hora,Hora)
type Viagem = [Etapa]

--1
--a
etapaBemCons :: Etapa -> Bool
etapaBemCons (h1,h2) = horaValida h1 && horaValida h2 && horaDepoisDeOutra h1 h2

--b
viagemBemCons :: Viagem -> Bool
viagemBemCons [] = True
viagemBemCons [e] = etapaBemCons e
viagemBemCons (e1:e2:ets) = etapaBemCons e1 && etapasBemCons e1 e2 && viagemBemCons (e2:ets)

etapasBemCons :: Etapa -> Etapa -> Bool
etapasBemCons (h1,h2) (h3,h4) = horaDepoisDeOutra h2 h3

--c
partidaChegada :: Viagem -> Etapa 
partidaChegada [e] = e
partidaChegada (h:t) = (fst h,snd (last t) )

--d 
tempoTotal :: Viagem -> Hora
tempoTotal [] = (H 0 0)
tempoTotal (e1:ets) = minutosParaHoras(horasParaMinutos (somaTempoDeEtapas(tempoEtapa e1:[tempoTotal ets]))) -- minutosParaHoras e horasParaMinutos "anulam-se" mas são usados como especie de conversor para que n haver 1h 99m

tempoEtapa :: Etapa -> Hora
tempoEtapa (h1,h2) = minutosParaHoras(diferencaHoras h1 h2 )

somaTempoDeEtapas :: [Hora] -> Hora
somaTempoDeEtapas [] = (H 0 0)
somaTempoDeEtapas [h] = h
somaTempoDeEtapas ((H h1 m1):(H h2 m2):ts) =  somaTempoDeEtapas ((H (h1+h2) (m1+m2)):ts)

--e
tempoEspera :: Viagem -> Hora
tempoEspera [] = (H 0 0)
tempoEspera [h] = (H 0 0)
tempoEspera ((h1,h2):(h3,h4):ets) =minutosParaHoras(horasParaMinutos (somaTempoDeEtapas (minutosParaHoras(diferencaHoras h2 h3):[tempoEspera ((h3,h4):ets)]))) -- mais uma vez as duas primeiras funções sao para não termos H 0 100

--f
tempoTotalDaViagem :: Viagem -> Hora
tempoTotalDaViagem [] = (H 0 0)
tempoTotalDaViagem l =  minutosParaHoras(horasParaMinutos(somaTempoDeEtapas (tempoTotal l : [tempoEspera l])))

--2
type Poligonal = [Ponto]

--a
comprimentoLinha :: [Ponto] -> Double
comprimentoLinha [] = 0 
comprimentoLinha (p1:p2:t) = dist p1 p2 + comprimentoLinha (p2:t)


--b
linhaFechada :: [Ponto] -> Bool
linhaFechada [] = False
linhaFechada [p1,p2] = False
linhaFechada (p1:ps) = p1 == last ps

--c
triangula  :: Poligonal -> [Figura]
triangula [p1,p2,p3] = [(Triangulo p1 p2 p3)]
triangula (p1:p2:p3:ps) = (Triangulo p1 p2 p3):triangula (p1:p3:ps)


--d ?

--e
mover :: Poligonal -> Ponto -> Poligonal
mover [] p = [p]
mover (h:t) p = (p:h:t)

--f -- not sure
zoom :: Double -> Poligonal -> Poligonal
zoom f ((Cartesiano x y):ps) = (Cartesiano (f * x) (f*y)) : zoom f ps 


--3
data Contacto = Casa Integer 
              | Trab Integer
              | Email String 
              deriving Show

type Nome = String
type Agenda = [(Nome,[Contacto])]

--a
acrescEmail :: Nome -> String -> Agenda -> Agenda
acrescEmail n m [] = [(n,[Email m])]
acrescEmail n m l = ((n,[Email m]):l)

--b -- não encontra mais que um email
verEmails :: Nome -> Agenda -> Maybe [String]
verEmails n [] = Nothing
verEmails n1 ((n,[Email m]):cts) | n1 == n = Just [m]
                                 | otherwise = verEmails n1 cts

--c
contaTelefs :: [Contacto] -> [Integer]
contaTelefs [] = [] 
contaTelefs (h:t) = case h of
                    Casa h -> h : contaTelefs t
                    Trab h -> h : contaTelefs t
                    otherwise -> contaTelefs t

--d -- também nao encontra mais que um elem 
casa :: Nome -> Agenda -> Maybe Integer 
casa n [] = Nothing
casa n ((n1,(c:ct)):cts) | n == n1 =  case c of 
                                      Casa c -> Just c 
                                      otherwise -> casa n ((n1,(ct)):cts)
                         | otherwise = casa n cts

--4
type Dia = Int
type Mes = Int 
type Ano = Int
--type Nome = String
data Data = D Dia Mes Ano deriving Show

type TabDN = [(Nome,Data)]
--a
procura :: Nome -> TabDN -> Maybe Data
procura _ [] = Nothing
procura nome ((n,d):tabDNs) | nome == n = Just d
                            | otherwise = procura nome tabDNs 

--b
idade :: Data -> Nome -> TabDN -> Maybe Int
idade _ _ [] = Nothing
idade dataAtual nome ((n,dataNasc):tabDNs) | nome == n = Just (calculaIdade dataAtual dataNasc)
                                                  | otherwise = idade dataAtual nome tabDNs
                                            
calculaIdade :: Data -> Data -> Int
calculaIdade (D d m a) (D d1 m1 a1) | m > m1 = (a-a1)
                                    | m == m1 && d >= d1 = (a-a1)
                                    | otherwise = (a-a1-1)

--c
anterior :: Data -> Data -> Bool
anterior (D d1 m1 a1) (D d2 m2 a2) | a1 >  a2 = True
                                   | a1 == a2 && m1 >  m2 = True
                                   | a1 == a2 && m1 == m2 && d1 > d2 = True
                                   | otherwise = False

--d
ordena :: TabDN -> TabDN
ordena [] = []
ordena ((n1,d1):tabDNs) =  insere (n1,d1) tabDNs

insere :: (Nome,Data) -> TabDN -> TabDN 
insere n [] = [n]
insere (n,d) ((n1,d1):tabDNs) | anterior d d1 = (n,d) : insere (n1,d1) tabDNs
                              | otherwise = (n1,d1) : insere (n,d) tabDNs

--e
porIdade :: Data -> TabDN -> [(Nome,Int)]
porIdade _ [] = []
porIdade d ((name,age):t) = (name, (calculaIdade d age)) : porIdade d t

--5
data Movimento = Credito Float | Debito Float deriving Show

-- data Data = D Int Int Int

data Extracto = Ext Float [(Data, String, Movimento)] deriving Show

--a
extValor :: Extracto -> Float -> [Movimento]  
extValor (Ext _ []) _ = []                                  
extValor (Ext valor ((dat, descr, mov):mvs)) vlor | vlor > valor = mov : extValor (Ext valor mvs) vlor
                                                  | otherwise = extValor (Ext valor mvs) vlor
--b
filtro :: Extracto -> [String] -> [(Data,Movimento)]
filtro (Ext _ []) _ = []
filtro (Ext valor ((dat, descr, mov):mvs)) l | elem descr l = (dat,mov) : filtro (Ext valor mvs) l

--c
creDeb :: Extracto -> (Float,Float)
creDeb (Ext _ []) = (0,0)
creDeb (Ext valor ((dat, descr, mov):mvs)) = case mov of 
                                             Debito mov -> ((mov+dbt),cre)
                                             Credito mov -> (dbt,(mov+cre))
   where (dbt,cre) = creDeb (Ext valor mvs)

--d
saldo :: Extracto -> Float
saldo (Ext valor ((dat, descr, mov):mvs)) = case mov of
    Debito mov -> (-valor) + saldo (Ext valor mvs)
    Credito mov -> valor +  saldo (Ext valor mvs)



