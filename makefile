loansanction:	calgini.o bankloantree.o testdata.o
	gcc -o loansanction calgini.o bankloantree.o testdata.o
calgini.o:	calgini.c bankheader.h
	gcc -c  calgini.c bankheader.h -lm
bankloantree.o:	bankloantree.c bankheader.h
	gcc -c  bankloantree.c bankheader.h
testdata.o: testdata.c bankheader.h
	gcc -c testdata.c bankheader.h	
clean:
	rm  *.o
