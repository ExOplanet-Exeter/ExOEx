clear all

load ~/Desktop/ExOEx/Output/polTest.dat
angle = polTest(:,1);
total = polTest(:,2);
pI = polTest(:,3);
pQ = polTest(:,4);
pU = polTest(:,5);
pV = polTest(:,6);

hold off
plot(angle,total,'k','linewidth',3);
hold on
plot(angle,pI,'g','linewidth',3);
plot(angle,pQ,'r','linewidth',3);
plot(angle,pU,'b','linewidth',3)