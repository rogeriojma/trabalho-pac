#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include <string>
#include "Compra.h"
#include "util/Tokenizer.h"
#include "util/NumberUtils.h"
#include "util/DateUtils.h"

using namespace std;
using namespace br_ufes_inf_nemo_cpp_util;

namespace trabalho_cpp {

//Construtor
Compra::Compra(int nota_fiscal, int fornec, time_t data_compra,
		int prod, int quantidade) {
	this->nota_fiscal = nota_fiscal;
	this->fornecedor = fornec;
	this->data_compra = data_compra;
	this->produto = prod;
	this->quantidade = quantidade;
}

//Função que retorna o custo da compra
double Compra::custo(map<int, Produto> mapa){
	Produto p = mapa.at(produto);
	return p.custo()*quantidade;
}

//Função que retorna o numero de produtos comprados dado um produto e um mapa de compras
int Compra::prod_comprados(Produto p, map<int, Compra> mapa_c){
	int saldo = 0;
	for(auto& c : mapa_c){
		if(p.get_codigo() == (c.second).get_produto()){
			saldo = saldo + (c.second).quantidade;
		}
	}
	return saldo;
}


ostream& operator<<(ostream& out, Compra c){
	string linha;
	linha += to_string(c.nota_fiscal);
	linha += ';';
	linha += to_string(c.fornecedor);
	linha += ';';
	linha += formatDate(c.data_compra, DATE_FORMAT_PT_BR_SHORT);
	linha += ';';
	linha += to_string(c.produto);
	linha += ';';
	linha += to_string(c.quantidade);
	linha += ";\n";
	return out << linha;
}

Compra::~Compra() {}

}
