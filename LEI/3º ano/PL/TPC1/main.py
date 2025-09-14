"""
1. Pretende-se um programa que some todas as sequências de dígitos que encontre num texto; 
2. Sempre que encontrar a string "Off" em qualquer combinação de maiúsculas e minúsculas, esse comportamento é desligado;
3. Sempre que encontrar a string "On" em qualquer combinação de maiúsculas e minúsculas, esse comportamento é novamente ligado; 
4. Sempre que encontrar o caráter "=" , o resultado da soma é colocado na saída.
"""
def somadigitos(imp):
    soma, i = 0, 0
    comportamento = True
    while i < len(imp):
        if imp[i] == '=':
            print(f"Soma: {soma}")
            i += 1

        elif imp[i].isdigit() and comportamento:
            novaString = ''
            while i < len(imp) and imp[i].isdigit(): 
                novaString += imp[i]
                i += 1  
            soma += int(novaString)  

        elif i + 2 < len(imp) and imp[i:i+2].lower() == 'on':  
            comportamento = True
            i += 2  
        elif i + 3 < len(imp) and imp[i:i+3].lower() == 'off':  
            comportamento = False
            i += 3 

        else:
            i += 1 

    return soma

def main():
    while True:
        imp = input("Input:  ")
        if imp.lower() == "sair":  # Condição para sair do loop
            break
        print(f"main said: {somadigitos(imp)}")  # Exibe o resultado da soma

main()