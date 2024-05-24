USE BDLeiloes;
GO

-- Criação da tabela 'BilhetePremium'
CREATE TABLE BilhetePremium (
  BilheteID CHAR(36) PRIMARY KEY,
  Usado TINYINT
);
GO



-- Criação da tabela 'Carro'
CREATE TABLE Carro (
  CarroID VARCHAR(45) PRIMARY KEY,
  Marca VARCHAR(45),
  Modelo VARCHAR(45),
  Descricao VARCHAR(45),
  PrecoInicial FLOAT
);
GO

-- Criação da tabela 'Leilao'
CREATE TABLE Leilao (
  LeilaoID VARCHAR(45) PRIMARY KEY,
  DataInicio DATE,
  DataFim DATE,
  TipoLeilao VARCHAR(10),
  PrecoInicial FLOAT,
  PrecoAtual FLOAT,
  PrecoFinal FLOAT,
  Carro_CarroID VARCHAR(45),
  Utilizador_UserID CHAR(36),
  FOREIGN KEY (Carro_CarroID) REFERENCES Carro(CarroID),
  FOREIGN KEY (Utilizador_UserID) REFERENCES Utilizador(UserID)
);
GO



-- Criação da tabela 'Utilizador'
CREATE TABLE Utilizador (
  UserID CHAR(36) PRIMARY KEY,
  Nome VARCHAR(45),
  Email VARCHAR(45),
  Password VARCHAR(100),
  Anonimo BIT,
  Premium BIT,
  Role VARCHAR(45),
  BilhetePremium_BilheteID CHAR(36),
  Leilao_LeilaoID VARCHAR(45),
  FOREIGN KEY (BilhetePremium_BilheteID) REFERENCES BilhetePremium(BilheteID),
  FOREIGN KEY (Leilao_LeilaoID) REFERENCES Leilao(LeilaoID)
  
);
GO


-- Criação da tabela 'Lance'
CREATE TABLE Lance (
  LanceID VARCHAR(45) PRIMARY KEY,
  Valor FLOAT,
  Cliente_ClienteID VARCHAR(45),
  Leilao_LeilaoID VARCHAR(45),
  FOREIGN KEY (Cliente_ClienteID) REFERENCES Utilizador(UserID),
  FOREIGN KEY (Leilao_LeilaoID) REFERENCES Leilao(LeilaoID)
);
GO