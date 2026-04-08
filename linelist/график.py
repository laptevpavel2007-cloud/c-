import numpy as np
import matplotlib.pyplot as plt


f = open('./results.txt', "r")
s = f.read()
s = s.split("\n")
f.close()

n = []
t = []

for i in range(1, len(s)):
    if not s[i].strip():
        continue
    parts = s[i].split("\t")
    if len(parts) >= 2:
        n.append(int(parts[0]))
        t.append(int(parts[1]))

x = np.array(n)
y = np.array(t)

data_x = x * np.log(x)
a = np.sum((data_x - np.mean(data_x)) * (y - np.mean(y))) / np.sum((data_x - np.mean(data_x))**2)
b = np.mean(y) - a * np.mean(data_x)

N_new = np.array([1500000, 2000000, 2500000, 3000000])
time_pred = a * N_new * np.log(N_new) + b

y_pred = a * x * np.log(x) + b
ss_res = np.sum((y - y_pred)**2)
ss_tot = np.sum((y - np.mean(y))**2)
r2 = 1 - (ss_res / ss_tot)

plt.figure(figsize=(12, 6))
plt.scatter(x, y, color='blue')
plt.scatter(N_new, time_pred, color='red')

x_trend = np.linspace(min(x), max(N_new), 100)
y_trend = a * x_trend * np.log(x_trend) + b

plt.plot(x_trend, y_trend, color='green', linestyle='--', alpha=0.7)


plt.legend()
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.show()