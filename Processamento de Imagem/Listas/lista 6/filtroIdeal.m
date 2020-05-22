function [nImg] = filtroIdeal(img, raio, width)
  fimg = fft2(img);
  fimg = fftshift(fimg);
  [M, N] = size(img);
  [x, y] = gridFourier(M, N);
  z = sqrt(x.^2 + y.^2);
  
  mask = z >= (raio - width/2) & z <= (raio + width/2);
  mask = ~mask;
  
  nimg = fimg .* mask;
  #imshow(log(abs(nimg) + 1), []);
  nImg = abs(ifft2(nimg));  
endfunction