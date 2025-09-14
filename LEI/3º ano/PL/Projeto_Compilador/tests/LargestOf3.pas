program Maior3;
        var  
            num1, num2, num3, maior: integer;
        begin
            { Ler 3 números }
            writeln('Introduza o primeiro número: ');  
            readln(num1);
            writeln('Introduza o segundo número: ');  
            readln(num2);
            writeln('Introduza o terceiro número: ');  
            readln(num3);
            if num1 > num2 then
                if num1 > num3 then 
                    maior := num1
                else maior := num3
            elseif num2 > num3 
                then maior := num2
            else 
                maior := num3;
            writeln(maior);
        end.