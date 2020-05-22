function [nImg] = filtragemDominio(img, range)
  fImg = img;
  
  fImg = fft2(fImg);
  fImg = fftshift(fImg);
  fImg(88-range:88+range, 88-range:88+range) = 0;
  fImg(170-range:170+range, 170-range:170+range) = 0;
  fImg = ifft2(fImg);
  
  nImg = uint8(abs(fImg));
  
endfunction
  