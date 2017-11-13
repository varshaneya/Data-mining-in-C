irisdecision:	calentropy.o irisdatatree.o takedecision.o
		gcc -std=c99 -o irisdecision calentropy.o irisdatatree.o takedecision.o -lm
irisdatatree.o:	irisdatatree.c irisheader.h
		gcc -c -std=c99 irisdatatree.c irisheader.h
calentropy.o:	calentropy.c irisheader.h
		gcc -c -std=c99 calentropy.c irisheader.h -lm
takedecision.o:	takedecision.c irisheader.h
		gcc -c -std=c99 takedecision.c irisheader.h
clean:
		rm -f *.o
