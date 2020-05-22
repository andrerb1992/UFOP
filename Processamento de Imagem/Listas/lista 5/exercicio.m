
img = imread("C./lenna_periodico2.png");
#imshow(img);

# 01) Eliminar o ruído produzido pelo ruído periódico. 
# Usar os filtros média, mediana e filtragem no domínio da frequência.
nImg = medfilt2(img, [5 5]); #mediana
#figure; imshow(nImg);
filter = fspecial('average', [3 3]); 
nImg = imfilter(img, filter); #media
#figure; imshow(nImg);
nImg = filtragemDominio(img, 15);
#figure; imshow(nImg);

imgA = imread("./letra_A0.png");
imgB = imread("./letra_B.png");
imgB2 = imread("./letra_Bt.png");
imgV = imread("./letra_V.png");

# 02) Rotacionar a imagem 
imgA1 = imrotate(imgA, 45, 'bilinear', 'crop');
imgA2 = imrotate(imgA, 90, 'bilinear', 'crop');
imgA3 = imrotate(imgA, 135, 'bilinear', 'crop');
imgA4 = imrotate(imgA, 180, 'bilinear', 'crop');

# a)
imgA0 = fft2(imgA);
imgAF1 = fft2(imgA1);
imgAF2 = fft2(imgA2);
imgAF3 = fft2(imgA3);
imgAF4 = fft2(imgA4);

hist_inter(abs(imgA0), abs(imgAF1))
hist_inter(abs(imgA0), abs(imgAF2))
hist_inter(abs(imgA0), abs(imgAF3))
hist_inter(abs(imgA0), abs(imgAF4))

#b) 
imgB0 = fft2(imgB);
imgV0 = fft2(imgV);

hist_inter(abs(imgA0), abs(imgB))
hist_inter(abs(imgA0), abs(imgV))

#c) 
imgBt = fft2(imgB2);
hist_inter(abs(imgB0), abs(imgBt))

#d) 
imgPA = polartrans(imgA, 128, 128);
imgPA1 = polartrans(imgA1, 128, 128);
imgPA2 = polartrans(imgA2, 128, 128);
imgPA3 = polartrans(imgA3, 128, 128);
imgPA4 = polartrans(imgA4, 128, 128);
imgPB = polartrans(imgB, 128, 128);
imgPV = polartrans(imgV, 128, 128);

imgPA = fft2(imgPA);
imgPA1 = fft2(imgPA1);
imgPA2 = fft2(imgPA2);
imgPA3 = fft2(imgPA3);
imgPA4 = fft2(imgPA4);
imgPB = fft2(imgPB);
imgPV = fft2(imgPV);

hist_inter(abs(imgA), abs(imgPA))
hist_inter(abs(imgA1), abs(imgPA1))
hist_inter(abs(imgA2), abs(imgPA2))
hist_inter(abs(imgA3), abs(imgPA3))
hist_inter(abs(imgA4), abs(imgPA4))
hist_inter(abs(imgB), abs(imgPB))
hist_inter(abs(imgV), abs(imgPV))
