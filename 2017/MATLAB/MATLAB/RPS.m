% Rock Paper Scissors
PA=0;
PB=0;
O1 = fopen('compotition.txt','r');
C = fscanf(O1,'%s',[26]);
fclose(O1);
for(x=1:2:26);
A(x) = C(x);
B(x) = C(x+1);
%disp(x)
end
O2 = fopen('Result.txt','W');
for(x=1:2:25);
    if(A(x)=='R')&&(B(x)=='R');
        fprintf(O2,'Draw\n');
    elseif(A(x)=='R')&&(B(x)=='S');
        fprintf(O2,'A wins\n');
        PA=PA+1;
    elseif(A(x)=='R')&&(B(x)=='P');
        fprintf(O2,'B wins\n');
        PB=PB+1;
    elseif(A(x)=='S')&&(B(x)=='R');
        fprintf(O2,'B wins\n');
        PB=PB+1;
    elseif(A(x)=='S')&&(B(x)=='S');
        fprintf(O2,'Draw\n'); 
    elseif(A(x)=='S')&&(B(x)=='P');
        fprintf(O2,'A wins\n');
        PA=PA+1;
    elseif(A(x)=='P')&&(B(x)=='R');
        fprintf(O2,'A wins\n');
        PA=PA+1;
    elseif(A(x)=='P')&&(B(x)=='S');
        fprintf(O2,'B wins\n');
        PB=PB+1;
    elseif(A(x)=='P')&&(B(x)=='P');
        fprintf(O2,'Draw\n');
    end
end
if(PA>PB);
    fprintf(O2,'RESULT = A is Champion!!\n');
else
    fprintf(O2,'RESULT = B is Champion!!\n');
end
fprintf(O2,'Signed Thanyasit');
fclose(O2);

