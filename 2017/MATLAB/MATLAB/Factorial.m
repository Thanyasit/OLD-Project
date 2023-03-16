function Factorial(x)
if x>=0 && x==ceil(x)
    n = x*2-1;
    s = 1;  
    for t = x:n
        s=s*x;
        x=x-1;
    end
    fprintf('Factorial = %d\n',s);
else
    fprintf('Please Enter Positive Integer Value\n');
end