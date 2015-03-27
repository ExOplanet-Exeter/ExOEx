clear all

angle = 90;
range = 10;

theta = angle*(pi/180);


load ~/Desktop/ExOEx/Output/polarisation.dat;
pol = polarisation;

x = pol(:,1);
y = pol(:,2);
z = pol(:,3);

pI = pol(:,4);
pU = pol(:,5);
pV = pol(:,6);
pQ = pol(:,7);

see = pol(:,8) * 0;


hor=0;
vir=0;
for i = 1:1000
	alpha = pol(i,8)*(180/pi);
	if (((angle-alpha)<=range) && (alpha-angle)<=range)
		see(i)=1;
		if (pU(i)>0.0)
			hor++;
		else
			vir++;
		endif
	endif
endfor

#x = (x.*cos(theta)) + (z.*sin(theta));
#z = (-x.*sin(theta)) + (z.*cos(theta));

total = 0;
for i = 1:1000
	if (see(i)==1)
		total++;
	endif
endfor

sx = [1:1:total];
sx = sx * 0;
sy = sx * 0;
sz = sx * 0;
alpha = sx * 0;

n = 1;
for i = 1:1000
	if (see(i)==1)
		sx(n) = x(i);
		sy(n) = y(i);
		sz(n) = z(i);
		alpha(n) = pol(i,5);
		beta(n) = pol(i,6);
		n++;
	endif
endfor


hor
vir
frac_vir_polarised = (hor/(hor+vir))*100

scatter3(sx,sy,sz,[],alpha,'filled');

axis([-1 1 -1 1 -1 1])