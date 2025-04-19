import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('sor_times.csv')


fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8))


ax1.plot(df['n'], df['time'], 'b-', label='Время (сек)')
ax1.set_xlabel('Размер матрицы (n)')
ax1.set_ylabel('Время выполнения')
ax1.set_title('Зависимость времени выполнения от размера матрицы')
ax1.grid(True)
ax1.legend()


ax2.plot(df['n'], df['iterations'], 'r--', label='Итерации')
ax2.set_xlabel('Размер матрицы (n)')
ax2.set_ylabel('Количество итераций')
ax2.set_title('Зависимость количества итераций от размера матрицы')
ax2.grid(True)
ax2.legend()


plt.tight_layout()
plt.show()


fig, ax = plt.subplots(figsize=(10, 5))
ax.plot(df['n'], df['time'], 'b-', label='Время (сек)')
ax.set_xlabel('Размер матрицы (n)')
ax.set_ylabel('Время выполнения', color='b')
ax.tick_params(axis='y', labelcolor='b')

ax2 = ax.twinx()
ax2.plot(df['n'], df['iterations'], 'r--', label='Итерации')
ax2.set_ylabel('Количество итераций', color='r')
ax2.tick_params(axis='y', labelcolor='r')

plt.title('Совмещенный график: время и итерации')
plt.grid(True)
plt.show()