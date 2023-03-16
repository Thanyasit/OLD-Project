syms x y
eq1 = ((x/7)^2*sqrt(abs(abs(x)-3)/(abs(x)-3))+(y/3)^2*sqrt(abs(y+3/7*sqrt(33))/(y+3/7*sqrt(33)))-1);
eq2 = (abs(x/2)-((3*sqrt(33)-7)/112)*x^2-3+sqrt(1-(abs(abs(x)-2)-1)^2)-y);
eq3 = (9*sqrt(abs((abs(x)-1)*(abs(x)-.75))/((1-abs(x))*(abs(x)-.75)))-8*abs(x)-y);
eq4 = (3*abs(x)+.75*sqrt(abs((abs(x)-.75)*(abs(x)-.5))/((.75-abs(x))*(abs(x)-.5)))-y);
eq5 = (2.25*sqrt(abs((x-.5)*(x+.5))/((.5-x)*(.5+x)))-y);
eq6 = (6*sqrt(10)/7+(1.5-.5*abs(x))*sqrt(abs(abs(x)-1)/(abs(x)-1))-(6*sqrt(10)/14)*sqrt(4-(abs(x)-1)^2)-y);
axes('Xlim', [-7.25 7.25], 'Ylim', [-5 5]); % ล็อกกราฟตามตำแหน่งที่ต้องการ
hold on %ให้กราฟขึ้นทับกันได้โดยไม่ลบกราฟที่ขึ้นก่อน
%แสดงกราฟกำหนเช่วง X,Y
ezplot(eq1,[-8 8 -3*sqrt(33)/7 6-4*sqrt(33)/7]);
ezplot(eq2,[-4 4]);
ezplot(eq3,[-1 -0.75 -5 5]);
ezplot(eq3,[0.75 1 -5 5]);
ezplot(eq4,[-0.75 0.75 2.25 5]);
ezplot(eq5,[-0.5 0.5 -5 5]);
ezplot(eq6,[-3 -1 -5 5]);
ezplot(eq6,[1 3 -5 5]);
colormap([0 0 1]) %เลือกสี 
title('Batman'); %กำหนดชื่อกราฟ
xlabel(''); %กำหนดชื่อ แกน X
ylabel(''); % กำหนดชื่อแกน Y
hold off ปิดการเพิ่มกราฟ