//Arquivo header da classe de I/O do programa

#ifndef CLASSEIO_H_
#define CLASSEIO_H_

#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "util/DateUtils.h"
#include "Cliente.h"
#include "Venda.h"
#include "Fornecedor.h"
#include "Compra.h"
#include "FormasPgto.h"


using namespace std;
using namespace br_ufes_inf_nemo_cpp_util;

namespace trabalho_cpp {

class ClasseIO {
public:

	//Construtor vazio da classe
	ClasseIO() { };

	//Funções de leitura dos arquivos
	static void add_produtos(map<int, Produto>&, string);
	static void add_fornecedores(map<int, Fornecedor>&, string);
	static void add_clientes(map<int, Cliente*>&, string);
	static void add_compras(map<int, Compra>&, string);
	static void add_vendas(map<int, Venda>&, string);

	//Funções de escrita dos arquivos
	static void apagar(map<int, Fornecedor>&, map<int, Compra>&, map<int, Produto>&, string);
	static void areceber(map<int, Cliente*>, map<int, Venda>, map<int, Produto>, string);
	static void vendasprod(map<int, Produto>, map<int, Venda>, string);
	static void vendaspgto(map<int, Venda>, map<int, Produto>, string);
	static void estoque(map<int, Produto>, map<int, Compra>, map<int, Venda>, string);

	virtual ~ClasseIO();
};

}

#endif /* CLASSEIO_H_ */
