%Point
point = 0;
while point <= 100 
point = input('Please input your grade = ');
if (point >= 50) && (point < 55)  
    grade = 'D';
elseif (point >= 70) && (point < 75)  
    grade = 'B';
elseif (point >= 75) && (point < 80)  
    grade = 'B+';
elseif (point >= 65) && (point < 70)  
    grade = 'C+';
elseif (point >= 55) && (point < 60)  
    grade = 'D+';
elseif (point >= 60) && (point < 65)  
    grade = 'C';
elseif (point >= 80) && (point <= 100)  
    grade = 'A';
elseif  point<50
    grade = 'F';
end
if point<=100
fprintf('Your Grade is %s \n',grade);
else
fprintf('Please input Your New Grade Again\n');
grade = 0;
end
switch grade
	case 'A'
		fprintf('You get A Ultimate\n');
	case 'B+' 
		fprintf('You get B+ Excellent\n');
	case 'B' 
		fprintf('You get B Good\n');
    case 'C+' 
		fprintf('You get C+ Standard\n');
    case 'C' 
		fprintf('You get C Medium\n');
    case 'D+' 
		fprintf('You get D+ Fair\n');
    case 'D' 
		fprintf('You get D Adjust\n');
    case 'F' 
		fprintf('You get F Bad\n');
end
point = 0;
end
