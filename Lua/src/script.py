import os

files = os.listdir("C:\\dev\\git\\Tomato\\Lua\\src")

outputFile = open("output.txt", "w")
for f in files:
	print(f)
	outputFile.write('"' + f + '"\n')

print("done")