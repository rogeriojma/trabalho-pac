
#ifndef COMPRA_H_
#define COMPRA_H_

#include <map>
#include <iostream>
#include <string>
#include "util/DateUtils.h"
#include "Produto.h"
#include "Fornecedor.h"


using namespace std;
using namespace br_ufes_inf_nemo_cpp_util;

namespace trabalho_cpp {

class Compra {

	//Atributos de uma compra
	int nota_fiscal;
	int fornecedor;
	time_t data_compra;
	int produto;
	int quantidade;

public:

	//Construtor
	Compra(int, int, time_t, int, int);

	//Função que retorna
	double custo(map<int, Produto>);

	//Implementação inline da função get_produto
	int get_produto(){
		return produto;
	}

	//Função que retorna o número de produtos comprados 
	static int prod_comprados(Produto, map<int, Compra>);

	
	friend string Fornecedor::divida(map<int, Compra> mapa_c, map<int, Produto> mapa_p);

	friend ostream& operator<<(ostream&, Compra);

	virtual ~Compra();
};

}

#endif /* COMPRA_H_ */
