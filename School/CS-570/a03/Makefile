pagetable: driver.o pagetable.o byu_tracereader.o
	cc driver.o pagetable.o byu_tracereader.o -o pagetable -std=c99

driver.o: driver.c pagetable.h byutr.h
	cc -c driver.c -std=c99

pagetable.o: pagetable.c pagetable.h
	cc -c pagetable.c -std=c99

byu_tracereader.o: byu_tracereader.c byutr.h
	cc -c byu_tracereader.c -std=c99
	
