driver: driver.o BST.o ListP.o 
	g++ -o driver driver.o BST.o ListP.o

driver.o: driver.cpp ListP.h BST.h
	g++ -c driver.cpp

BST.o: BST.cpp BST.h TreeException.h TreeNodeBST.h  KeyedItem.h
	g++ -c BST.cpp

ListP.o: ListP.cpp ListP.h ListException.h ListIndexOutOfRangeException.h
	g++ -c ListP.cpp

