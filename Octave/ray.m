clear all
load ~/Desktop/ExOEx/Output/rayleighTest.dat
x = rayleighTest(:,1);
y = rayleighTest(:,2);
scatter(x,y,[],y)