function [nImg] = gaussianNoise(img, raio, width)
  fimg = fft2(img);
  fimg = fftshift(fimg);
  [M, N] = size(img);
  [x, y] = gridFourier(M, N);
  z = sqrt(x.^2 + y.^2);
  
  #expoente do E
  up = ((z.^2 - raio.^2)./(z .* width)).^2;
  # multiplica o expoente por -1 e salva em E
  e = exp(up .* (-1));
  # faz o 1 - e;
  mask = 1 - e;
  
  nimg = fimg .* mask;
  nImg = abs(ifft2(nimg));
endfunction