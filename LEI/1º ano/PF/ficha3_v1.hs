module PF_ficha3 where 
import PF_ficha1

-- data Hora2 = H Int Int deriving (Show,Eq)
type Etapa = (Hora2,Hora2)
type Viagem = [Etapa]
 

-- a
etapaValida :: Etapa -> Bool
etapaValida (h1,h2) = horaValida2 h1 && horaValida2 h2 && horaDepoisDeOutra2 h2 h1

-- b
viagemValida :: Viagem -> Bool
viagemValida [] = True
viagemValida [(h1,h2)] = etapaValida (h1,h2)
viagemValida ((h1,h2):(h3,h4):hs) = etapaValida (h1,h2) && horaDepoisDeOutra2 h3 h2 && viagemValida ((h3,h4):hs)

-- c
partidaChegada :: Viagem -> (Hora2,Hora2)
partidaChegada [(h1,h2)] = (h1,h2) 
partidaChegada ((h1,h2):t) = (h1, snd(last t))
-- prof -> partidaChegada ((h1,h2):(h3,h4):hs) = partidaChegada ((h1,h4):hs)

-- d
tempoViagem :: Viagem -> Hora2
tempoViagem v = auxTemp (partidaChegada v)

auxTemp :: (Hora2,Hora2) -> Hora2
auxTemp (H h1 m1,H h2 m2) = (H (h2-h1) (m2-m1))

-- prof version
tempoViagemProf :: Viagem -> Hora2
tempoViagemProf [] = H 0 0
tempoViagemProf (e1:es) = somaDuracao(duracao e1) (tempoViagemProf es)

duracao :: Etapa -> Hora2
duracao (H h1 m1, H h2 m2) | h2 >= h1 && m2 > m1 = H (h2-h1) (m2-m1)
                           | m2 < m1 = H (h2-h1-1) (m2-m1) + 60

somaDuracao :: Hora2 -> Hora2 -> Hora2
somaDuracao (H h1 m1) (H h2 m2) = H (h1+h2) (m1+m2)


-- e
-- dá o resultado em minutos, tentar usar o minutosToHoras2 para converter (descobrir o erro)
--tempoEspera :: Viagem -> Int
--tempoEspera [] = 0 
--tempoEspera [(h1,h2)] = 0
--tempoEspera ((h1,h2):(h3,h4):hs) = (subtraiHoras h2 h3) + tempoEspera ((h3,h4):hs)
--
--subtraiHoras :: Hora2 -> Hora2 -> Int
--subtraiHoras (H h1 m1) (H h2 m2) | (m1+m2 >= 60) = H (h1+h2+1) (m2-m1)
--                                 | otherwise = H (h1+h2) (m1+m2)
--


-- f
 


-- 2
type Poligonal = [Ponto]
-- data Ponto = Cartesiano Double Double | Polar Double Double
-- a 
-- ' -> linha
-- cumprimentoLinha :: Ponto -> Ponto -> Double
-- cumprimentoLinha p1 p2 = 