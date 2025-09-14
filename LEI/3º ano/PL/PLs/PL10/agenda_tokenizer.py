"""
<?xml version="1.0" encoding="UTF-8"?>
<agenda>
  <entrada ident="e1">
    <nome>Pedro Henriques</nome>
    <email>prh@di.uminho.pt</email>
    <telefone>253 605555</telefone>
  </entrada>
  <entrada ident="e2">
    <nome>José Carlos Ramalho</nome>
    <email>jcr@di.uminho.pt</email>
    <telefone>253 604444</telefone>
  </entrada>
  <grupo ident="gepl">
    <ref apontado="e1"/>
    <ref apontado="e2"/>
    <entrada ident="e3">
      <nome>Mário Martins</nome>
      <email>fmm@di.uminho.pt</email>
      <telefone>253 408878</telefone>
    </entrada>
  </grupo>
</agenda>

"""
"""
Agenda -> Cabecalho Conteudo
Cabecalho -> DCA XMLID ListaAtributos DCF
ListaAtributos -> ListaAtributos Atributo 
              | epsilon
Atributo -> ID '=' vatrib
Conteudo -> AAgenda Lista FAgenda
Lista -> Lista Elem
      | Elem
Elem -> Entrada
      | Grupo

Entrada -> Aentrada Nome Email Telefone Fentrada
Aentrada -> '<' entrada ListaAtributos '>'
Nome -> Anome string Fnome
Email -> Aemail string Femail
      | epsilon
Telefone -> Atelefone string Ftelefone 
Grupo -> Agrupo Listagrupo Fgrupo
Agrupo -> '<' grupo ListaAtributos '>'
Listagrupo -> Listagrupo ElemGrupo
           | epsilon
ElemGrupo -> Ref 
          | Entrada
          | Grupo
Ref -> '<'Ref ListaAtributos '/''>'

"""
import sys
from agenda_lex import lex

lexer.input = sys.stdin.read()
for tok in lexer:
  print(tok)
