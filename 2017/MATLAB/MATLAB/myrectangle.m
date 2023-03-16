function myrectangle(b,h,request)
area=b*h;
circ=2*(b+h);
lx=(b*h^3)/12;
ly=(b*h^3)/12;
centX=b/2;
centY=h/2;
if(strcmp(request,'area')==1);
    disp(area)
elseif(strcmp(request,'circ')==1);
    disp(circ)
elseif(strcmp(request,'lx')==1);
    disp(lx)
elseif(strcmp(request,'ly')==1);
    disp(ly)
elseif(strcmp(request,'centX')==1);
    disp(centX)
elseif(strcmp(request,'centY')==1);
    disp(centY)
end
axis([-0.5 b*2 -0.5 h*2]);
pos=[0 0 b h];
rectangle('Position',pos,'FaceColor',[0 .5 .5]);
s1=num2str(area);
s2='area = ';
s=strcat(s2,s1);
text(0,h/6*12,s);
s1=num2str(circ);
s2='circ = ';
s=strcat(s2,s1);
text(0,h/6*11,s);
s1=num2str(centX);
s2='centX = ';
s=strcat(s2,s1);
text(0,h/6*10,s);
s1=num2str(centY);
s2='centY = ';
s=strcat(s2,s1);
text(0,h/6*9,s);
s1=num2str(lx);
s2='lx = ';
s=strcat(s2,s1);
text(0,h/6*8,s);
s1=num2str(ly);
s2='ly = ';
s=strcat(s2,s1);
text(0,h/6*7,s);
end



