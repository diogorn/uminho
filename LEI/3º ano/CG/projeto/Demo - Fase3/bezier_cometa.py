import math

def desenhar_gomo(alfa1, alfa2, beta1, beta2):
    
    pontos = []
    
    for i in range(4):
        
        u = i / 3
        beta = (1-u)*beta1 + u*beta2

        for j in range(4):
            
            v = j / 3
            alfa = (1-v)*alfa1 + v*alfa2

            x = math.cos(alfa) * math.cos(beta)
            y = math.sin(alfa)
            z = math.cos(alfa) * math.sin(beta)

            pontos.append((x, y, z))
            
    return pontos

def main():
    
    lista = []
    
    #Hemisférios sul e norte
    for alfa in [(0, math.pi/2),((3*math.pi)/2, math.pi*2)]:
        
        #4 quadrantes
        for beta in [(0,math.pi/2),(math.pi/2,math.pi),(math.pi, (3*math.pi)/2),((3*math.pi)/2, math.pi*2)]:
            
            alfa1, alfa2 = alfa
            beta1, beta2 = beta
            
            gomo = desenhar_gomo(alfa1, alfa2, beta1, beta2)
            lista.append(gomo)
        
    tamanho = len(lista)
    
    #Print dos patches    
    print(tamanho)
    for i in range(tamanho):
        
        print(f"{i*16},{i*16+1},{i*16+2},{i*16+3},{i*16+4},{i*16+5},{i*16+6},{i*16+7},{i*16+8},{i*16+9},{i*16+10},{i*16+11},{i*16+12},{i*16+13},{i*16+14},{i*16+15}")
    
    #Print dos pontos
    print(tamanho*16)
    for i, gomo in enumerate(lista):
        
        for j, (x, y, z) in enumerate(gomo):
            
            print(f"{x:.3f}, {y:.3f}, {z:.3f}")

main()
