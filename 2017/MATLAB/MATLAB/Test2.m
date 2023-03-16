%----------------'
%open file
fid2 = fopen('test.bin','r');
%read data
B = fread(fid2,10,'float32');
D = fread(fid2,'int8');
%close file
fclose(fid2);
