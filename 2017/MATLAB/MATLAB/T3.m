
hold on
ezplot('(x/7)^2+(y/3)^2-1=0',[-8 8 -3*sqrt(33)/7 6-4*sqrt(33)/7]);
ezplot('abs(x/2)-((3*sqrt(33)-7)/112)*x^2-3+sqrt(1-(abs(abs(x)-2)-1)^2)');
ezplot('y=9-8*abs(x)',[-1 -0.75 1 3]);
ezplot('y=9-8*abs(x)',[1 0.75 1 3]);
ezplot('y=3*abs(x)+0.75',[-2 2 0 3]);
xlim( [-7.25 7.25]);
ylim([-5 5]);
colormap([0 0 0]);