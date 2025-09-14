# Processamento de Linguagens 2025

## Objetivo do TPC

Neste TPC, o objetivo foi criar um conversor de Markdown para HTML em Python, sem utilizar bibliotecas externas específicas para essa conversão. O programa suporta diferentes elementos do Markdown, como títulos, formatação de texto, listas, links e imagens.

## Abordagem

Para converter os elementos do Markdown em HTML, utilizei expressões regulares para identificar e substituir os padrões necessários. 
A abordagem consistiu nos seguintes passos:

### 1. Conversão de Títulos
Os títulos de nível 1 a 3 são convertidos para as tags `<h1>`, `<h2>` e `<h3>`, respectivamente, através das seguintes expressões regulares:

```python
text = re.sub(r'^# (.+)$', r'<h1>\1</h1>', text, flags=re.MULTILINE)
text = re.sub(r'^## (.+)$', r'<h2>\1</h2>', text, flags=re.MULTILINE)
text = re.sub(r'^### (.+)$', r'<h3>\1</h3>', text, flags=re.MULTILINE)
```
Posteriormentem, o objetivo seria criar uma única expressão regular para todos os títulos, sem repetir código.

### 2. Formatação de Texto
A formatação em negrito e itálico foi implementada, de forma muito semelhante, utilizando:

- **Negrito:** Texto entre `**...**` é convertido para `<b>...</b>`
- **Itálico:** Texto entre `*...*` é convertido para `<i>...</i>`

```python
text = re.sub(r'\*\*(.+?)\*\*', r'<b>\1</b>', text)
text = re.sub(r'\*(.+?)\*', r'<i>\1</i>', text)
```

### 3. Conversão de Listas Numeradas
As listas numeradas foram convertidas em elementos `<li>` e agrupadas dentro de `<ol>`. Para garantir que blocos consecutivos de `<li>` fiquem dentro de um único `<ol>`, utilizamos a seguinte abordagem:

```python
text = re.sub(r'^\d+\. (.*)$', r'<li>\1</li>', text, flags=re.MULTILINE)
text = re.sub(r'(<li>.*?</li>(?:\n<li>.*?</li>)*)', r'<ol>\n\1\n</ol>', text, flags=re.DOTALL)
```

Explicação da Regex:

- **`^\d+\. (.*)$`** → Captura linhas que começam com um número seguido de um ponto e converte para `<li>...</li>`
- **`(<li>.*?</li>(?:\n<li>.*?</li>)*)`** → Agrupa itens consecutivos de lista para inseri-los dentro de `<ol>...</ol>` 

### 4. Links e Imagens
Para a conversão de links e imagens, utilizei duas expressões regulares separadas:

#### Links
A expressão para converter links Markdown `[texto](url)` em `<a href="url">texto</a>` para evitar que imagens sejam transformadas incorretamente. Para isso, utilizei a seguinte regex:

```python
text = re.sub(r'(?<!\!)\[(.*?)\]\((.*?)\)', r'<a href="\2">\1</a>', text)
```

Explicação:
- `(?<!\!)` → Garante que o link **não** seja precedido por `!`, evitando que imagens sejam capturadas
- `\[(.*?)\]` → Captura o texto do link
- `\((.*?)\)` → Captura a URL do link

#### Imagens
A conversão de imagens `![alt](url)` para `<img src="url" alt="alt">` foi feita com:

```python
text = re.sub(r'!\[([^\]]+)\]\(([^)]+)\)', r'<img src="\2" alt="\1">', text)
```

Explicação:
- `!\[([^\]]+)\]` → Captura o texto alternativo da imagem
- `\(([^)]+)\)` → Captura a URL da imagem

## Resultados obtidos

Após a conversão, o Markdown de entrada:

```markdown
# Título
## Subtítulo
### Subsubtítulo
**bold**
*italico*
1. lista numerada
2. lista numerada
33. lista numerada

Como pode ser consultado em [página da UC](http://www.uc.pt)

![imagem dum coelho](http://www.coellho.com) ...
```

É convertido para:

<img width="520" alt="Screenshot 2025-02-24 at 08 55 15" src="https://github.com/user-attachments/assets/285cfa45-89cc-4b43-b13e-d8c74bc8d62a" />



## Identificação

**Nome:** Diogo do Rego Neto  
**Número:** A98197  
**Data:** 24-02-2025

<img src="https://github.com/user-attachments/assets/385c7dc7-ea9c-4c82-b595-82a84b63bac0" width="200">

