r = input('Please input the  distance = ');
h = input('Please input the  Use oil = ');
l = input('Please input the  Use oil = ');
v = (r^2*acos*((r-h)/r)-(r-h)*sqrt(2*r*h-h^2))*l;
fprintf('Oil consumption rate per kilo = %d \n',v);