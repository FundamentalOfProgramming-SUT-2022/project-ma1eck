f = open("baaa.txt", "a")


for i in range(1000000):
    f.write("baaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n")

f.close()