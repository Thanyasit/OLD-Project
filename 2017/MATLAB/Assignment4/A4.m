a=input('Input rows = ');
i=0;
x=1;
y=a;
for i= 1:a;
    y=y-1;
    for i= 1:y
    fprintf(' ');
    end
    for i= 1:x
    fprintf('*');
    end
    x=x+2;
    fprintf('\n');
end
