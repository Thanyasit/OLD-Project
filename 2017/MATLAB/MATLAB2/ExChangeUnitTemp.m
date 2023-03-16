function ExChangeUnitTemp(x)

y1 = x + 273.15; %kelvin
y2 = 1.8*x+32; %Farenhine
y3 = 1.8*y1; % Rakine
x1 = 'ChangeUnitTemp'
z =[y1;y2;y3];
fprintf('\nT(K)= %i ',y1);
%disp(y1)
fprintf('\nT(F)= %i ',y2) ;
%disp(y2)
fprintf('\nT(R)= %i ',y3);
fprintf('\n String= %s \n',x1);
fprintf('\n A = %i  B = %i \n',y1,y2);
fprintf('\n A = %5.0f  B = %5.0f  C = %5.0f \n',z);
%disp(y3)
end
