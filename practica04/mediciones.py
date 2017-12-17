import sys
import os
import subprocess
import matplotlib.pyplot as plt

opt = []
no_opt = []
x_axis = []

i = 1024
while i < 536870912:
    command1 = "cat main.c | sed -r 's/aqui/\#define N " + str(i) + "/g' > m.c"
    command2 = "gcc -O1 -funroll-loops m.c"
    command3 = "./a.out"
    os.system(command1)
    os.system(command2)
    a = 0
    for j in range(20):
        result = subprocess.check_output(command3, shell=True)
        a = a + float(result.split("tiempo:")[1])
    opt.append(a / 20)
    x_axis.append(i)
    print(i)
    i = i * 2

i = 2014
while i < 536870912:
    command1 = "cat main.c | sed -r 's/aqui/\#define N " + str(i) + "/g' > m.c"
    command2 = "gcc -O1 m.c"
    command3 = "./a.out"
    os.system(command1)
    os.system(command2)
    a = 0
    for j in range(20):
        result = subprocess.check_output(command3, shell=True)
        a = a + float(result.split("tiempo:")[1])
    no_opt.append(a / 20)
    i = i * 2

plt.semilogx(x_axis, no_opt, label="-O1", marker="o")
plt.semilogx(x_axis, opt, label="-O1 -funroll-loops", marker="x")
plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)
plt.ylabel('Tiempo de ejecucion medio')
plt.xlabel('Tamanho de N')
plt.show()
