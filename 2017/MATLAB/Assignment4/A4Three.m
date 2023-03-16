a=input('Numbers of students : ');
for i=1:a
    fprintf('Please input score of student%d.\n',i);
    b=input('Test1 : ');
    c=input('Test2 : ');
    d=input('Test3 : ');
    a1(i)=(b*30/100+c*30/100+d*40/100);
end
t=['A' 'B' 'C' 'D' 'F'];
y=0;
for i=1:a 
   if(a1(i)<50)
       y=5;
   elseif(a1(i)>=50)&&(a1(i)<60)
       y=4;
   elseif(a1(i)>=60)&&(a1(i)<70)
       y=3;
   elseif(a1(i)>=70)&&(a1(i)<80)
       y=2;
   elseif(a1(i)>=80)
       y=1;
   end
   fprintf('Average score of Student%d is %2.1f, Grade %c\n',i,a1(i),t(y));
end