%exchange m
B=0;
B1=0;
B5=0;
B10=0;
B20=0;
B50=0;
B100=0;
B500=0;
B = input('Please input money = ');
while(B~=0)
if B>=500
    B=B-500;
    B500=B500+1;
elseif B>=100
    B=B-100;
    B100=B100+1;
elseif B>=50
    B=B-50;
    B50=B50+1;
elseif B>=20
    B=B-20;
    B20=B20+1;
elseif B>=10
    B=B-10;
    B10=B10+1;
elseif B>=5
    B=B-5;
    B5=B5+1;
elseif B>=1;
    B=B-1;
    B1=B1+1;
end
end
fid = fopen('Output.dat','w');
fprintf(fid,'500 bank note = %d\n',B500);
fprintf(fid,'100 bank note = %d\n',B100);
fprintf(fid,'50 bath bank note = %d\n',B50);
fprintf(fid,'20 bath bank note = %d\n',B20);
fprintf(fid,'10 bath bank note = %d\n',B10);
fprintf(fid,'5 bath coin = %d\n',B5);
fprintf(fid,'1 bath coin = %d\n',B1);
fclose(fid);


