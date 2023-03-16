f2 = fopen('test01.dat','r');
A=fscanf(f2,'%c',[3]);
%[A,count] = fscanf(f2,'%f',[1 10]);
st = fclose(f2);