
pkg load image

img = imread('./lenna.png');
#imshow(img);
# 01) Remover o ruído com o Filtro Notch
#nImg = notchFilter(img, 40, 40, 40, 30);
#imshow(nImg, []);

# 02) Filtro Ideal, Filtro Butterworth e Filtro Gaussian
#nImg = filtroIdeal(img, 60, 25);
#imshow(nImg, []);
#nImg = butterworthMask (img, 60, 30, 20);
#figure; #imshow(nImg, []);
#nImg = gaussianNoise(img, 60, 40);
#imshow(nImg, []);

# 03) Filtro de Wiener
img = imread('./ruido.png');
nImg = filtroWiener(img, 5, 200);
imshow(nImg, []);
