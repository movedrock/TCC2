clc

%freq = (30)*rand(30,1);
%satis = (10)*rand(30,1);

inputs = horzcat(freq,satis);


fismat = readfis('PROJETO3');
out = evalfis(inputs,fismat);

