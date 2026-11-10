# directory_traversal.py
import os
from os import system

BASE_PATH = './documents/'
filename = input('\nEnter the file name: ')
filename = os.path.join(BASE_PATH, filename)
system('cat ' + filename)