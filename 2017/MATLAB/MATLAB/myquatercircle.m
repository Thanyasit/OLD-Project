function myquatercircle(r,orient,request)
area=(pi*r^2)/4;
circ=(pi*r)/2+2*r;
lx=(pi*r^4)/16;
ly=lx;
centX=(4*r)/3*pi;
centY=(4*r)/3*pi;
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
if(strcmp(orient,'nw')==1);
    y=[0:0.1:r];
    x=sqrt(r.^2-y.^2);
    plot((-x),y);
    hold on
    axis([-r*2 0.5 -0.5 r*2]);
    x1=0*y;
    plot((-y),x1,x1,y,'b');
    hold off
    s1=num2str(area);
    s2='area = ';
    s=strcat(s2,s1);
    text((-r*2)+1,r*2,s);
    s1=num2str(circ);
    s2='circ = ';
    s=strcat(s2,s1);
    text((-r*2)+1,r*1.8,s);
    s1=num2str(centX);
    s2='centX = ';
    s=strcat(s2,s1);
    text((-r*2)+1,r*1.6,s);
    s1=num2str(centY);
    s2='centY = ';
    s=strcat(s2,s1);
    text((-r*2)+1,r*1.4,s);
    s1=num2str(lx);
    s2='lx = ';
    s=strcat(s2,s1);
    text((-r*2)+1,r*1.2,s);
    s1=num2str(ly);
    s2='ly = ';
    s=strcat(s2,s1);
    text((-r*2)+1,r*1.1,s);
elseif(strcmp(orient,'ne')==1);
    y=[0:0.1:r];
    x=sqrt(r.^2-y.^2);
    plot(x,y);
    hold on
    axis([-0.5 r*2 -0.5 r*2]);
    x1=0*y;
    plot(y,x1,x1,y,'b');
    hold off
    s1=num2str(area);
    s2='area = ';
    s=strcat(s2,s1);
    text(0,r*2,s);
    s1=num2str(circ);
    s2='circ = ';
    s=strcat(s2,s1);
    text(0,r*1.8,s);
    s1=num2str(centX);
    s2='centX = ';
    s=strcat(s2,s1);
    text(0,r*1.6,s);
    s1=num2str(centY);
    s2='centY = ';
    s=strcat(s2,s1);
    text(0,r*1.4,s);
    s1=num2str(lx);
    s2='lx = ';
    s=strcat(s2,s1);
    text(0,r*1.2,s);
    s1=num2str(ly);
    s2='ly = ';
    s=strcat(s2,s1);
    text(0,r*1.1,s);
elseif(strcmp(orient,'sw')==1);
    y=[0:0.1:r];
    x=sqrt(r.^2-y.^2);
    plot((-x),(-y));
    hold on
    axis([-r*2 0.5 -r*2 0.5]);
    x1=0*y;
    plot((-y),x1,x1,(-y),'b');
    hold off
    s1=num2str(area);
    s2='area = ';
    s=strcat(s2,s1);
    text((-r*2)+1,(-r/6*1),s);
    s1=num2str(circ);
    s2='circ = ';
    s=strcat(s2,s1);
    text((-r*2)+1,(-r/6*2),s);
    s1=num2str(centX);
    s2='centX = ';
    s=strcat(s2,s1);
    text((-r*2)+1,(-r/6*3),s);
    s1=num2str(centY);
    s2='centY = ';
    s=strcat(s2,s1);
    text((-r*2)+1,(-r/6*4),s);
    s1=num2str(lx);
    s2='lx = ';
    s=strcat(s2,s1);
    text((-r*2)+1,(-r/6*5),s);
    s1=num2str(ly);
    s2='ly = ';
    s=strcat(s2,s1);
    text((-r*2)+1,(-r/6*6),s);
elseif(strcmp(orient,'se')==1);
    y=[0:0.1:r];
    x=sqrt(r.^2-y.^2);
    plot(x,(-y));
    hold on
    axis([-0.5 r*2 -r*2 0.5]);
    x1=0*y;
    plot(y,x1,x1,(-y),'b');
    hold off
    s1=num2str(area);
    s2='area = ';
    s=strcat(s2,s1);
    text(r,(-r/6*1),s);
    s1=num2str(circ);
    s2='circ = ';
    s=strcat(s2,s1);
    text(r,(-r/6*2),s);
    s1=num2str(centX);
    s2='centX = ';
    s=strcat(s2,s1);
    text(r,(-r/6*3),s);
    s1=num2str(centY);
    s2='centY = ';
    s=strcat(s2,s1);
    text(r,(-r/6*4),s);
    s1=num2str(lx);
    s2='lx = ';
    s=strcat(s2,s1);
    text(r,(-r/6*5),s);
    s1=num2str(ly);
    s2='ly = ';
    s=strcat(s2,s1);
    text(r,(-r/6*6),s);
end
