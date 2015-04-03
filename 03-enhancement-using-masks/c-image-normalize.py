#!/usr/bin/python
# -*- coding: utf-8 -*-

name = raw_input("Please select one of these images: coins, columns or dragon.\n")
while name not in ["coins", "columns", "dragon"]:
  name = raw_input("ERROR! Please select one of these images: coins, columns or dragon.\n")

image = open(name + ".pgm", "r")
if image.readline() == "P2\n":
  normalized = open(name + "_.pgm", "w")
  normalized.write("P2\n")

  image.readline() # ignore comment line from PGM format
  normalized.write("# created by Davi K. Uezono - RA 097464\n")

  size_string = image.readline()
  normalized.write(size_string)
  size = size_string.split()
  n_lines = int(size[0])
  n_columns = int(size[1])
  
  depth_string = image.readline()
  normalized.write(depth_string)
  depth = depth_string.split()
  depth = int (depth[0])

  pixel_list = []
  lines = image.readlines()
  for i in range(0, len(lines)):
    values_in_this_line = lines[i].split()
    for pixel in values_in_this_line:
      pixel_list.append(pixel)

  image.close()

  for i in range(0, n_lines - 1):
    for j in range(0, n_columns - 1):
      normalized.write(pixel_list[4*i+j])
      normalized.write(" ")
    normalized.write("\n")

  normalized.close()
