eq1=@(x) (x.*exp(-x.*x));
eq2=@(x) (0.1./(x.*x));

x_values_1=linspace(-2.5,-0.01,100);
x_values_2=linspace(0.01,2.5,100);

y_values_1_1=eq1(x_values_1);
y_values_2_1=eq2(x_values_1);
y_values_1_2=eq1(x_values_2);
y_values_2_2=eq2(x_values_2);

plot(x_values_1,y_values_1_1,"-r",'DisplayName',"xexp(-x²)");
hold on;
plot(x_values_2,y_values_1_2,"-r",'DisplayName',"xexp(-x²)");
hold on;
plot(x_values_1,y_values_2_1,"-b",'DisplayName',"0.1/x²");
hold on;
plot(x_values_2,y_values_2_2,"-b",'DisplayName',"0.1/x²");

xlabel('x');
ylabel('y');
ylim([-1, 1]);
hold off;