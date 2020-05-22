function [nImg] = filtroWiener(img, neight, ruidoPadrao) 
  myImg = double(img);
  
  media = colfilt(myImg, [neight neight], 'sliding', @mean); #pego a media
  desvioPadrao = colfilt(myImg, [neight neight], 'sliding', @var); #pego o desvio padrao
  
  nImg = media + ((desvioPadrao - ruidoPadrao)./desvioPadrao) .* (img - media);
  
  nImg = uint8(nImg);
  
endfunction