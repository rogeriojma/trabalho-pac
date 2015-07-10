#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "util/DateUtils.h"
#include "util/Tokenizer.h"
#include "util/NumberUtils.h"
#include "Cliente.h"
#include "ClasseIO.h"

using namespace std;
using namespace br_ufes_inf_nemo_cpp_util;

namespace trabalho_cpp {

//Função que lê o arquivo de produtos
void ClasseIO::add_produtos(map<int, Produto>& mapa, string arquivo) {
	try{
	ifstream in(arquivo);
	string linha;
	getline(in, linha);

	while (getline(in, linha)) {

		//Verifica se há uma quebra de linha ao final, e não uma nova linha
		if (linha == "")
			break;
		Tokenizer tok(linha, ';');
		int codigo = stoi(tok.next());
		string descricao = tok.next();
		int estoque_min = stoi(tok.next());
		int estoque_atual = stoi(tok.next());
		double valor_custo = parseDouble(tok.next(), LOCALE_PT_BR);
		int percentual_lucro = stoi(tok.next());

		//Cria um produto com os dados da linha
		Produto p(codigo, descricao, estoque_min, estoque_atual, valor_custo,
				percentual_lucro);

		//Insere o produto no mapa
		mapa.insert(pair<int, Produto> (codigo, p));

	}
	in.close();
	}
	catch(exception& e){
		cout << "Erro de I/O." << endl;
	}
}

//Função que lê o arquivo de fornecedores
void ClasseIO::add_fornecedores(map<int, Fornecedor>& mapa, string arquivo) {
	try{
	ifstream in(arquivo);
	string linha;
	getline(in, linha);
	while (getline(in, linha)) {
		
		//Verifica se há uma quebra de linha, e não uma nova linha
		if (linha == "")
			break;
		Tokenizer tok(linha, ';');
		int identificador = stoi(tok.next());
		string nome = tok.next();
		string endereco = tok.next();
		string telefone = tok.next();
		string cnpj = tok.next();
		string contato = tok.next();

		//Cria um novo fornecedor com os dados da linha
		Fornecedor f(identificador, nome, endereco, telefone, cnpj, contato);

		//Insere o fornecedor no mapa
		mapa.insert(pair<int, Fornecedor> (identificador, f));
	}
	in.close();
	}
	catch(exception& e){
		cout << "Erro de I/O." << endl;
	}
}

//Função que lê o arquivo de clientes
void ClasseIO::add_clientes(map<int, Cliente*>& mapa, string arquivo) {
	try{
	ifstream in(arquivo);
	string linha;
	getline(in, linha);
	char tipo;
	while (getline(in, linha)) {

		//Verifica se há uma quebra de linha, e não uma linha inteira
		if (linha == "")
			break;
		Tokenizer tok(linha, ';');
		int identificador = stoi(tok.next());
		string nome = tok.next();
		string endereco = tok.next();
		string telefone = tok.next();
		time_t data = parseDate(tok.next(), DATE_FORMAT_PT_BR_SHORT);

		tipo = (tok.next())[0];

		//Cria uma pessoa jurídica ou física, conforme o tipo informado
		switch (tipo) {
		case 'J': {
			string cnpj = tok.next();
			int inscricao = stoi(tok.next());

			PessoaJuridica* pj = new PessoaJuridica(identificador, nome,
					endereco, telefone, data, cnpj, inscricao);
			mapa.insert(pair<int, Cliente*> (identificador, pj));
			break;
		}
		case 'F': {
			string cpf = tok.next();
			tok.next();

			PessoaFisica* pf = new PessoaFisica(identificador, nome, endereco,
					telefone, data, cpf);
			mapa.insert(pair<int, Cliente*> (identificador, pf));
			break;
		}

		}

	}
	in.close();
	}
	catch(exception& e){
		cout << "Classe de I/O." << endl;
	}
}

//Função que lê o arquivo de compras
void ClasseIO::add_compras(map<int, Compra>& mapa, string arquivo) {
	try{
	ifstream in(arquivo);
	string linha;
	getline(in, linha);
	int i = 0;
	while (getline(in, linha)) {
		
		//Verifica se há uma quebra de linha ou uma linha inteira
		if (linha == "")
			break;
		Tokenizer tok(linha, ';');
		int nota_fiscal = stoi(tok.next());
		int num_fornec = stoi(tok.next());
		time_t data = parseDate(tok.next(), DATE_FORMAT_PT_BR_SHORT);
		int num_prod = stoi(tok.next());
		int quantidade = stoi(tok.next());

		//Cria a compra e insere no mapa
		Compra c(nota_fiscal, num_fornec, data, num_prod, quantidade);
		mapa.insert(pair<int, Compra> (i, c));
		i++;
	}
	in.close();
	}
	catch(exception& e){
		cout << "Erro de I/O." << endl;
	}

}

//Função que lê o arquivo de vendas
void ClasseIO::add_vendas(map<int, Venda>& mapa, string arquivo) {
	try{
	ifstream in(arquivo);
	string linha;
	getline(in, linha);
	int i = 0;
	while (getline(in, linha)) {
		Tokenizer tok(linha, ';');
		string cod_temp = tok.next();

		//Variável que, ou armazena a data antecipamente, ou diz se há uma quebra de linha
		string data_temp = tok.next();
		if (!data_temp.compare("")) { break; }
		int num_cli;
		time_t data;
		int num_prod;
		int quantidade;
		FormaPgto forma;

		//Cria uma venda relacionando-a com um cliente, ou não, e adciona ao mapa
		if (!cod_temp.compare("")) {
			num_cli = -1;
			data = parseDate(data_temp, DATE_FORMAT_PT_BR_SHORT);
			num_prod = stoi(tok.next());
			quantidade = stoi(tok.next());
			forma = leEnum((tok.next())[0]);
		} else {
			num_cli = stoi(cod_temp);
			data = parseDate(data_temp, DATE_FORMAT_PT_BR_SHORT);
			num_prod = stoi(tok.next());
			quantidade = stoi(tok.next());
			forma = leEnum((tok.next())[0]);
		}
		Venda v(num_cli, data, num_prod, quantidade, forma);
		mapa.insert(pair<int, Venda> (i, v));
		i++;

	}
	in.close();
	}
	catch(exception& e){
		cout << "Erro de I/O." << endl;
	}
}

//Função que escreve o arquivo "1-apagar.csv"
void ClasseIO::apagar(map<int, Fornecedor>& mapa_f, map<int, Compra>& mapa_c,
		map<int, Produto>& mapa_p, string arquivo) {
	try{
	ofstream out(arquivo);

	//Escreve o cabeçalho do arquivo
	out << "Fornecedor;CNPJ;Pessoa de contato ;Telefone;Total a pagar" << endl;
	vector < string > linhas;

	//Adciona as linha a serem impressas para o vetor
	for (auto& f : mapa_f) {
		linhas.push_back((f.second).divida(mapa_c, mapa_p));
	}

	//Ordena as linhas e escreve no arquivo
	sort(linhas.begin(), linhas.end());
	for (vector<string>::iterator it = linhas.begin(); it != linhas.end(); it++) {
		out << *it << endl;
		;
	}
	out.close();
	}
	catch(exception& e){
		cout << "Erro de I/O." << endl;
	}
}

//Função que escreve o arquivo "2-areceber.csv"
void ClasseIO::areceber(map<int, Cliente*> mapa_c, map<int, Venda> mapa_v,
		map<int, Produto> mapa_p, string arquivo) {
	try{
	ofstream out(arquivo);
	vector < string > linhas;

	//Escreve o cabeçalho do arquivo
	out << "Cliente;Tipo;CPF/CNPJ;Telefone;Data de cadastro;Total a pagar"
			<< endl;

	//Adciona as linhas a serem impressas pelo vetor
	for(auto& c : mapa_c) {
		linhas.push_back((c.second)->lucro(mapa_v, mapa_p));
	}

	//Ordena as linhas e escreve no arquivo
	sort(linhas.begin(), linhas.end());
	for (vector<string>::iterator it = linhas.begin(); it != linhas.end(); it++) {
		out << *it << endl;
	}
	out.close();
	}
	catch(exception& e){
		cout << "Erro de I/O." << endl;
	}
}

//Função que escreve o arquivo "3-vendasprod.csv"
void ClasseIO::vendasprod(map<int, Produto> mapa_p, map<int, Venda> mapa_v,
		string arquivo) {
	try{
	ofstream out(arquivo);
	vector<Produto> prod_vec;

	//Escreve o cabeçalho do arquivo
	out << "Código;Produto;Receita bruta;Lucro" << endl;

	//Calcula o lucro_total e a receita para cada produto e adciona-o ao vetor
	for(auto& p : mapa_p) {
		Venda::calc_lucro_receita(mapa_v, mapa_p, p.second);
		prod_vec.push_back(p.second);
	}

	//Ordena o vetor de produtos segundo os critérios da especificação
	Produto::sort_produtos_vendasprod(prod_vec);

	//Escreve cada produto no arquivo com o operador << sobrescrito
	for(auto& p : prod_vec) {
		out << p;
	}
	out.close();
	}
	catch(exception& e){
		cout << "Erro de I/O." << endl;
	}
}

//Função que escreve o arquivo "4-vendaspgto.csv"
void ClasseIO::vendaspgto(map<int, Venda> mapa_v, map<int, Produto> mapa_p,
		string arquivo) {
	try{
	ofstream out(arquivo);

	//Cria um vetor de formas de pagamento e outro de structs de forma com lucro e receita
	FormaPgto f_temp[6] = { leEnum('$'), leEnum('X'), leEnum('D'), leEnum('C'),
			leEnum('T'), leEnum('F') };
	TFormaPgto f[6] = { TFormaPgto(f_temp[0]), TFormaPgto(f_temp[1]),
			TFormaPgto(f_temp[2]), TFormaPgto(f_temp[3]),
			TFormaPgto(f_temp[4]), TFormaPgto(f_temp[5]) };

	//Escreve o cabeçalho do arquivo
	out << "Modo de pagamento;Receita bruta;Lucro" << endl;

	//Adciona a cada struct a seu lucro e sua receita, para cada forma
	for (unsigned i = 0; i < 6; i++) {
		double lucro_temp = 0;
		double receita_temp = 0;
		for	(auto& v : mapa_v) {
			if(f[i].get_forma() == (v.second).get_forma()) {
				lucro_temp = lucro_temp + (v.second).lucro(mapa_p);
				receita_temp = receita_temp + (v.second).receita(mapa_p);
			}
		}
		f[i].set_receita(receita_temp);
		f[i].set_lucro(lucro_temp);
	}

	//Ordena as formas de acordo com os critérios da especificação
	TFormaPgto::sort_formas(f);

	//Escreve as formas no arquivo com o operador sobrescrito <<
	for (int i = 0; i < 6; i++) {
		out << f[i] << endl;
	}
	out.close();
	}
	catch(exception& e){
		cout << "Erro de I/O." << endl;
	}
}

//Função que escreve o arquivo "5-estoque.csv"
void ClasseIO::estoque(map<int, Produto> mapa_p, map<int, Compra> mapa_c, map<int, Venda> mapa_v, string arquivo) {
	try{
	ofstream out(arquivo);
	vector<Produto> vec_prod;

	//Escreve o cabeçalho do arquivo
	out << "Código;Produto;Quantidade em estoque;Observações" << endl;

	//Atualiza o estoque de cada produto e adciona-o ao vetor
	for(auto& p : mapa_p) {
		int saldo = Venda::prod_vendidos((p.second), mapa_v) - Compra::prod_comprados((p.second), mapa_c);
		(p.second).set_estoque(saldo);
		vec_prod.push_back(p.second);
	}

	//Ordena os produtos de acordo com os critérios da especificação
	Produto::sort_produtos_estoque(vec_prod);

	//Verifica se, para cada produto, há a necessidade de comprar mais e escreve o produto
	for(auto& p : vec_prod) {
		if(p.comprar_mais()) {
			out << p.linha_estoque() << "COMPRAR MAIS" << endl;
		}
		else
		out << p.linha_estoque() << endl;
	}
	out.close();
	}
	catch(exception& e){
		cout << "Erro de I/O." << endl;
	}
}

ClasseIO::~ClasseIO() {}

}
