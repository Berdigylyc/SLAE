import matplotlib.pyplot as plt
import numpy as np


data = {
    '100x100': {
        'Chebyshev': {'iters': 16, 'time': 1},
        'Jacobi': {'iters': 101, 'time': 2.797},
        'Gauss-Seidel': {'iters': 145, 'time': 3.435}
    },
    '1000x1000': {
        'Chebyshev': {'iters': 18, 'time': 172},
        'Jacobi': {'iters': 325, 'time': 65.9},
        'Gauss-Seidel': {'iters': 83, 'time': 15.8}
    },
    '10000x10000': {
        'Chebyshev': {'iters': 20, 'time': 19830}
    }
}

methods = ['Chebyshev', 'Jacobi', 'Gauss-Seidel']
matrix_sizes = list(data.keys())

# Create figure
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 10))


bar_width = 0.25
for i, method in enumerate(methods):
    iters = []
    labels = []
    for size in matrix_sizes:
        if method in data[size]:
            iters.append(data[size][method]['iters'])
            labels.append(size)
    x = np.arange(len(labels)) + i*bar_width
    ax1.bar(x, iters, width=bar_width, label=method)

ax1.set_title('Iteration Count Comparison')
ax1.set_xticks(np.arange(len(matrix_sizes)) + bar_width)
ax1.set_xticklabels(matrix_sizes)
ax1.set_ylabel('Number of Iterations')
ax1.legend()
ax1.grid(True, linestyle='--', alpha=0.6)


for i, method in enumerate(methods):
    times = []
    labels = []
    for size in matrix_sizes:
        if method in data[size]:
            times.append(data[size][method]['time'])
            labels.append(size)
    x = np.arange(len(labels)) + i*bar_width
    ax2.bar(x, times, width=bar_width, label=method)

ax2.set_title('Computation Time Comparison (Log Scale)')
ax2.set_xticks(np.arange(len(matrix_sizes)) + bar_width)
ax2.set_xticklabels(matrix_sizes)
ax2.set_ylabel('Time (ms)')
ax2.set_yscale('log')
ax2.legend()
ax2.grid(True, linestyle='--', alpha=0.6)

plt.tight_layout()
plt.show()