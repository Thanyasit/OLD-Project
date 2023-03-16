function [y,x] = myex2(N,M)
%myodds.m
y = M
x = N
for i = 1:N
    y = y + (2*i-1);
 %   disp(y);
end