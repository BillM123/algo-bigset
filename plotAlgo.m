executionTimes = [6*10^-5 2 235]; %In minutes

fileIDErdos = fopen("output/Erdos-cpls.out","r");
fileIDKarate = fopen("output/karate-cpls.out","r");
fileIDGrid = fopen("output/grid-cpls.out","r");

cplsErdos = fscanf(fileIDErdos,"%lf\n");
cplsKarate = fscanf(fileIDKarate,"%lf\n");
cplsGrid = fscanf(fileIDGrid,"%lf\n");

fclose(fileIDErdos);
fclose(fileIDKarate);
fclose(fileIDGrid);

fileIDErdos = fopen("output/Erdos-Sizes.out","r");
fileIDKarate = fopen("output/karate-Sizes.out","r");
fileIDGrid = fopen("output/grid-Sizes.out","r");

sizesErdos = fscanf(fileIDErdos,"%lf\n");
sizesKarate = fscanf(fileIDKarate,"%lf\n");
sizesGrid = fscanf(fileIDGrid,"%lf\n");

fclose(fileIDErdos);
fclose(fileIDKarate);
fclose(fileIDGrid);

medianCPLErdos = median(cplsErdos);
medianCPLKarate = median(cplsKarate);
medianCPLGrid = median(cplsGrid);

meanCPLErdos = mean(cplsErdos);
meanCPLKarate = mean(cplsKarate);
meanCPLGrid = mean(cplsGrid);

A = [meanCPLErdos medianCPLErdos; meanCPLKarate medianCPLKarate; 
    meanCPLGrid medianCPLGrid;];

figure("Name","Execution Time per Graph");
bar(["Karate" "Grid" "Erdos"],executionTimes);
xlabel("Graphs");
ylabel("Minutes");

figure("Name","Average and Mean CPL for all Graphs");
bar(["Karate" "Grid" "Erdos"],A);
xlabel("Graphs");
ylabel("CPL");
legend("Mean Value","Median Value");

figure("Name","CPL evolution during execution time for Erdos Graph");
bar(cplsErdos);
xlabel("Sub Graph");
ylabel("CPL for Sub Graph");

figure("Name","CPL evolution during execution time for Karate Graph");
bar(cplsKarate);
xlabel("Sub Graph");
ylabel("CPL for Sub Graph");

figure("Name","CPL evolution during execution time for Grid Graph");
bar(cplsGrid);
xlabel("Sub Graph");
ylabel("CPL for Sub Graph");

figure("Name","Bigger graph plot after a split for Erdos Graph");
bar(sizesErdos);
xlabel("Bigger Graph every split");
ylabel("Size in nodes");

figure("Name","Bigger graph plot after a split for Karate Graph");
bar(sizesKarate);
xlabel("Bigger Graph every split");
ylabel("Size in nodes");

figure("Name","Bigger graph plot after a split for Grid Graph");
bar(sizesGrid);
xlabel("Bigger Graph every split");
ylabel("Size in nodes");