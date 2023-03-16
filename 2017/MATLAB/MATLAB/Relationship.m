%Find Relationship Speed and Time
a=1;
for t = -5:50;
    if t>=0 && t<=10
    y(a)= (12*t^2)-6*t;
    elseif t>10 && t<=20
    y(a) = 1200-6*t;
    elseif t>20 && t<=30
    y(a) = 54*t+3*(t-20)^2;
    elseif t>30
    y(a) = 1920*exp(-0.2*(t-30));
    else
    y(a) = 0;
    end
    a = a+1;    
end
t = -5:50;
plot(t,y,'--r');
