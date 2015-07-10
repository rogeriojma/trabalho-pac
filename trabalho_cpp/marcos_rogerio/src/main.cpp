#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "Produto.h"
#include "Fornecedor.h"
#include "Cliente.h"
#include "Compra.h"
#include "Venda.h"
#include "ClasseIO.h"

using namespace std;
using namespace trabalho_cpp;

int main(int argc, char** argv) {

	//Analisa os argumentos passados pela linha de comando e armazena os nomes 
	//dos arquivos

	int ind_prod = 0, ind_cli = 0, ind_for = 0, ind_comp = 0, ind_vend = 0;

	for (int i = 0; i < argc; i++) {
		string s(argv[i]);
		if(s == "-c"){
			ind_cli = ++i;
		}
		if(s == "-v"){
			ind_vend = ++i;
		}
		if(s == "-p"){
			ind_prod = ++i;
		}
		if(s == "-f"){
			ind_for = ++i;
		}
		if(s == "-a"){
			ind_comp = ++i;
		}
	}

	string arq_cli(argv[ind_cli]);
	string arq_vend(argv[ind_vend]);
	string arq_prod(argv[ind_prod]);
	string arq_for(argv[ind_for]);
	string arq_comp(argv[ind_comp]);

	//Cria as coleções (mapas) para armazenar os dados 

	map<int, Produto> produtos;
	map<int, Fornecedor> fornecedores;
	map<int, Cliente*> clientes;
	map<int, Compra> compras;
	map<int, Venda> vendas;

	//Executa as funções de leitura dos arquivos 

	ClasseIO::add_produtos(produtos, arq_prod);
	ClasseIO::add_fornecedores(fornecedores, arq_for);
	ClasseIO::add_clientes(clientes, arq_cli);
	ClasseIO::add_compras(compras, arq_comp);
	ClasseIO::add_vendas(vendas, arq_vend);

	//Executa as funções de escrita nos arquivos

	ClasseIO::apagar(fornecedores, compras, produtos, "1-apagar.csv");
	ClasseIO::areceber(clientes, vendas, produtos, "2-areceber.csv");
	ClasseIO::vendasprod(produtos, vendas, "3-vendasprod.csv");
	ClasseIO::vendaspgto(vendas, produtos, "4-vendaspgto.csv");
	ClasseIO::estoque(produtos, compras, vendas, "5-estoque.csv");

	return 0;

}
