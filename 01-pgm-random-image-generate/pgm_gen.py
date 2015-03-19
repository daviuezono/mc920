#!/usr/bin/python
# -*- coding: utf-8 -*-
from random import randint

name = raw_input("Enter image name (without file extension): ")
size = raw_input("Enter image size (square): ")
depth = raw_input("Enter image depth: ")

my_file = open(name + ".pgm", "w")

my_file.write("P2\n")
my_file.write(size + " " + size + "\n")
my_file.write(depth + "\n")
my_file.write("# optional info is (not) optional\n")

size = int(size)
depth = int(depth)

for i in range(1, size):
  list = []
  for j in range(1, size):
    list.append(str(randint(0, depth-1)))
  my_file.write(" ".join(list) + "\n")

my_file.close()

