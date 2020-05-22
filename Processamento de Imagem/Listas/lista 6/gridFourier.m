function [x, y] = gridFourier(row, col)
  u = 0:row-1;
  v = 0:col-1;
  
  u = u-floor(row/2);
  v = v-floor(col/2);
  
  [x, y] = meshgrid(u, v);
endfunction