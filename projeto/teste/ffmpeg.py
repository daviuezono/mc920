#!/usr/bin/python
# -*- coding: utf-8 -*-
import re
import subprocess
from decimal import Decimal
from os import system

name = raw_input("Enter the movie filename (WITH file extension): ")

# validate the movie filename (should not have any spaces or special chars).
while not re.match("^[A-Za-z0-9-_]+.mp4$", name):
  print "Your movie does not have a valid filename.\n"
  name = raw_input("Please, enter a valid movie filename (WITH file extension): ")

original_file = 1
# validate the movie timelenght (should not have more than 30 seconds).
# http://www.codingwithcody.com/2012/04/get-video-duration-with-ffmpeg-and-python/
# http://stackoverflow.com/questions/28884159/using-python-script-to-cut-long-videos-into-chunks-in-ffmpeg
#cmd_lenght = "ffprobe -show_format " + name + " | grep \"duration\""
#system(cmd_lenght)

# if it is not valid, offer to crop the videofile to its first 30 seconds.
cmd_crop = "ffmpeg -i " + name + " -t 30 intermediate.mp4"
system(cmd_crop)
original_file = 0

# build and execute the command
if original_file:
  cmd_img = "ffmpeg -i " + name + " -r 25 -f image2 output-%3d.pgm"
else:
  cmd_img = "ffmpeg -i intermediate.mp4 -r 25 -f image2 output-%3d.pgm"
system(cmd_img)

if not original_file:
  system("rm intermediate.mp4")
