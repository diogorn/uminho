# Processamento de Linguagens 2025

## Objetivo do TPC

Analisador léxico de uma linguagem típica de queries

## Abordagem

Construir um analisador léxico para uma liguagem de query com a qual se podem escrever frases como: 

# DBPedia: obras de Chuck Berry
select ?nome ?desc where {
?s a dbo:MusicalArtist.
?s foaf:name "Chuck Berry"@en .
?w dbo:artist ?s.
?w foaf:name ?nome.
?w dbo:abstract ?desc
} LIMIT 1000

# Resultados obtidos
![Res](Screenshot%202025-03-11%20at%2008.56.30.png)

## Identificação

**Nome:** Diogo do Rego Neto  
**Número:** A98197  
**Data:** 6-03-2025

<img src="https://github.com/user-attachments/assets/385c7dc7-ea9c-4c82-b595-82a84b63bac0" width="200">

