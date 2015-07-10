#include "Produto.h"
#include "Cliente.h"
#include <string>
#include <set>
#include <map>
#include <fstream>
#include "util/Tokenizer.h"
#include "util/NumberUtils.h"
#include "Venda.h"

using namespace std;
using namespace br_ufes_inf_nemo_cpp_util;

namespace trabalho_cpp {

Venda::Venda(int cliente, time_t data, int produto, int quantidade,
		FormaPgto forma_pag) {
	this->cliente = cliente;
	this->data = data;
	this->produto = produto;
	this->quantidade = quantidade;
	this->forma_pag = forma_pag;

}

int Venda::num_cliente() {
	return cliente;
}

int Venda::get_produto() {
	return produto;
}

double Venda::receita(map<int, Produto> mapa_p) {
	return (mapa_p.at(produto).valor_venda()) * quantidade;
}

double Venda::lucro(map<int, Produto> mapa_p) {
	return (mapa_p.at(produto)).lucro_unidade() * quantidade;
}

int Venda::prod_vendidos(Produto p, map<int, Venda> mapa_v){
	int saldo = 0;
	for(auto& v : mapa_v){
		if(p.get_codigo() == (v.second).produto){
			saldo = saldo + (v.second).quantidade;
		}
	}
	return saldo;
}

void Venda::calc_lucro_receita(map<int, Venda> mapa_v,
		map<int, Produto> mapa_p, Produto& p) {
	double lucro = 0;
	double receita = 0;

	for(auto& v : mapa_v) {
		if(p.get_codigo() == (v.second).get_produto()) {
			lucro = lucro + (v.second).lucro(mapa_p);
			receita = receita + (v.second).receita(mapa_p);
		}
	}
	p.set_lucro_receita(lucro, receita);

}

ostream& operator<<(ostream& out, Venda v) {
	string linha;
	linha += to_string(v.cliente);
	linha += ';';
	linha += formatDate(v.data, DATE_FORMAT_PT_BR_SHORT);
	linha += ';';
	linha += to_string(v.produto);
	linha += ';';
	linha += to_string(v.quantidade);
	linha += ';';
	linha += v.forma_pag;
	linha += ";\n";
	return out << linha;
}

Venda::~Venda() {
}

}
