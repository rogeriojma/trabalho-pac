#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include <string>
#include "Cliente.h"
#include "util/Tokenizer.h"
#include "util/DateUtils.h"
#include "util/NumberUtils.h"

using namespace std;
using namespace br_ufes_inf_nemo_cpp_util;

namespace trabalho_cpp {

//Construtor 
Cliente::Cliente(int identificador, string nome, string endereco,
		string telefone, time_t data) {
	this->identificador = identificador;
	this->nome = nome;
	this->endereco = endereco;
	this->telefone = telefone;
	this->data = data;
}

//Método que será implementado nas subclasses para polimorfismo
string Cliente::lucro(map<int, Venda> mapa_v, map<int, Produto> mapa_p) {
	return "";
}

Cliente::~Cliente() {}

//Construtor da subclasse PessoaFisica
PessoaFisica::PessoaFisica(int identificador, string nome, string endereco,
		string telefone, time_t data, string cpf) :
	Cliente(identificador, nome, endereco, telefone, data) {
	this->cpf = cpf;
}

//Função que retorna uma linha a ser impressa no arquivo "2-areceber.csv"
string PessoaFisica::lucro(map<int, Venda> mapa_v, map<int, Produto> mapa_p) {
	double lucro_d = 0;

	//Calcula o lucro e receita para cada PessoaFisica
	for (auto& v : mapa_v) {
		if(this->identificador == (v.second).num_cliente())
		lucro_d = lucro_d + (v.second).receita(mapa_p);
	}

	return (nome + ";F;" + cpf + ";" + telefone + ";" + formatDate(data,
			DATE_FORMAT_PT_BR_SHORT) + ";R$ " + formatDoubleCurrency(lucro_d,
			LOCALE_PT_BR));

}

PessoaFisica::~PessoaFisica() {}


//Construtor da subclasse PessoaJuridica
PessoaJuridica::PessoaJuridica(int identificador, string nome, string endereco,
		string telefone, time_t data, string cnpj, int inscricao) :
	Cliente(identificador, nome, endereco, telefone, data) {
	this->cnpj = cnpj;
	this->inscricao = inscricao;
}

PessoaJuridica::~PessoaJuridica() {}

//Função que retorna uma linha a ser impressa no arquivo "2-areceber.csv"
string PessoaJuridica::lucro(map<int, Venda> mapa_v, map<int, Produto> mapa_p) {
	double lucro_d = 0;

	//Calcula o lucro e receita para cada PessoaJuridica
	for (auto& v : mapa_v) {
		if(this->identificador == (v.second).num_cliente())
		lucro_d = lucro_d + (v.second).receita(mapa_p);
	}

	return (nome + ";J;" + cnpj + ";" + telefone + ";" + formatDate(data,
			DATE_FORMAT_PT_BR_SHORT) + ";R$ " + formatDoubleCurrency(lucro_d,
			LOCALE_PT_BR));
}


}
