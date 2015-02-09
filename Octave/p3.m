clear all
load ~/Desktop/ExOEx/Arc/data/threeDpos.dat
x = threeDpos(:,1);
y = threeDpos(:,2);
z = threeDpos(:,3);
scatter3(x,y,z,'b');
axis([-1,1,-1,1,-1,1])