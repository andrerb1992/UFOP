img = imread("./util/matches.png");
pkg load image
imgmask = imread("./util/matchMask.png");

# 1) NoiseSum
[nImg, figs] = NoiseSum(img, 50);
#imshow(nImg);

# 2) changeBackGround
newImage = changeBackground(img, imgmask, 20);
#imshow(newImage);

img = imread("./util/mars_moon.png");
# 3) MinimalMeanSquare
function newImage = MinimalMeanSquare(img, tam, ruido)
  img = double(img);
  
  varRuido = ruido;
  
  mediaLocal = colfilt(img, [tam tam], 'sliding', @mean);
  varLocal = colfilt(img, [tam tam], 'sliding', @var);
  
  newImage = (1-(varRuido./varLocal)) .* img + ((varRuido./varLocal).*mediaLocal);
  newImage = uint8(newImage);
endfunction



