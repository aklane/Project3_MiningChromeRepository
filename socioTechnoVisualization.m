clear all
clc

mat = importdata('matrix.txt');

dev = importdata('developers.txt');


fileID = fopen('files.txt','r');
file = textscan(fileID,'%d %s','Delimiter','\t');

n = size(mat);
mat2= zeros(n(2));

for i=1:n(1)
    for j=1:n(2)
        for k=1:n(2)
            if mat(i,j)==1 && mat(i,k)==1  && j~=k            
                mat2(j,k)=mat2(j,k)+ 1;                
            end
        end
    end
end
disp(mat2);

dlmwrite('myFile.txt',mat2,'delimiter',' ');

fclose(fileID);

k = 1:n(2);                           
[mat2,XY] = bucky;
gplot(mat2(k,k),XY(k,:),'-pm')
for i=1:n(2)
    text(XY(i,1),XY(i,2),dev(i))    
end

xlabel('Developers who co-worked on the same file') 







