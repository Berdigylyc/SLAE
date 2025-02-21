import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file
data = [
    ["100x100", 0.1, 2.571e-05, 3.738e-06],
    ["1000x1000", 0.1, 0.000922758, 0.000113671],
    ["10000x10000", 0.1, 0.0933504, 0.0110432],
    ["100x100", 0.2, 7.986e-06, 2.124e-06],
    ["1000x1000", 0.2, 0.000979756, 0.00020606],
    ["10000x10000", 0.2, 0.095569, 0.0185076],
    ["100x100", 0.3, 8.046e-06, 2.495e-06],
    ["1000x1000", 0.3, 0.000966604, 0.000284322],
    ["10000x10000", 0.3, 0.0909965, 0.0242514],
    ["100x100", 0.4, 8.366e-06, 2.796e-06],
    ["1000x1000", 0.4, 0.000975613, 0.000342431],
    ["10000x10000", 0.4, 0.135019, 0.0323598],
    ["100x100", 0.5, 1.4017e-05, 3.417e-06],
    ["1000x1000", 0.5, 0.000955685, 0.000409306],
    ["10000x10000", 0.5, 0.0923117, 0.0364568],
    ["100x100", 0.6, 9.468e-06, 3.808e-06],
    ["1000x1000", 0.6, 0.00095747, 0.000472944],
    ["10000x10000", 0.6, 0.0904664, 0.0426568],
    ["100x100", 0.7, 9.408e-06, 4.118e-06],
    ["1000x1000", 0.7, 0.000952272, 0.000557772],
    ["10000x10000", 0.7, 0.0906309, 0.0472836],
    ["100x100", 0.8, 1.065e-05, 4.749e-06],
    ["1000x1000", 0.8, 0.000994666, 0.000599347],
    ["10000x10000", 0.8, 0.177536, 0.0625488],
  
]

# Convert the data to a DataFrame
df = pd.DataFrame(data, columns=["Size", "Sparsity", "Dense Time (s)", "CSR Time (s)"])

# Plot results
plt.figure(figsize=(12, 6))

# Plot for each sparsity level
for sparsity in df['Sparsity'].unique():
    subset = df[df['Sparsity'] == sparsity]
    
    # Plot Dense matrix results
    plt.plot(subset['Size'], subset['Dense Time (s)'], label=f"Dense (Sparsity={sparsity})", marker='o')
    
    # Plot CSR matrix results
    plt.plot(subset['Size'], subset['CSR Time (s)'], label=f"CSR (Sparsity={sparsity})", marker='x')

# Labels and title
plt.xlabel("Matrix Size")
plt.ylabel("Time (seconds)")
plt.title("Matrix-Vector Multiplication Performance")

# Show legend and grid
plt.legend()
plt.grid(True)

# Save the plot to a file
plt.savefig('matrix_performance.jpg')

# Display the plot
plt.show()
