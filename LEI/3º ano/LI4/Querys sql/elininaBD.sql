USE BDLeiloes;
GO

-- Desativar restrições de chave estrangeira para evitar erros ao eliminar tabelas que são referenciadas por outras tabelas
EXEC sp_MSforeachtable 'ALTER TABLE ? NOCHECK CONSTRAINT all';
GO

-- Eliminar tabelas
DROP TABLE IF EXISTS [dbo].[LeilaoModel];
DROP TABLE IF EXISTS [dbo].[LanceModel];
DROP TABLE IF EXISTS [dbo].[CarroModel];
DROP TABLE IF EXISTS [dbo].[BilhetePremiumModel];
DROP TABLE IF EXISTS [dbo].[AspNetUserTokens];
DROP TABLE IF EXISTS [dbo].[AspNetUsers];
DROP TABLE IF EXISTS [dbo].[AspNetUserRoles];
DROP TABLE IF EXISTS [dbo].[AspNetUserLogins];
DROP TABLE IF EXISTS [dbo].[AspNetUserClaims];
DROP TABLE IF EXISTS [dbo].[AspNetRoles];
DROP TABLE IF EXISTS [dbo].[AspNetRoleClaims];
DROP TABLE IF EXISTS [dbo].[__EFMigrationsHistory];
GO

-- Reativar restrições de chave estrangeira
EXEC sp_MSforeachtable 'ALTER TABLE ? WITH CHECK CHECK CONSTRAINT all';
GO

-- Criar tabelas
CREATE TABLE Utilizador (
  UserID CHAR(36) PRIMARY KEY,
  Nome VARCHAR(45),
  Email VARCHAR(45),
  Password VARCHAR(100),
  Anonimo BIT,
  Premium BIT,
  Role VARCHAR(45),
  BilhetePremium_BilheteID VARCHAR(45),
  Leilao_LeilaoID VARCHAR(45)
  -- Chaves estrangeiras serão adicionadas após a criação de todas as tabelas
);
GO

CREATE TABLE BilhetePremium (
  BilheteID CHAR(36) PRIMARY KEY,
  Usado TINYINT
);
GO

CREATE TABLE Carro (
  CarroID VARCHAR(45) PRIMARY KEY,
  Marca VARCHAR(45),
  Modelo VARCHAR(45),
  Descricao VARCHAR(45),
  PrecoInicial FLOAT
);
GO

CREATE TABLE Leilao (
  LeilaoID VARCHAR(45) PRIMARY KEY,
  DataInicio DATE,
  DataFim DATE,
  TipoLeilao VARCHAR(10),
  PrecoInicial DOUBLE,
  PrecoAtual DOUBLE,
  PrecoFinal DOUBLE,
  Carro_CarroID VARCHAR(45),
  Utilizador_UserID CHAR(36),
  FOREIGN KEY (Carro_CarroID) REFERENCES Carro(CarroID),
  FOREIGN KEY (Utilizador_UserID) REFERENCES Utilizador(UserID)
);
GO

CREATE TABLE Lance (
  LanceID VARCHAR(45) PRIMARY KEY,
  Valor FLOAT,
  Cliente_ClienteID VARCHAR(45),
  Leilao_LeilaoID VARCHAR(45),
  FOREIGN KEY (Cliente_ClienteID) REFERENCES Utilizador(UserID),
  FOREIGN KEY (Leilao_LeilaoID) REFERENCES Leilao(LeilaoID)
);
GO

-- Adicionar chaves estrangeiras
ALTER TABLE Utilizador ADD CONSTRAINT FK_Utilizador_BilhetePremium
FOREIGN KEY (BilhetePremium_BilheteID) REFERENCES BilhetePremium(BilheteID);
GO

ALTER TABLE Utilizador ADD CONSTRAINT FK_Utilizador_Leilao
FOREIGN KEY (Leilao_LeilaoID) REFERENCES Leilao(LeilaoID);
GO


-- Criar índices
CREATE INDEX IDX_BilhetePremium_BilheteID ON Utilizador(BilhetePremium_BilheteID);
GO

CREATE INDEX IDX_Leilao_LeilaoID ON Utilizador(Leilao_LeilaoID);
GO

CREATE INDEX IDX_Carro_CarroID ON Leilao(Carro_CarroID);
GO

CREATE INDEX IDX_Utilizador_UserID ON Leilao(Utilizador_UserID);
GO

CREATE INDEX IDX_Cliente_ClienteID ON Lance(Cliente_ClienteID);
GO

CREATE INDEX IDX_Leilao_LeilaoID ON Lance(Leilao_LeilaoID);
GO
