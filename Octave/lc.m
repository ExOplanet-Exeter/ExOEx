clear all
load ~/Desktop/ExOEx/Arc/data/lightcurve.dat
x = lightcurve(:,1);
y = lightcurve(:,2);
plot(x,y,'b.')