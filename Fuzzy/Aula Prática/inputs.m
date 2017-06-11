lin=1;
for(i=0:10:100),
    for(j=0:10:100),
        entrada(lin,:) = [i j];
        lin = lin+1;
    end
end