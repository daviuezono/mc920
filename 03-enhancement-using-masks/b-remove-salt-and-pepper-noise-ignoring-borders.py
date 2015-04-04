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

  # reading the image into a list of pixels
  pixel_list = []
  lines = image.readlines()
  for i in range(0, len(lines)):
    values_in_this_line = lines[i].split()
    for pixel in values_in_this_line:
      pixel_list.append(int(pixel))
  image.close()

  # and converting this list into a matrix
  matrix = []
  for i in range(0, n_lines):
    pixel_line = []
    for j in range(0, n_columns):
      pos = i*n_columns + j
      pixel_line.append(pixel_list[pos])
    matrix.append(pixel_line)

  # cloning this matrix
  matrix_out = matrix
  mw = int(mask/2)

  # to produce the output matrix (ignoring border)
  for i in range(0+mw, n_lines-mw):
    for j in range(0+mw, n_columns-mw):
      mask_of_pixels = []
      for x in range(i-mw, i+mw+1):
        for y in range(j-mw, j+mw+1):
          mask_of_pixels.append(matrix[x][y])
      mask_of_pixels.sort()
      median = int(len(mask_of_pixels)/2)
      matrix_out[i][j] = mask_of_pixels[median]

  # creating the final image through the output matrix
  clean_image = open(name + "_without_salt_pepper.pgm", "w")
  clean_image.write("P2\n")
  clean_image.write("# created by Davi K. Uezono - RA 097464\n")
  clean_image.write(size_string)
  clean_image.write(depth_string)

  for i in range(0, n_lines):
    for j in range(0, n_columns):
      clean_image.write(str(matrix_out[i][j]) + " ")
    clean_image.write("\n")
  clean_image.close()
