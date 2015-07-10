//Arquivo header da classe produto


#ifndef PRODUTO_H_
#define PRODUTO_H_

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

namespace trabalho_cpp {

//Declaração antecipada da classe venda

class Venda;

//Definição da classe produto

class Produto {

	//Atributos de um produto
	
	string descricao;
	int codigo;
	int estoque_min;
	int estoque_atual;
	double valor_custo;
	int percent_lucro;

	//Atributos inicializados com 0 que recebem seus valores após
	//o processamento das vendas

	double receita;
	double lucro_total;

public:

	//Construtores

	Produto() {};
	Produto(int, string, int, int, double, int);

	//Funções de ordenação de produtos para escrita dos arquivos
	static void sort_produtos_vendasprod(vector<Produto>&);
	static void sort_produtos_estoque(vector<Produto>&);

	//Função que recebe os valores dos atributos receita e lucro_total
	void set_lucro_receita(double, double);

	//Função que retorna o código do produto
	double get_codigo();

	//Função que calcula e retorna o valor de venda do produto
	double valor_venda();

	//Função que retorna o custo de um produto
	double custo();

	//Função que retorna o lucro por unidade vendida do produto
	double lucro_unidade();

	//Função que atualiza o estoque após o processamento das compras e vendas
	void set_estoque(int);

	//Função que retorna uma linha a ser estoque no arquivo 5-estoque.csv
	string linha_estoque();

	//Função que verifica se é necessário comprar mais do produto
	bool comprar_mais();

	//Declaração como "friend" da sobrescrita do operador <<
	friend ostream& operator<<(ostream&, Produto);

};

}

#endif /* PRODUTO_H_ */
