import matplotlib.pyplot as plt

# Чтение файла
sizes = []
times_1 = []   # 1 поток
times_2 = []   # 2 потока
times_4 = []   # 4 потока
times_8 = []   # 8 потоков
times_16 = []  # 16 потоков

with open('results.txt', 'r') as f:
    for line in f:
        if line.strip() and not line.startswith('#'):
            data = line.split()
            if len(data) >= 6:
                sizes.append(int(float(data[0])))
                times_1.append(float(data[1]))
                times_2.append(float(data[2]))
                times_4.append(float(data[3]))
                times_8.append(float(data[4]))
                times_16.append(float(data[5]))

# Построение графиков
plt.figure(figsize=(12, 8))

plt.plot(sizes, times_1, 'o-', label='1 поток', linewidth=2, markersize=8)
plt.plot(sizes, times_2, 's-', label='2 потока', linewidth=2, markersize=8)
plt.plot(sizes, times_4, '^-', label='4 потока', linewidth=2, markersize=8)
plt.plot(sizes, times_8, 'd-', label='8 потоков', linewidth=2, markersize=8)
plt.plot(sizes, times_16, '*-', label='16 потоков', linewidth=2, markersize=8)

plt.xlabel('Размер матрицы (n)', fontsize=14)
plt.ylabel('Время (секунды)', fontsize=14)
plt.title('Умножение матриц: время от размера и количества потоков', fontsize=16)
plt.legend(fontsize=12)
plt.grid(True, alpha=0.3)
plt.xscale('log', base=2)
plt.yscale('log')

plt.tight_layout()
plt.savefig('plot.png', dpi=150)
plt.show()

# Вывод таблицы
print("\nРезультаты:")
print("-" * 80)
print(f"{'n':>8} {'1 поток':>12} {'2 потока':>12} {'4 потока':>12} {'8 потоков':>12} {'16 потоков':>12}")
print("-" * 80)
for i in range(len(sizes)):
    print(f"{sizes[i]:8d} {times_1[i]:12.6f} {times_2[i]:12.6f} {times_4[i]:12.6f} {times_8[i]:12.6f} {times_16[i]:12.6f}")