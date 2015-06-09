#!/usr/bin/python
# -*- coding: utf-8 -*-
from re import match
from os import system

name = raw_input("Enter the movie filename (WITH file extension): ")

# validate the movie filename (should not have any spaces or special chars)
while match("^[A-Za-z0-9-_]+.mp4$", name):
#while !match("^((?!\s).)*(.mp4)$", name):
  print "Your movie does not have a valid filename.\n"
  name = raw_input("Please, enter a valid movie filename (WITH file extension): ")

# validate the movie timelenght (should not have more than 30 seconds)


# build and execute the command 
cmd = "ffmpeg -i " . name . " -r 25 -f image2 output-%3d.jpeg"
system(cmd)