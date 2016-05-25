clear all
clc

fileID = fopen('log-raw2.txt','r');

C = textscan(fileID,'%d %s','Delimiter','\t');
fclose(fileID);
n = size(C{1});

h = bar(diag(C{1}),'stacked');
colormap(summer(n(1)));
grid on
set(gca,'xticklabel', C{2}) 
title('Developers according to number of commits');

