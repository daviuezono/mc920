#!/usr/bin/python
# -*- coding: utf-8 -*-
from random import randint

# mask size
mask = 3


name = raw_input("Please select one of these images: coins, columns or dragon.\n")
while name not in ["coins", "columns", "dragon"]:
  name = raw_input("ERROR! Please select one of these images: coins, columns or dragon.\n")

image = open(name + "_with_salt_pepper.pgm", "r")
if image.readline() == "P2\n":

  image.readline() # ignore comment line from PGM format

  size_string = image.readline()
  size = size_string.split()
  n_lines = int(size[0])
  n_columns = int(size[1])

  depth_string = image.readline()
  depth = depth_string.split()
  depth = int (depth[0])

  # reading the image into a matrix
  pixel_list = []
  lines = image.readlines()
  for i in range(0, len(lines)):
    values_in_this_line = lines[i].split()
    for pixel in values_in_this_line:
      pixel_list.append(int(pixel))
  image.close()

  matrix = []
  for i in range(0, n_lines - 1):
    pixel_line = []
    for j in range(0, n_columns - 1):
      pixel_line.append(pixel_list[4*i+j])
    matrix.append(pixel_line)

  # creating the final image
  clean_image = open(name + "_without_salt_pepper.pgm", "w")
  clean_image.write("P2\n")
  clean_image.write("# created by Davi K. Uezono - RA 097464\n")
  clean_image.write(size_string)
  clean_image.write(depth_string)

  mx = my = int(mask/2)

  for i in range(0, n_lines - 1):
    for j in range(0, n_columns - 1):
      print matrix[i][j]
      mask_left = max(0, i-mx)
      mask_right = min(n_lines, i+mx)
      mask_up = max(0, j-my)
      mask_down = min(n_columns, j+my)
      mask_of_pixels = []
      for x in range(mask_up, mask_down - 1):
        for y in range(mask_left, mask_right - 1):
          mask_of_pixels.append(matrix[i][j])
      print mask_of_pixels
      mask_of_pixels.sort()
      #print mask_of_pixels
      median = mask_of_pixels[len(mask_of_pixels)/2]
      clean_image.write(str(median))
    clean_image.write("\n")

  clean_image.close()
