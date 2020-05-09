"""
Rename jpg files in folder.
1. Shuffle all files
2. Rename
"""
import os
from random import shuffle

path = "./sofa"
files = os.listdir(path)
shuffle(files)

n = 0
for i in files:
    oldname = path + os.sep + files[n]
    newname = path + os.sep +str(n).zfill(8)  +".JPG"
    os.rename(oldname, newname)
    print("finished : ", n)
    n+=1
