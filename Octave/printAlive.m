clear all
load ~/Desktop/ExOEx/Arc/data/position.dat
x = position(:,1);
y = position(:,2);
z = position(:,3);
scatter3(x,y,z);
axis([-1,1,-1,1,-1,1])
