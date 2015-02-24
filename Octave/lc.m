clear all
load ~/Desktop/ExOEx/Output/lightcurve.dat
x = lightcurve(:,1);
y = lightcurve(:,2);

scatter(x,y,[],x)