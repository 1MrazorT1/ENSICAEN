p1=[1 -2 -1 2];
p2=[-1 4 -2];
p3=[1 0 -1];

dp1=polyder(p1);
dp2=polyder(p2);
dp3=polyder(p3);

p12=conv(p1,p2);

dp=setdiff(p1,p3);
r=roots(dp);
disp(r);

[q,r]=deconv(p1,p3);
disp([q,r]);

x=[0 1 2 3];
v=polyval(p1,x);

