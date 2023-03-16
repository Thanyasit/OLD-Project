% example
x=linspace(1,2*pi,10);
y = sin(x);
%open file
fid = fopen('test01.dat','W');
%count = fprintf(fid,'%8.4f%8.4f\n',y);
count = fprintf(fid,'OMG');
fs = fclose(fid);