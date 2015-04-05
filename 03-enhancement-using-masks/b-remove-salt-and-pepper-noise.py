#!/usr/bin/python
# -*- coding: utf-8 -*-
from random import randint

# mask size
mask = 3


name = raw_input("Please select one of these images: coins, columns or dragon.\n")
while name not in ["coins", "columns", "dragon"]:
  name = raw_input("ERROR! Please select one of these images: coins, columns or dragon.\n")

salt_and_pepper = open(name + "_adding_salt_pepper.pgm", "r")
if salt_and_pepper.readline() == "P2\n":
  # ignore comment line from PGM format.
  salt_and_pepper.readline()

  size_string = salt_and_pepper.readline()
  size = size_string.split()
  n_columns = int(size[0])
  n_lines = int(size[1])

  depth_string = salt_and_pepper.readline()
  depth = depth_string.split()
  depth = int(depth[0])

  # reading the input image into a pixel list.
  pixel_list = []
  lines = salt_and_pepper.readlines()
  for i in range(len(lines)):
    values_in_this_line = lines[i].split()
    for pixel in values_in_this_line:
      pixel_list.append(int(pixel))
  salt_and_pepper.close()

  # output pixel list initialized as the same of input one.
  pixel_list_out = pixel_list
  mw = int(mask/2)

  # rastering the input image including borders.
  for i in range(n_lines):
    for j in range(n_columns):
      mask_of_pixels = []
      for x in range (i - mw, i + mw + 1):
        for y in range (j - mw, j + mw + 1):
          # ignoring negative bounds.
          if (x >= 0 and x < n_lines and y >= 0 and y < n_columns):
            mask_of_pixels.append(pixel_list[x*n_columns + y])
      # median value is the central value of an ordered vector.
      mask_of_pixels.sort()
      median = int(len(mask_of_pixels)/2)
      pixel_list_out[i*n_columns + j] = mask_of_pixels[median]

  # initializing the final (clean) image.
  clean_image = open(name + "_removing_salt_pepper.pgm", "w")
  clean_image.write("P2\n")
  clean_image.write("# created by Davi K. Uezono - RA 097464\n")
  clean_image.write(size_string)
  clean_image.write(depth_string)

  # printing final pixel values in the final (clean) image.
  for i in range(n_lines):
    for j in range(n_columns):
      clean_image.write(str(pixel_list_out[i*n_columns + j]) + " ")
    clean_image.write("\n")
  clean_image.close()
