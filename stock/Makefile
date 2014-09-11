stockdemo: stock.o mstack.o stockdemo.o
	gcc -o stockdemo stockdemo.o stock.o mstack.o
stock.o:
	gcc -c stock.c
stockdemo.o:
	gcc -c stockdemo.c
mstack.o:
	gcc -c mstack.c
clean:
	rm -f mstack.o stock.o stockdemo.o stockdemo
