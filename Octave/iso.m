clear all
load ~/Desktop/ExOEx/Output/isotropicTest.dat
x = isotropicTest(:,1);
y = isotropicTest(:,2);

scatter(x,y,[],y)