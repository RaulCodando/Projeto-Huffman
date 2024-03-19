import os
import matplotlib.pyplot as plt

# Função para compilar e executar o programa C e capturar a saída
def compile_and_execute():
    # Compilar o programa C
    os.system('gcc filadePrioridades2.c -o marcio')
    # Executar o programa C e redirecionar a saída para um arquivo
    os.system('./marcio > output.txt')

# Função para ler o arquivo de saída e extrair os valores das iterações
def extract_values(file_name):
    iterations_with_heap = []
    iterations_without_heap = []

    with open(file_name, 'r') as file:
        for line in file:
            if 'com heap' in line:
                # Verificar se a linha contém a palavra "com heap" e extrair o valor da iteração
                iterations_with_heap.append(int(line.split()[-2]))
            elif 'sem heap' in line:
                # Verificar se a linha contém a palavra "sem heap" e extrair o valor da iteração
                iterations_without_heap.append(int(line.split()[-2]))

    return iterations_with_heap, iterations_without_heap

# Função para plotar os resultados
def plot_results(iterations_with_heap, iterations_without_heap):
    plt.plot(iterations_with_heap, label='Com Heap', color='red')
    plt.plot(iterations_without_heap, label='Sem Heap', color='blue')
    plt.xlabel('Elemento')
    plt.ylabel('Iterações')
    plt.title('Iterações com e sem Heap')
    plt.legend()
    plt.show()

# Função para plotar os resultados com heap
def plot_heap_results(iterations_with_heap):
    plt.plot(iterations_with_heap, label='Com Heap', color='red')
    plt.xlabel('Elemento')
    plt.ylabel('Iterações')
    plt.title('Iterações com Heap')
    plt.legend()
    plt.show()

# Função para plotar os resultados sem heap
def plot_without_heap_results(iterations_without_heap):
    plt.plot(iterations_without_heap, label='Sem Heap', color='blue')
    plt.xlabel('Elemento')
    plt.ylabel('Iterações')
    plt.title('Iterações sem Heap')
    plt.legend()
    plt.show()

# Compilar e executar o programa C
compile_and_execute()

# Nome do arquivo de saída
output_file = 'output.txt'

# Extrair os valores das iterações
iterations_with_heap, iterations_without_heap = extract_values(output_file)

# Plotar os resultados
plot_results(iterations_with_heap, iterations_without_heap)

# Plotar resultados apenas com heap
plot_heap_results(iterations_with_heap)

# Plotar resultados apenas sem heap
plot_without_heap_results(iterations_without_heap)







