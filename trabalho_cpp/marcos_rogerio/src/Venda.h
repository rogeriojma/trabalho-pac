
#ifndef VENDA_H_
#define VENDA_H_

#include <iostream>
#include <string>
#include "Produto.h"
#include "util/DateUtils.h"
#include "FormasPgto.h"

using namespace std;
using namespace br_ufes_inf_nemo_cpp_util;

namespace trabalho_cpp {

class Venda {

	//Atributos de uma venda
	int cliente;
	time_t data;
	int produto;
	int quantidade;
	FormaPgto forma_pag;

public:

	//Construtor
	Venda(int, time_t, int, int, FormaPgto);

	//Função que retorna o identificador do cliente relacionado a venda
	int num_cliente();

	//Função que retorna o identificador do produto relacionado a venda
	int get_produto();

	//Implementação inline da função que retorna a forma de pagamento relacionada a venda
	FormaPgto get_forma(){ return forma_pag; }

	//Função que retorna a receita da venda
	double receita(map<int, Produto>);

	//Função que retorna o lucro da venda
	double lucro(map<int, Produto>);

	//Função que retorna o numero de produtos vendidos dado um produto
	static int prod_vendidos(Produto, map<int, Venda>);

	//Função que calcula e atribui o lucro e a receita de um produto
	static void calc_lucro_receita(map<int, Venda>, map<int, Produto>, Produto&);

	friend ostream& operator<<(ostream&, Venda);

	virtual ~Venda();
};
}
#endif /* VENDA_H_ */
