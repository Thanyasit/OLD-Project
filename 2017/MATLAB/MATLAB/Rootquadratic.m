%Find root of quadratic
a = input('Please Enter Value x^2 = ');
b = input('Please Enter Value x = ');
c = input('Please Enter Value c = ');
d = b^2-(4*a*c);
p = [a b c];
if d<0
    fprintf('The Equation has no real root')
elseif d==0
    fprintf('The Equation has one root')
elseif d>0
    fprintf('The Equation has two root')
end
root = roots(p)
