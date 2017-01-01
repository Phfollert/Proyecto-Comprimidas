from antennas import  initial_data_antennas as dict

list = dict["antennas"]
f = open('set1.txt', 'w')

elements = 0
for value in list:
    lat = value["lat"]
    lon = value["lon"]
    if (lat < -33 and lat >= -34.048576 and lon < -70 and lon >= -71.048576):
        lat = (int)((-lat-33)*1000000)
        lon = (int)((-lon-70)*1000000)
        elements = elements+1
        f.write(str(lat)+" "+str(lon)+" ")

print elements
f.close()
