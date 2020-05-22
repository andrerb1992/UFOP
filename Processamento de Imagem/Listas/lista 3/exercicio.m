img = imread('C:\Users\Aluno\Downloads\Lista 3\grain.png');

# 1) Rotacione a imagem
#imgRotated = rotateImage(img, 45);
#imshow(imgRotated, []);

# 2) Arrumar intensidade
imgAdjusted = imgAjuste(img);
I = imhist(imgAdjusted);
plot(I);

# 3) 