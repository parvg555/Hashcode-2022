import os

os.system("g++ -o code code.cpp")

for file in os.listdir("./output"):
    os.remove("./output/" + file)

for file in os.listdir("./input"):
    if file.endswith(".txt"):
        command = "./code "+file
        os.system(command)