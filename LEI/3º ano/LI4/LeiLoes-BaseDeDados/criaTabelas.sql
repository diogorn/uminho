CREATE DATABASE LeiLoesBD;
USE LeiLoesBD;

-- Tabela Funcionário
CREATE TABLE dbo.Funcionário (
    IDFuncionário INT PRIMARY KEY,
    Nome VARCHAR(45) NOT NULL,
    Email VARCHAR(45) NOT NULL,
    loginPass VARCHAR(100) NOT NULL
);

-- Tabela Carro
CREATE TABLE dbo.Carro (
    CarroID VARCHAR(45) PRIMARY KEY,
    Marca VARCHAR(45) NOT NULL,
    Modelo VARCHAR(45) NOT NULL,
    Descrição VARCHAR(45) NOT NULL,
    PreçoInicial FLOAT NOT NULL
);

-- Tabela BilhetePremium
CREATE TABLE dbo.BilhetePremium (
    BilheteID VARCHAR(45) PRIMARY KEY,
    DataAquisicao DATE NOT NULL,
    Usado BIT NOT NULL
);

-- Tabela Leilao
CREATE TABLE dbo.Leilao (
    LeilaoID VARCHAR(45) PRIMARY KEY,
    Datalnicio DATE NOT NULL,
    DataFim DATE NOT NULL,
    ExclusividadeLeilao BIT NOT NULL,
    TipoLeilao VARCHAR(10) NOT NULL,
    Carro_CarroID VARCHAR(45),
    Funcionário_IDFuncionário INT,
    FOREIGN KEY (Carro_CarroID) REFERENCES Carro(CarroID),
    FOREIGN KEY (Funcionário_IDFuncionário) REFERENCES Funcionário(IDFuncionário)
);

-- Tabela Cliente
CREATE TABLE dbo.Cliente (
    ClienteID INT PRIMARY KEY,
    Nome VARCHAR(45) NOT NULL,
    Email VARCHAR(45) NOT NULL,
    loginPass VARCHAR(100) NOT NULL,
    Anonimo BIT NOT NULL,
    Premium BIT NOT NULL,
    BilhetePremium_BilheteID VARCHAR(45),
    FOREIGN KEY (BilhetePremium_BilheteID) REFERENCES BilhetePremium(BilheteID)
);

-- Tabela Lance
CREATE TABLE dbo.Lance (
    LanceID VARCHAR(45) PRIMARY KEY,
    Valor FLOAT NOT NULL,
    Cliente_ClienteID INT NOT NULL,
    Leilao_LeilaoID VARCHAR(45) NOT NULL,
    FOREIGN KEY (Cliente_ClienteID) REFERENCES Cliente(ClienteID),
    FOREIGN KEY (Leilao_LeilaoID) REFERENCES Leilao(LeilaoID)
);
