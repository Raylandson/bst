import random

# Nome do arquivo onde os números serão salvos
arquivo_saida = "numeros_sorteados.txt"

with open(arquivo_saida, "w") as f:
    for i in range(1, 1001):
        if i % 10 == 0:
            f.write("2\n")  # A cada 10 linhas, escreve apenas o número 2
        else:
            num_aleatorio = random.randint(1, 10000)
            f.write(f"1 {num_aleatorio}\n")  # Escreve "1 <número aleatório>"
    
    f.write("99\n")  # Última linha com o número 99

print(f"Arquivo '{arquivo_saida}' gerado com sucesso!")

