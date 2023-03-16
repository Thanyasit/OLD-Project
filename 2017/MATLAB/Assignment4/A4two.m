a=input('Input N = ');
x=a-1;
b=0;
c=0;
y=x+a+1;
for i= 1:x+a;
    if(c>=a)
        b=b-1;
    else
        b=i;
    end
    for i=1:x+a;
        if(i==b)
            fprintf('%d',b);
        else
            if(i==(y-b))
                fprintf('%d',b);
            else
                fprintf(' ');
            end
        end
    end
    fprintf('\n');
    c=c+1;
end
