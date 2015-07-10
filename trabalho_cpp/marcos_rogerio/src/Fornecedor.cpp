#include "Fornecedor.h"
#include "Compra.h"
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "util/Tokenizer.h"
#include "util/NumberUtils.h"
#include <algorithm>

using namespace std;
using namespace br_ufes_inf_nemo_cpp_util;

namespace trabalho_cpp {

//Construtor
Fornecedor::Fornecedor(int identificador, string nome, string endereco,
		string telefone, string cnpj, string contato) {
	this->identificador = identificador;
	this->nome = nome;
	this->endereco = endereco;
	this->telefone = telefone;
	this->cnpj = cnpj;
	this->contato = contato;
}

//Função que retorna uma linha a ser escrita no arquivo "1-apagar.csv"
string Fornecedor::divida(map<int, Compra> mapa_c, map<int, Produto> mapa_p) {
	double divida = 0;
	for (map<int, Compra>::iterator it = mapa_c.begin(); it != mapa_c.end(); ++it) {
		Compra c = it->second;
		if (this->identificador == c.fornecedor)
			divida = divida + c.custo(mapa_p);
	}

	return (this->nome + ";" + this->cnpj + ";" + this->contato + ";"
			+ this->telefone + ";" + "R$ " + formatDoubleCurrency(divida,
			LOCALE_PT_BR));

}


ostream& operator<<(ostream& out, Fornecedor f) {
	string linha;
	linha += to_string(f.identificador);
	linha += ';';
	linha += f.nome;
	linha += ';';
	linha += f.endereco;
	linha += ';';
	linha += f.telefone;
	linha += ';';
	linha += f.cnpj;
	linha += ';';
	linha += f.contato;
	linha += ";\n";
	return out << linha;
}

Fornecedor::~Fornecedor() {
	// TODO Auto-generated destructor stub
}

}
