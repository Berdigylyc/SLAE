import pandas as pd
import matplotlib.pyplot as plt

bicg_data = pd.read_csv("Bicg_times.csv")
cg_data = pd.read_csv("CG_times.csv")

plt.figure(figsize=(12, 6))

plt.plot(bicg_data["Size"], bicg_data["time"], label="BiCG", marker='.', linestyle='-', color='blue')
plt.plot(cg_data["Size"], cg_data["time"], label="CG", marker='.', linestyle='--', color='red')


plt.title("Сравнение времени выполнения методов BiCG и CG")
plt.xlabel("Размер матрицы ")
plt.ylabel("Время, мс")
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.tight_layout()

plt.savefig("comparison_plot.png", dpi=300)
plt.show()