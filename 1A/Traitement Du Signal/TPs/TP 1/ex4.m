run("f4.m");

x_values_1;
x_values_2;

y_values_1=fun4(x_values_1);
y_values_2=fun4(x_values_2);

plot(x_values_1,y_values_1,"-r");
hold on;
plot(x_values_2,y_values_2,"-r");
ylim([-0.7,0.7]);
hold off;

racine=fzero(fun4,1);
disp(racine);
racine2=fzero(fun4,2);
disp(racine2);