t=0;
s=0;
A=2;
while A~=0
A = input('Please input route = ');
t=t+1;
if(t==1)
    A1=A;
elseif(t==2)
    A2=A;
    s=s+z(A1,A2);
    
elseif(A==0)
else
    A1=A2;
    A2=A;
    s=s+z(A1,A2);
end
end
disp(s)
                
    

