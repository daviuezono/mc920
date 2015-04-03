#!/usr/bin/python
# -*- coding: utf-8 -*-
from random import randint

# percentage of salt and pepper pixels
percentage = 5


name = raw_input("Please select one of these images: coins, columns or dragon.\n")
while name not in ["coins", "columns", "dragon"]:
  name = raw_input("ERROR! Please select one of these images: coins, columns or dragon.\n")

image = open(name + "_.pgm", "r")
if image.readline() == "P2\n":
  salt_and_pepper = open(name + "_with_salt_pepper.pgm", "w")
  salt_and_pepper.write("P2\n")

  image.readline() # ignore comment line from PGM format
  salt_and_pepper.write("# created by Davi K. Uezono - RA 097464\n")

  size_string = image.readline()
  salt_and_pepper.write(size_string)
  size = size_string.split()
  n_pixels = int(size[0]) * int(size[1]) # number of pixels in image
  # number of pixels in image to apply salt and pepper (around 20%)
  sp_pixels = int (n_pixels * percentage / 100)
  
  depth_string = image.readline()
  salt_and_pepper.write(depth_string)
  depth = depth_string.split()
  depth = int (depth[0])

  counter = 0
  lines = image.readlines()
  for i in range(0, len(lines)):
    values_in_this_line = lines[i].split()
    for pixel in values_in_this_line:
      counter = counter + 1
      max_prob = int (100 / percentage) - 1
      if(not bool(randint(0,max_prob)) and bool(sp_pixels > 0)):
        pixel_out = str(depth * randint(0,1))
        salt_and_pepper.write(pixel_out)
        sp_pixels = sp_pixels - 1
      else:
        salt_and_pepper.write(pixel)
      salt_and_pepper.write(" ")
    salt_and_pepper.write("\n")

  image.close()
  salt_and_pepper.close()
