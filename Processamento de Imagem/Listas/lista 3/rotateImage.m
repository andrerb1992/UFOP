function newImage = rotateImage (img, ang)
  newImage = zeros(size(img));
  
  midx=ceil(((size(img,1)+1)/2));
  midy=ceil(((size(img,2)+1)/2));
  
  [I, J] = meshgrid(1:size(img, 1), 1:size(img, 2));
  
  Coord = [I(:)'; J(:)'; ones(1, prod(size(img)))];
  
  R = [cosd(ang)    -sind(ang)    0;
      sind(ang)     cosd(ang)     0;
       0            0             1];
       
  T1 = [1 0 -midx; 0 1 -midy; 0 0 1];
  T2 = [1 0 midx; 0 1 midy; 0 0 1];
  
  M = T2 * R * T1;
  
  newCoord = M * Coord;
  
  X = reshape(newCoord(1,:), size(img, 1), size(img, 2));
  Y = reshape(newCoord(2,:), size(img, 1), size(img, 2));
  newImage = interp2(img, X, Y);
endfunction