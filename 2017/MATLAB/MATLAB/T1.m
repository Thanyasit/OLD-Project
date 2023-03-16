syms x y

axes('Xlim', [-7.25 7.25], 'Ylim', [-5 5]);
hold on
eq1 = ((x/7)^2*sqrt(abs(abs(x)-3)/(abs(x)-3))+(y/3)^2*sqrt(abs(y+3/7*sqrt(33))/(y+3/7*sqrt(33)))-1);
ezplot(eq1,[-8 8 -3*sqrt(33)/7 6-4*sqrt(33)/7]);
%eq2 = (abs(x./2)-((3.*sqrt(33)-7)./112).*x.^2-3+sqrt(1-(abs(abs(x)-2)-1).^2)-y);
%ezplot(eq2,[-4 4]);
colormap([0 1 0]);