OBJS := bin/ClasseIO.o bin/Cliente.o bin/Compra.o bin/FormasPgto.o bin/Fornecedor.o bin/Produto.o bin/Venda.o bin/util/NumPunctPTBR.o bin/util/NumberUtils.o bin/util/DateUtils.o bin/util/Tokenizer.o
UTIL := bin/util/DateUtils.o bin/util/NumberUtils.o bin/util/NumPunctPTBR.o bin/util/Tokenizer.o
COMPILER := g++ -std=c++11
CFLAGS := -Wall -c 

all: Main

Main: $(OBJS) $(UTIL)
	$(COMPILER) src/main.cpp $(OBJS) -o bin/Main

bin/util/NumberUtils.o: src/util/NumberUtils.cpp src/util/NumberUtils.h
	$(COMPILER) $(CFLAGS) src/util/NumberUtils.cpp -o bin/util/NumberUtils.o

bin/util/NumPunctPTBR.o: src/util/NumPunctPTBR.cpp src/util/NumPunctPTBR.h
	$(COMPILER) $(CFLAGS) src/util/NumPunctPTBR.cpp -o bin/util/NumPunctPTBR.o

bin/util/Tokenizer.o: src/util/Tokenizer.cpp src/util/Tokenizer.h
	$(COMPILER) $(CFLAGS) src/util/Tokenizer.cpp -o bin/util/Tokenizer.o

bin/util/DateUtils.o: src/util/DateUtils.cpp src/util/DateUtils.h
	$(COMPILER) $(CFLAGS) src/util/DateUtils.cpp -o bin/util/DateUtils.o

bin/Produto.o: src/Produto.cpp src/Produto.h bin/util/Tokenizer.o bin/util/NumberUtils.o
	$(COMPILER) $(CFLAGS) src/Produto.cpp -o bin/Produto.o

bin/Fornecedor.o: src/Fornecedor.cpp src/Fornecedor.h bin/Compra.o bin/util/Tokenizer.o bin/util/NumberUtils.o
	$(COMPILER) $(CFLAGS) src/Fornecedor.cpp -o bin/Fornecedor.o

bin/Cliente.o: src/Cliente.cpp src/Cliente.h bin/util/DateUtils.o
	$(COMPILER) $(CFLAGS) src/Cliente.cpp -o bin/Cliente.o

bin/Compra.o: src/Compra.cpp src/Compra.h bin/util/Tokenizer.o bin/util/NumberUtils.o bin/util/DateUtils.o
	$(COMPILER) $(CFLAGS) src/Compra.cpp -o bin/Compra.o

bin/Venda.o: src/Venda.cpp src/Venda.h bin/Produto.o bin/FormasPgto.o bin/Cliente.o
	$(COMPILER) $(CFLAGS) src/Venda.cpp -o bin/Venda.o

bin/FormasPgto.o: src/FormasPgto.cpp src/FormasPgto.h bin/util/NumberUtils.o
	$(COMPILER) $(CFLAGS) src/FormasPgto.cpp -o bin/FormasPgto.o

bin/ClasseIO.o: src/ClasseIO.cpp src/ClasseIO.h bin/Cliente.o bin/Fornecedor.o bin/Produto.o bin/Compra.o bin/Venda.o bin/FormasPgto.o bin/util/Tokenizer.o bin/util/NumberUtils.o bin/util/DateUtils.o
	$(COMPILER) $(CFLAGS) src/ClasseIO.cpp -o bin/ClasseIO.o

run:
	./bin/Main -c clientes.csv -p produtos.csv -a compras.csv -v vendas.csv -f fornecedores.csv

clean:
	rm -f Main bin/*.o bin/util/*.o *.csv

