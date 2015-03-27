clear all
load ~/Desktop/ExOEx/Output/view.dat;
x = view(:,1);
y = view(:,2);

xS = 0.0;
yS = 0.0;

rho = sqrt(xS + yS);

scatter(x,y,[],rho);

axis([-1 1 -1 1],"equal")