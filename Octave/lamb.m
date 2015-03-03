clear;

theta = linspace(0,pi,100);
phi = (sin(theta)+(pi-theta).*cos(theta))/pi;
plot(theta*(180/pi),phi,'r-','linewidth',2);

hold on;

clear all
load ~/Desktop/ExOEx/Output/lambertian.dat
x = lambertian(:,1);
y = lambertian(:,2);

plot(x,y,'b.');
hold off;