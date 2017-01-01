
f = open('set2.txt', 'w')
elements = 0
for i in range(200,401):
    for j in range(200,401):
        f.write(str(i)+" "+str(j)+" ")
        elements = elements + 1


print elements
f.close()
