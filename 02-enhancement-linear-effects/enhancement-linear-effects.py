#!/usr/bin/python
# -*- coding: utf-8 -*-

name = raw_input("Please select one of these images: coins, columns or dragon.\n")
while name not in ["coins", "columns", "dragon"]:
  name = raw_input("ERROR! Please select one of these images: coins, columns or dragon.\n")

effect = raw_input("Please select one of these linear effects: threshold or negative.\n")
while effect not in ["threshold", "negative"]:
  effect = raw_input("ERROR! Please select one of these linear effects: threshold or negative.\n")

image = open(name + ".pgm", "r")
if image.readline() == "P2\n":
  image_out = open(name + "_" + effect + ".pgm", "w")
  image_out.write("P2\n")

  image.readline() # ignore comment line from PGM format
  image_out.write("# created by Davi K. Uezono - RA 097464\n")

  size_string = image.readline()
  size = size_string.split()
  image_out.write(size_string)
  
  depth_string = image.readline()
  depth = depth_string.split()
  if effect == "threshold":
    depth_out = "2\n"
  else:
    depth_out = depth_string
  image_out.write(depth_out)

  lines = image.readlines()
  for i in range(0, len(lines)):
    values_in_this_line = lines[i].split()
    for pixel in values_in_this_line:
      int_pixel = int(pixel)
      int_depth = int(depth[0])

      if (effect == "threshold"):
        if (int_pixel < int_depth/2):
          image_out.write("0\n")
        else:
          image_out.write("1\n")

      elif (effect == "negative"):
        pixel_out = (str) (int_depth - int_pixel) + "\n"
        image_out.write(pixel_out)

  image.close()
  image_out.close()
