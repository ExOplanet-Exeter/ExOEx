clear all

load ~/Desktop/ExOEx/Output/lightcurve.dat
angle = lightcurve(:,1);
total = lightcurve(:,2);
pI = lightcurve(:,3);
pQ = lightcurve(:,4);
pU = lightcurve(:,5);
pV = lightcurve(:,6);

hold off
plot(angle,total,'k','linewidth',3);
hold on
plot(angle,pI,'g','linewidth',3);
plot(angle,pQ,'r','linewidth',3);
plot(angle,pU,'b','linewidth',3)