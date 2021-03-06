pkg load image

img = imread("./columns.pgm");

# compute the Fourier transform of the image
fimg = fft2(img);
logimg = log2(fimg);

# apply a high-pass filter by...
mags = abs(logimg); # calculating the magnitudes of the frequencies
#imshow(mags);

imwrite(mags, "colums-filtered.pgm");
