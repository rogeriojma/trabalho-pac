

#ifndef FORNECEDOR_H_
#define FORNECEDOR_H_

#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "Produto.h"

using namespace std;


namespace trabalho_cpp {
class Compra;
class Fornecedor {

	int identificador;
	string nome;
	string endereco;
	string telefone;
	string cnpj;
	string contato;

public:

	//Construtor
	Fornecedor(int, string, string,
			string, string, string);

	//Função que retorna uma linha a ser impressa no arquivo "1-apagar.csv"
	string divida(map<int, Compra>, map<int, Produto>);

	virtual ~Fornecedor();

	friend ostream& operator<<(ostream& out, Fornecedor f);

};

}
#endif /* FORNECEDOR_H_ */
