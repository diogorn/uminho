program SomaN;
var  
    i, n, num, soma: integer;
begin  
    soma := 0;
    writeln('Quantos números quer somar?');
    readln(n);
    for i := 1 to n do
    begin
        writeln('Introduza o número ', i, ':');
        readln(num);
        soma := soma + num;
    end;
    writeln('A soma é: ', soma);
end.
