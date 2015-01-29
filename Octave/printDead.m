clear all
load ~/Desktop/ExOEx/Arc/data/deadPosition.dat
x = deadPosition(:,1);
y = deadPosition(:,2);
z = deadPosition(:,3);
scatter3(x,y,z);
axis([-1,1,-1,1,-1,1])
