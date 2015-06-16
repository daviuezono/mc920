#!/usr/bin/python
# -*- coding: utf-8 -*-
import re
import subprocess
from decimal import Decimal
from os import system
from sys import exit

name = raw_input("Enter the movie filename (WITH file extension): ")

# validate the movie filename (should not have any spaces or special chars).
while not re.match("^[A-Za-z0-9-_]+.mp4$", name):
  print "\nYour movie does not have a valid filename.\nValid characters are A-Z, a-z, 0-9, hyfens and underscore."
  name = raw_input("Please, enter a valid movie filename (WITH file extension): ")

original_file = 1
# validate the movie timelenght (should not have more than 30 seconds).
cmd_lenght = "ffprobe -loglevel quiet -show_format " + name + " | grep 'duration'"
duration = subprocess.check_output(cmd_lenght, shell=True)
length = Decimal(duration.strip().strip("duration="))

if length > 30:
  # if it is not valid, offer to crop the videofile to its first 30 seconds.
  print "\nYour movie seems to have more than 30 seconds.\nIt might not work properly this way, so, we're offering you to crop your video automatically."
  answer = raw_input("Do you want to crop your movie to the first 30 seconds? [Y/N]: ")
  while answer not in ['y', 'Y', 'n', 'N']:
    print "\nINVALID OPTION"
    answer = raw_input("Do you want to crop your movie to the first 30 seconds? [Y/N]: ")
  if answer == 'y' or answer == 'Y':
    cmd_crop = "ffmpeg -loglevel quiet -i " + name + " -t 30 intermediate.mp4"
    system(cmd_crop)
    original_file = 0
  if answer == 'n' or answer == 'N':
    print "ERROR: your movie has more than 30 seconds.\n"
    exit(0)

# re-scale the video size to fit 640px of width.
if original_file:
  cmd_resize = "ffmpeg -loglevel quiet -i " + name + " -vf scale=640:-1 output.mp4"
else:
  cmd_resize = "ffmpeg -loglevel quiet -i intermediate.mp4 -vf scale=640:-1 output.mp4"
system(cmd_resize)

# build and execute the command
cmd_img = "ffmpeg -loglevel quiet -i output.mp4 -r 30 -f image2 output-%3d.jpg"
system(cmd_img)

if not original_file:
  system("rm intermediate.mp4")
system("rm output.mp4")

cmd_n_images = "ls -l | grep '.jpg' | wc -l"
n_images = subprocess.check_output(cmd_n_images, shell=True)
number = str(n_images.strip())

print "FINISH: Your input movie file has been successfully converted to " + number + " images.\n"
