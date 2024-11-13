w=6.28;
m=@(z) (1-z*z)*0.5;
wp=@(m) m(z)*w;
y =@(t,z) 1-exp(-z*w.*t).*((z/m(z)).*sin(wp(m).*t)+cos(wp(m).*t));

z_values=[0.1,0.3,0.45,0.8]
t_values=linspace(0,5,100);

figure;
hold on;

z=z_values(1);
y_values=y(t_values,z);
plot(t_values,y_values,"-r","DisplayName",['z = ' num2str(z)]);

z=z_values(2);
y_values=y(t_values,z);
plot(t_values,y_values,"-g","DisplayName",['z = ' num2str(z)]);

z=z_values(3);
y_values=y(t_values,z);
plot(t_values,y_values,"-b","DisplayName",['z = ' num2str(z)]);

z=z_values(4);
y_values=y(t_values,z);
plot(t_values,y_values,'color', [0.5, 0.2, 0.8],"DisplayName",['z = ' num2str(z)]);

xlabel('t');
ylabel('y');
title('Reponse indicielle d''un second ordre');
legend('show');
grid on;

hold off;