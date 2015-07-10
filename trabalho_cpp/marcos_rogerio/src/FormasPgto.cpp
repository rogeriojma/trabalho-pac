#include "FormasPgto.h"
#include <string>
#include <ostream>
#include <iostream>
#include "util/NumberUtils.h"

using namespace std;
using namespace br_ufes_inf_nemo_cpp_util;

namespace trabalho_cpp {

//Função que, dado um caractere, retorna uma forma de pagamento
FormaPgto leEnum(char c) {
	switch (c) {
	case '$':
		return $;
	case 'X':
		return X;
	case 'D':
		return D;
	case 'C':
		return C;
	case 'T':
		return T;
	case 'F':
		return F;
	default:
		return $;
	}
}

//Função que, dada uma forma de pagamento, retorna seu caractere
char char_forma(FormaPgto f) {
	switch (f) {
	case 0:
		return '$';
	case 1:
		return 'X';
	case 2:
		return 'D';
	case 3:
		return 'C';
	case 4:
		return 'T';
	case 5:
		return 'F';
	default:
		return '$';
	}
}

//Construtor da classe que contém uma forma, um lucro e uma receita
TFormaPgto::TFormaPgto(FormaPgto f) {
	forma = f;
	lucro = 0;
	receita = 0;
}

//Função que ordena um vetor de instancias segundo a especificação
void TFormaPgto::sort_formas(TFormaPgto *f){
	for (unsigned i = 0; i < 6; i++) {

		//Cria uma forma temporária, que armazenará os candidatos
		TFormaPgto forma_temp(leEnum(' '));
		forma_temp.lucro = -1;

		//Armazena a posição dos temporários no vetor
		int temp = 0;

		//Ordena segundo o lucro, primeiro critério
		for (unsigned j = i; j < 6; j++) {
			if (f[i].lucro <= f[j].lucro && forma_temp.lucro < f[j].lucro) {
				forma_temp = f[j];
				temp = j;

				//Ordena segundo o caractere da forma, segundo critério
			} else if (f[i].lucro == f[j].lucro && forma_temp.lucro
					<= f[j].lucro) {
				if(i == 4 && j == 5) {
					if(char_forma(f[4].forma) > char_forma(f[5].forma)) {
						forma_temp = f[5];
						temp = 5;
						break;
					}
				}
				else if (char_forma(f[j].forma) < char_forma(f[i].forma)) {
					forma_temp = f[j];
					temp = j;
				}
			}
		}

		//Faz a mudança na ordem do vetor
		f[temp] = f[i];
		f[i] = forma_temp;
	}
}


ostream& operator<<(ostream& out, TFormaPgto f) {
	string linha;
	linha.push_back(char_forma(f.forma));
	linha += ';';
	linha += "R$ ";
	linha += formatDoubleCurrency(f.receita, LOCALE_PT_BR);
	linha += ';';
	linha += "R$ ";
	linha += formatDoubleCurrency(f.lucro, LOCALE_PT_BR);
	return out << linha;
}

}
