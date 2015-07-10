#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include <string>
#include "util/DateUtils.h"
#include "Venda.h"

using namespace std;

namespace trabalho_cpp {

//Declarações da classe cliente
class Cliente {

protected:

	//Atributos a serem herdados por PessoaFisica e PessoaJuridica
	int identificador;
	string nome;
	string endereco;
	string telefone;
	time_t data;

public:

	//Construtor
	Cliente(int, string, string, string, time_t );

	//Função que será implementada pelas subclasses de Cliente
	virtual string lucro(map<int, Venda>, map<int, Produto>);

	virtual ~Cliente();
};


//Declarações da subclasse PessoaFisica
class PessoaFisica: public Cliente {

	friend class Cliente;

	//Atributo exclusivo de PessoaFisica
	string cpf;

public:

	//Construtor
	PessoaFisica(int, string, string, string, time_t, string);

	//Função que retorna uma linha a ser impressa no arquivo "2-areceber.csv"
	string lucro(map<int, Venda>, map<int, Produto>);

	virtual ~PessoaFisica();
};

//Declarações da subclasse PessoaJuridica
class PessoaJuridica: public Cliente {

	friend class Cliente;

	//Atributos exclusivos de PessoaJuridica
	string cnpj;
	int inscricao;

public:

	//Construtor
	PessoaJuridica(int, string, string, string, time_t, string, int);

	//Função que retorna uma linha a ser impressa no arquivo "2-areceber.csv"
	string lucro(map<int, Venda>, map<int, Produto>);

	virtual ~PessoaJuridica();
};

}
#endif /* CLIENTE_H_ */
