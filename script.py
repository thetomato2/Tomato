import os

# just some time saving scripts I wrote, 
# nothing important as of yet

files = os.listdir("C:\\dev\\git\\Tomato\\Lua\\src")

outputFile = open("output.txt", "w")

for f in files:
	print(f)
	outputFile.write('"src/' + f + '"\n')

print("done")