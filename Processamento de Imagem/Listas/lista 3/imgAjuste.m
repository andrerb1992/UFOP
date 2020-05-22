function newImage = imgAjuste(img)
  soma = 255;
  newImage = imadjust(img, [(80/soma) (150/soma)], [(50/soma) (250/soma)]);
endfunction