"""
Neste TPC, é proibido usar o módulo CSV do Python;
Deverás ler o dataset, processá-lo e criar os seguintes resultados:
. Lista ordenada alfabeticamente dos compositores musicais;
. Disrtribuição das obras por período: quantas obras catalogadas em cada período;
. Dicionário em que a cada período está a associada uma lista alfabética dos títulos das obras desse período. 
"""
import re
# csv nome;desc;anoCriacao;periodo;compositor;duracao;_id


def lerDataset():
    with open("obras.csv", "r", encoding="utf-8") as f:
        data = f.read()
        entradas = re.findall(r'^([^;]+);"?([\s\S]*?)"?;([^;]+);([^;]+);([^;]+);([^;]+);([^;]+)$', data, re.MULTILINE)

        # transformar a lista de tuplos numa lista de listas
        entradas = [list(entrada) for entrada in entradas]

        return entradas


def ordenarCompositoresAlfa(data):
    compositores = []
    for entrada in data:
        compositores.append(entrada[4])
    compositores = list(set(compositores))
    compositores.sort()
    return compositores

def obraPPeriodo(data):
    periodos = {}
    for entrada in data:
        periodo = entrada[3]
        if periodo in periodos:
            periodos[periodo] += 1
        else:
            periodos[periodo] = 1
    return periodos

def distobrasPeriodo(data):
    periodos = {}
    for entrada in data:
        periodo = entrada[3]
        obra = entrada[0] 
        if periodo in periodos:
            periodos[periodo].append(obra)
        else:
            periodos[periodo] = [obra]
        
    for periodo in periodos:
        periodos[periodo].sort()
    return periodos


def main():
    data = lerDataset()
    on = True
    while on:
        print("1 - Lista ordenada alfabeticamente dos compositores musicais\n2 - Disrtribuição das obras por período: quantas obras catalogadas em cada período\n3 - Dicionário em que a cada período está a associada uma lista alfabética dos títulos das obras desse período\n")
        opcao = int(input("Escolha uma opção: "))
        if opcao == 1:
            print(ordenarCompositoresAlfa(data))
        elif opcao == 2:
            print(obraPPeriodo(data))
        elif opcao == 3:
            print(distobrasPeriodo(data))
        else:
            print("sair")
            on = False 


main()