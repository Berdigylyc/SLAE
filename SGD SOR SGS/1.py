import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


df = pd.read_csv('sor_times.csv')


plt.figure(figsize=(10, 6), facecolor='white')
ax = plt.gca()


plt.plot(df['omega'], df['time'], 
         marker='o', 
         markersize=5,
         linestyle='-', 
         linewidth=1.5,
         color='royalblue',
         markerfacecolor='orange',
         markeredgecolor='navy')


ax.set_facecolor('whitesmoke')
ax.grid(True, linestyle='--', linewidth=0.5, alpha=0.7, color='gray')


plt.xlabel('Relaxation Parameter (ω)', fontsize=12, fontweight='bold')
plt.ylabel('Execution Time (seconds)', fontsize=12, fontweight='bold')
plt.title('SOR Method: Execution Time vs Relaxation Parameter', 
          fontsize=14, pad=20, fontweight='bold')


plt.axvspan(1.0, 1.5, alpha=0.2, color='limegreen', label='Optimal Range (1.0-1.5)')


plt.xticks(np.arange(0, 2.1, 0.2), fontsize=10)
plt.yticks(fontsize=10)
plt.xlim(0, 2.0)


plt.legend(loc='upper right', frameon=True, facecolor='white')
plt.tight_layout()


plt.savefig('sor_timing.png', dpi=300, bbox_inches='tight')
plt.show()