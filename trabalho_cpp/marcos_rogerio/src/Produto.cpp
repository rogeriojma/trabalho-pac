#include "Produto.h"
#include <string>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include "util/Tokenizer.h"
#include "util/NumberUtils.h"
#include <limits>

using namespace std;
using namespace br_ufes_inf_nemo_cpp_util;

namespace trabalho_cpp {

//Implementação do construtor não-vazio de Produto
Produto::Produto(int codigo, string descricao, int estoque_min,
		int estoque_atual, double valor_custo, int percent_lucro) {
	this->codigo = codigo;
	this->descricao = descricao;
	this->estoque_min = estoque_min;
	this->estoque_atual = estoque_atual;
	this->valor_custo = valor_custo;
	this->percent_lucro = percent_lucro;
	this->receita = 0;
	this->lucro_total = 0;
}


//Algorítimo de ordenação de produtos para o arquivo "3-vendasprod.csv"
void Produto::sort_produtos_vendasprod(vector<Produto>& vetor) {
	
	for (unsigned i = 0; i < vetor.size(); i++) {
		
		//Produto temporário que irá armazenar os candidatos
		Produto prod_temp(-1, "", -1, -1, -1, -1);
		
		//Variável que verifica se existiu uma mudança na ordem
		bool changed = false;
		
		//Variável que armazena a posição do candidato
		int pos_temp = 0;
		for (unsigned j = i + 1; j < vetor.size(); j++) {
			
			//Comparação por lucro (primeiro critério)
			if((vetor[j]).lucro_total < (vetor[i].lucro_total)
					|| (vetor[j]).lucro_total < (prod_temp.lucro_total)) {
				continue;
			} else if ((vetor[j]).lucro_total > (vetor[i].lucro_total)
					&& (vetor[j]).lucro_total > (prod_temp.lucro_total)) {
				prod_temp = vetor[j];
				pos_temp = j;
				changed = true;
				continue;

			//Caso em que há empate, compara por código
			} else {
				if(prod_temp.codigo == -1){
					prod_temp.codigo = numeric_limits<int>::max();
				} 
				if ((vetor[i].codigo) > (vetor[j].codigo) && 
						(vetor[j].codigo) < (prod_temp.codigo)){
					prod_temp = vetor[j];
					pos_temp = j;
					changed = true;
					continue;
				}
			}
		}

		//Se existe um candidato, realiza a mudança na ordem do vetor
		if(changed){
			vetor[pos_temp] = vetor[i];
			vetor[i] = prod_temp;
		}
	}
}

//Algorítimo de ordenação de produtos para o arquivo "5-estoque.csv"
void Produto::sort_produtos_estoque(vector<Produto>& vetor) {
	for (unsigned i = 0; i < vetor.size(); i++) {
		
		//Produto temporário que armazena os candidatos
		Produto prod_temp(-1, "", -1, -1, -1, -1);
		//Variável que armazena a posição dos candidatos
		int pos_temp = 0;
		for (unsigned j = i; j < vetor.size(); j++) {
			
			//Primeiro caso, compara por descrição
			if ((vetor[j]).descricao < (vetor[i].descricao)
					&& (vetor[j]).descricao < (prod_temp.descricao)) {
				prod_temp = vetor[j];
				pos_temp = j;

			//Caso haja empate, compara por código
			} else if ((vetor[j].descricao) == (vetor[i].descricao)) {
				if (prod_temp.codigo == -1) {
					prod_temp.codigo = numeric_limits<int>::max();
				}
				if (vetor[j].codigo <= vetor[i].codigo && vetor[j].codigo
						<= prod_temp.codigo) {
					prod_temp = vetor[j];
					pos_temp = j;
				}
			}
		}

		//Se há um candidato, realiza a mudança na ordem
		vetor[pos_temp] = vetor[i];
		vetor[i] = prod_temp;
	}
}

//Função que retorna o código do produto
double Produto::get_codigo() {
	return codigo;
}

//Função que retorna o valor de venda do produto
double Produto::valor_venda() {
	return valor_custo * (1.0 + percent_lucro / 100.0);
}

//Função que retorna o valor de custo do produto
double Produto::custo() {
	return this->valor_custo;
}

//Função que retorna o lucro por unidade do produto
double Produto::lucro_unidade() {
	return (this->valor_venda() - valor_custo);
}

//Função que recebe os valores de lucro_total e receita do produto
void Produto::set_lucro_receita(double luc, double rec) {
	lucro_total = luc;
	receita = rec;
}

//Função que atualiza o estoque após o processamento das compras e vendas
void Produto::set_estoque(int saldo) {
	estoque_atual = estoque_atual - saldo;
}

//Função que retorna uma linha a ser escrita no arquivo "5-estoque.csv"
//É usada porque o operador << já for sobrescrito
string Produto::linha_estoque() {
	string linha;
	linha += to_string(codigo);
	linha += ";";
	linha += descricao;
	linha += ";";
	linha += to_string(estoque_atual);
	linha += ";";
	return linha;
}

//Função que verifica se é necessário comprar mais do produto
bool Produto::comprar_mais() {
	if (estoque_atual < estoque_min)
		return true;
	return false;
}

//Sobrescrita do operador << para ser usado no arquivo "3-vendasprod"
ostream& operator<<(ostream& out, Produto p) {
	string linha;
	linha += to_string(p.codigo);
	linha += ';';
	linha += p.descricao;
	linha += ';';
	linha += "R$ ";
	linha += formatDoubleCurrency(p.receita, LOCALE_PT_BR);
	linha += ';';
	linha += "R$ ";
	linha += formatDoubleCurrency(p.lucro_total, LOCALE_PT_BR);
	linha += "\n";
	return out << linha;
}

}

