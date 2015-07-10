

#ifndef FORMASPGTO_H_
#define FORMASPGTO_H_

#include <ostream>
#include <string>
#include <map>

using namespace std;

namespace trabalho_cpp {

//Definição do tipo enumerável das formas de pagamento

class Venda;
class Produto;

enum FormaPgto{
	$,
	X,
	D,
	C,
	T,
	F
};

//Função que, dado um caractere, retorna uma forma de pagamento
FormaPgto leEnum(char c);

//Função que faz o inverso da anterior. Dada uma forma, retorna seu caractere 
char char_forma(FormaPgto);

//Estrutura que relaciona uma forma de pagamento com um lucro e uma receita
class TFormaPgto{
	FormaPgto forma;
	double lucro;
	double receita;

	//Construtor da class
public:
	TFormaPgto(FormaPgto f);

	inline FormaPgto get_forma(){ return forma;}

	inline void set_receita(double rec){this->receita = rec;}

	inline void set_lucro(double luc){ this->lucro = luc;}

	//Função que, dado um vetor de structs, ordena-os segundo a especificação
	static void sort_formas(TFormaPgto *);

	friend ostream& operator<<(ostream&, TFormaPgto);

};

}

#endif /* FORMASPGTO_H_ */
