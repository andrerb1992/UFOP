function [nImg] = notchFilter(img, u0, v0, r, n)
  fimg = fft2(img);
  fimg = fftshift(fimg);
  
  [M, N] = size(img);
  
  for u = 1 : M
    for v = 1 : N
      D1 = sqrt((u - M/2 - u0).^2 + (v - N/2 - v0).^2);    
      D2 = sqrt((u - M/2 + u0).^2 + (v - N/2 + v0).^2);
      
      mask(u, v) = (1 / (1 + ((r.^2)/(D1 * D2)).^n));
    endfor
  endfor
  
  nImg = fimg .* mask;
  nImg = abs(ifft2(nImg));
endfunction
