import subprocess
import matplotlib.pyplot as plt

# Compilar o código C
subprocess.run(["gcc", "filaDePrioridades.c", "-o", "marcio"])

# Executar o programa C e capturar a saída
output = subprocess.check_output(["./marcio"]).decode("utf-8")

# Analisar a saída para extrair os tempos de busca
tempos_sem_heap = []
tempos_com_heap = []

numero_atual = None
tempo_sem_heap = None
tempo_com_heap = None

for line in output.split("\n"):
    if line.startswith("Número"):
        if numero_atual is not None:
            tempos_sem_heap.append((numero_atual, tempo_sem_heap))
            tempos_com_heap.append((numero_atual, tempo_com_heap))
        numero_atual = int(line.split(" ")[1].strip(":\n"))
    elif line.startswith("Sem heap"):
        tempo_sem_heap = float(line.split(":")[1].split("segundos")[0].strip())
    elif line.startswith("Com heap"):
        tempo_com_heap = float(line.split(":")[1].split("segundos")[0].strip())

# Preparar os dados para plotagem
numeros = [numero for numero, _ in tempos_sem_heap]
tempos_sem_heap = [tempo for _, tempo in tempos_sem_heap]
tempos_com_heap = [tempo for _, tempo in tempos_com_heap]

# Plotar os tempos de busca
plt.figure(figsize=(10, 6))
plt.plot(numeros, tempos_sem_heap, label='Sem Heap', color='blue')
plt.plot(numeros, tempos_com_heap, label='Com Heap', color='orange')
plt.title("Tempos de busca dos números de 1 a 5000")
plt.xlabel("Número")
plt.ylabel("Tempo (segundos)")
plt.legend()
plt.grid(True)
plt.show()



