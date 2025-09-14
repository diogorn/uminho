program MenorDe3;
var
    a, b, c, menor: integer;
begin
    writeln('Introduza três números:');
    readln(a);
    readln(b);
    readln(c);

    if a < b then
        if a < c then
            menor := a
        else
            menor := c
    else
        if b < c then
            menor := b
        else
            menor := c;

    writeln('O menor número é: ', menor);
end.
