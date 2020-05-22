% questao 1
>> A=[1:7;9:-2:-3;2.^[2:8]]
A =

     1     2     3     4     5     6     7
     9     7     5     3     1    -1    -3
     4     8    16    32    64   128   256


%questao 2a

>> colvec=ones(3,1)
colvec =

   1
   1
   1

>> rowvec=[1:5]
rowvec =

   1   2   3   4   5

>> x=colvec*rowvec
x =

   1   2   3   4   5
   1   2   3   4   5
   1   2   3   4   5

   

%questao 2b 
>> colvec=[0:1:4]'
colvec =

   0
   1
   2
   3
   4

>> linha=ones(1,3)
linha =

   1   1   1

>> x=colvec * linha
x =

   0   0   0
   1   1   1
   2   2   2
   3   3   3
   4   4   4
   
% questa 3a
>> t=[1 2 3 4 5]
t =

   1   2   3   4   5
>> a= log (2 + (t) +((t).^2))
a =

   1.3863   2.0794   2.6391   3.0910   3.4657

% questa 3b
>> t
t =

   1   2   3   4   5

>> b=exp(t.*(1 + cos(3 * t)))
b =

      1.0101     50.4176      1.3055   1596.2555      3.3253



% questa 3c

>> c= cos(t.^2) + sin(t.^2)
c =

   1.38177  -1.41045  -0.49901  -1.24556   0.85885
   
% Questao 4 

>> a = plot(sin(1./[0.01:0.01:0.1]))
a = -1.1780


% Questao 5a 

>> a=[7.5 8.0 9.0; 6.7 7.7 5.4; 8.0 9.2 7.4; 6.6 6.6 6.6; 5.0 8.0 7.0]

a =

    7.5000    8.0000    9.0000
    6.7000    7.7000    5.4000
    8.0000    9.2000    7.4000
    6.6000    6.6000    6.6000
    5.0000    8.0000    7.0000

>> n = ((a( :, 3)*2)+(a( :,2)+(a( :,1))))/3

n =

   11.1667
    8.4000
   10.6667
    8.8000
    9.0000

% Questao 5b

>> a=[7.5 8.0 9.0; 6.7 7.7 5.4; 8.0 9.2 7.4; 6.6 6.6 6.6; 5.0 8.0 7.0]

a =

    7.5000    8.0000    9.0000
    6.7000    7.7000    5.4000
    8.0000    9.2000    7.4000
    6.6000    6.6000    6.6000
    5.0000    8.0000    7.0000

>> n = ((a( 3,:)*2)+(a(2,:)+(a( 1,:))))/5

n =

    6.0400    6.8200    5.8400

>> mean((a( 3,:)*2)+(a(2,:)+(a( 1,:))))/5

ans =

    6.2333

% Questao 6
y=[];
for x=-1:0.1:3
	y = [y x.^2 + 3x +2];
end
plot(y, 'r');

x = [-1:0.1:3];
plot(x.^2+3*x+2,'r');


% Questao 7
	function [m,t] = Medias(vet)
	m = prod(vet)^(1/length(vet));
	t = mean(vet);
end




% questao 8
>> a

a =

     2     5     1     6     2     3     4
 
>> t=(mod(a,2)) + 3

t =

     3     4     4     3     3     4     3

>> 



% Questao 9

>> m=rand(3,2)

m =

    0.8147    0.9134
    0.9058    0.6324
    0.1270    0.0975

>> min(min(m))

ans =

    0.0975

>> max(max(m))

ans =

    0.9134

>> 


