import sys
import math

def main():
    
    raio = float(sys.argv[1])
    
    angulo = 0
    alfa = 360 / 36
    
    print('<translate time="10" align="true">')
    
    while angulo < 360:

        x = raio * math.cos(math.radians(angulo))
        z = raio * math.sin(math.radians(angulo))
        y = 1
           
        print(f'\t<point x="{x}" y="{y}" z="{z}"/>')
        
        angulo += alfa

    print('</translate>')
    
    
main()