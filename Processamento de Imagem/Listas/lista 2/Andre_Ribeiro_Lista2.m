%exe1

img=imread('C:/Users/Aluno/lenna_rgb512.jpg');
imshow(img);
img = double(img);
for i = 1:10
  imgray = 0.299 * img(:,:,1) + 0.587*img(:,:,2) + 0.114*img(:,:,3);
  img(:,:,1) = imgray; 
  img(:,:,2) = imgray;
  img(:,:,3) = imgray;
end

imshow(uint8 (img));
imwrite(img, 'lenna_gray.jng');


%exe2
function nimg = wxe2(img,ang)
  [lin col,~]=size(img);
  linha= (-lin)/2;
  coluna=(-col)/2;
  linha1= (lin)/2;
  coluna1=(col)/2;
  matT=[1 0 linha; 0 1 coluna; 0 0 1];
  matR=[cosd(ang) -sind(ang) 0; sind(ang) cosd(ang) 0; 0 0 1];
  matT2=[1 0 linha1; 0 1 coluna1;0 0 1];
  mat=matT2 * matR * matT;
  for x=1:lin
    for y=1:col 
      p= mat * [x;y;1];
      nx(x,y)=p(1);
      ny(x,y)=p(2);
    end
  end
img = double(img);
 nimg= interp2(img, nx,ny);
 nimg=uint8(nimg);
 imshow(nimg);
%exe3

 function ex3= exe3(img)
  razao_h=floor(length(img(1,:,1))*2);
  razao_v=floor(length(img(:,1,1))*2);
  for k=1:length(img(1,1,:))
    for j=1:razao_h
      for i=1:razao_v
        B(i,j,k) = img(round(i/2),round(j/2),k);
      end
    end
  end
  imshow(B)
  
  size(img)
  size(B)

%exe4
>> img1=imread('C:\Users\Andre\Desktop\pdi\CLOWN.bmp');
>> img=imread('C:\Users\Andre\Desktop\pdi\lenna_rgb512.jpg');
>> k=imadd(img,img1);
>> imshow(k);

%exe5
>> img=imread('C:\Users\Andre\Desktop\pdi\lenna_rgb512.jpg');
>> img = double(img);
>> imshow(uint8 (img));
>> img = fliplr(img);
>> imshow(uint8 (img));
>> img3 = imrotate(img , -180, 'bilinear');
>> imshow(uint8 (img3));