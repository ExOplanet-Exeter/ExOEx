clear all
load ~/Desktop/ExOEx/Output/position.dat
x = position(:,1);
y = position(:,2);
z = position(:,3);

xS = x.*x;
yS = y.*y;
zS = z.*z;

rho = sqrt(xS + yS + zS);

scatter3(x,y,z,[],rho);

axis([-1 1 -1 1 -1 1],"equal")