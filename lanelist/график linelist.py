import numpy as np
import matplotlib.pyplot as plt

x = np.array([1000, 5000, 10000, 50000, 75000, 100000, 250000, 500000, 750000, 1000000])
y = np.array([0.002, 0.003, 0.003, 0.007, 0.009, 0.014, 0.029, 0.067, 0.081, 0.13])

data_x = x * np.log(x)
a = np.sum((data_x - np.mean(data_x)) * (y - np.mean(y))) / np.sum((data_x - np.mean(data_x))**2)
b = np.mean(y) - a * np.mean(data_x)

x_new = np.array([1500000, 2000000, 2500000, 3000000])
y_new = a * x_new * np.log(x_new) + b

plt.scatter(x, y, color='blue', label='Данные')
plt.scatter(x_new, y_new, color='green', label='Прогноз')
plt.legend()
plt.grid()
plt.show()