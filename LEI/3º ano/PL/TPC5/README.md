# Processamento de Linguagens 2025

## Objetivo do TPC

O objetivo deste trabalho consiste na construção de um simulador de uma máquina de vendas (vending machine), que inclui análise léxica e processamento de comandos simples. A interação com a máquina permite ao utilizador listar os produtos, adicionar ou remover itens do stock, efetuar pagamentos com moedas e realizar compras.

## Abordagem

Este trabalho tem como principal objetivo implementar um analisador léxico para uma linguagem de comandos de uma máquina de vendas, permitindo que o utilizador interaja com a máquina através de vários comandos. A linguagem suportada inclui os seguintes comandos:

- `LISTAR`: Exibe os produtos disponíveis na máquina.
- `MOEDA`: Regista as moedas inseridas pelo utilizador, atualizando o saldo.
- `SELECIONAR`: Efetua a compra de um produto, se o saldo for suficiente.
- `ADICIONAR`: Adiciona um novo produto ao stock ou atualiza a quantidade e preço de um produto existente.
- `REMOVER`: Remove um produto do stock.
- `SAIR`: Finaliza a interação, devolve o troco e encerra o programa.

O analisador léxico é responsável por identificar e processar os comandos que o utilizador insere, convertendo-os em ações que modificam o estado da máquina de vendas. O stock de produtos é carregado a partir de um ficheiro JSON e pode ser modificado em tempo real, conforme as interações do utilizador.
os tokens usados:
```
tokens = [
    'CMD', 
    'PCODE', 
    'COIN',  
    'FLOAT', 
    'NUM',   
    'COMMA', 
    'DOT'    
]

Comandos: LISTAR, MOEDA, SELECIONAR, SAIR, ADICIONAR, REMOVER
Código do produto (ex.: A23)
Moeda no formato, por exemplo, 1e, 50c, etc.
Números com ponto decimal (para preços)
Números inteiros (para quantidades)
Vírgula separadora
Ponto final (marca fim de sequência, se necessário)
```


#

## Funcionalidades
- **Processamento de Comandos**: Permite que o utilizador execute ações como listar os produtos, adicionar moedas ao saldo, selecionar produtos para compra, adicionar ou remover produtos do stock e sair com o troco.
- **Moedas e Troco**: O utilizador pode inserir moedas (1e, 2e, 50c, 20c, 10c, 5c) e o sistema calcula automaticamente o saldo. No final, o troco é devolvido em moedas de forma otimizada.
- **Persistência**: O stock dos produtos é guardado num ficheiro JSON e atualizado conforme as ações do utilizador.

## Exemplo de Execução
![Res](Screenshot%202025-03-16%20at%2017.54.46.png)

## Identificação

**Nome:** Diogo do Rego Neto  
**Número:** A98197  
**Data:** 16-3-2025

<img src="https://github.com/user-attachments/assets/385c7dc7-ea9c-4c82-b595-82a84b63bac0" width="200">

