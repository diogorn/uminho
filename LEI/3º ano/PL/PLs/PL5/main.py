import re


def escapeP1():
    text = """
            RbtHRGPxP5t4nCyD62aC
            yrAS8rKLTdtfqhfwL8Bj
            sepWC036eLIaiFqMiE50
            04o5fIEMg1qImfiwaSxq
            l86eGZRlY2iC8474sMsJ
            gcF6b8zJRSu1v84CXMIE
            Tmysd0HtNJadpSyntHwJ
            DyFrKlsJgKBySv9bTk3E
            """
    
    # encontra um digito entre um par e uma vogal
    result = re.findall(r'<=[02468])[0-9](?=[AEIOUaeiou]', text)
    print(result)

def main():
    escapeP1()

main()