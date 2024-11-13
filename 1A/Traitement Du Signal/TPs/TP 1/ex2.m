eq1=@(x) (2*x-4);
eq2=@(x) (-x+5);

x_values=linspace(-5,5,100);
y1_values=eq1(x_values);
y2_values=eq2(x_values);

plot(x_values,y1_values,'-r');
hold on;
plot(x_values,y2_values,'-b');

xlabel('x');
ylabel('y');

intersection_x=fzero(@(x) eq1(x)-eq2(x),0);
intersection_y=eq1(intersection_x);

plot(intersection_x,intersection_y,'-g');

hold off;