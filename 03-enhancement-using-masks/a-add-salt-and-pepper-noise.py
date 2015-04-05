#!/usr/bin/python
# -*- coding: utf-8 -*-
from random import randint

# percentage of salt and pepper pixels
percentage = 5


name = raw_input("Please select one of these images: coins, columns or dragon.\n")
while name not in ["coins", "columns", "dragon"]:
  name = raw_input("ERROR! Please select one of these images: coins, columns or dragon.\n")

image = open(name + ".pgm", "r")
if image.readline() == "P2\n":
  # ignore comment line from PGM format.
  image.readline()

  size_string = image.readline()
  size = size_string.split()

  # number of pixels in image.
  n_pixels = int(size[0]) * int(size[1])
  # number of pixels in image to apply salt and pepper.
  sp_pixels = int(n_pixels * percentage / 100)
  
  depth_string = image.readline()
  depth = depth_string.split()
  depth = int(depth[0])

  # creating the new image with salt and pepper effect.
  salt_and_pepper = open(name + "_adding_salt_pepper.pgm", "w")
  salt_and_pepper.write("P2\n")
  salt_and_pepper.write("# created by Davi K. Uezono - RA 097464\n")
  salt_and_pepper.write(size_string)
  salt_and_pepper.write(depth_string)

  lines = image.readlines()
  for i in range(len(lines)):
    values_in_this_line = lines[i].split()
    for pixel in values_in_this_line:
      # when I have a colection of (max_prob + 1) elements, if I choose one of
      # them arbitrary, I will have the same percentage of choosing one of them
      # as defined in the very beginning of this source code.
      max_prob = int(100 / percentage) - 1
      # the random int between zero and max_prob converted to a boolean value
      # and negated will return a TRUE value in the same percentage as defined
      # in the very beginning of this source code.
      if(not bool(randint(0,max_prob)) and bool(sp_pixels > 0)):
        # arbitrary BLACK or WHITE dots in the image.
        pixel_out = str(depth * randint(0,1))
        salt_and_pepper.write(pixel_out)
        sp_pixels = sp_pixels - 1
      else:
        salt_and_pepper.write(pixel)
      salt_and_pepper.write(" ")
    salt_and_pepper.write("\n")

  image.close()
  salt_and_pepper.close()
