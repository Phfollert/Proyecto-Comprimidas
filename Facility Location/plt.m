folder = "/home/nacho/Desktop/Proyecto comprimidas/Facility Location/results/set2 measure/"
a = csvread(strcat(folder,"result1.txt"));
b = csvread(strcat(folder,"result2.txt"));
c = csvread(strcat(folder,"result3.txt"));
d = csvread(strcat(folder,"result4.txt"));
ae = csvread(strcat(folder,"error1.txt"));
be = csvread(strcat(folder,"error2.txt"));
ce = csvread(strcat(folder,"error3.txt"));
de = csvread(strcat(folder,"error4.txt"));
errorbar(a,ae,".b")
title ("Gráfico tiempo vs cantidad caso ficticio localmente denso");
xlabel ("Cantidad m de localidades cercanas requeridas");
ylabel ("Tiempo en segundos");
hold on
errorbar(b,be,".g")
errorbar(c,ce,".y")
errorbar(d,de,".m") 
legend ("Búsqueda con prioridad", "Búsqueda recursiva", "Búsqueda centrada (i)", "Búsqueda centrada (ii)");
