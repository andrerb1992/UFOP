function [nImg] = butterworthMask(img, raio, n, width)
  fimg = fft2(img);
  fimg = fftshift(fimg);
  [M, N] = size(img);
  [x, y] = gridFourier(M, N);
  z = sqrt(x.^2 + y.^2);
  mask = 1 ./ (1 + ( z*width ./ (z.^2 - raio^2) ).^(2*n));
  nimg = fimg .* mask;
  nImg = abs(ifft2(nimg));
endfunction