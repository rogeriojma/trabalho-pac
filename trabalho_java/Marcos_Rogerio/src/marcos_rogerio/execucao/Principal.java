package marcos_rogerio.execucao;

/* Trabalho prático realizado pela dupla:
 *
 *	Marcos Mercandeli Rodrigues  e	Rogerio Jose Menezes Alves, 
 *
 * como requisito para aprovação parcial na disciplina de PAC
 * (Programação Aplicada de Computadores), do curso de Engenharia
 * Elétrica da UFES, ministrada pelo Prof. Vitor Estevão Silva Souza.
 * 
 * 21/06/2014
 */

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import marcos_rogerio.pessoas.Cliente;
import marcos_rogerio.pessoas.Fornecedor;
import marcos_rogerio.produtos.Compra;
import marcos_rogerio.produtos.FormasPagamento;
import marcos_rogerio.produtos.Produto;
import marcos_rogerio.produtos.Venda;

// Classe principal que contem a função main() do trabalho prático

public class Principal {

	public static void main(String[] args) {

		// Verifica as entradas por linha de comando

		int indProd = 0, indCli = 0, indFor = 0, indComp = 0, indVend = 0;

		for (int i = 0; i < args.length; i++) {

			switch (args[i]) {
			case "-c":
				indCli = i + 1;
				break;
			case "-p":
				indProd = i + 1;
				break;
			case "-f":
				indFor = i + 1;
				break;
			case "-a":
				indComp = i + 1;
				break;
			case "-v":
				indVend = i + 1;
				break;
			}
		}

		// Cria as coleções

		Map<Integer, Produto> produtos = new HashMap<Integer, Produto>();
		Map<Integer, Cliente> clientes = new HashMap<Integer, Cliente>();
		Map<Integer, Fornecedor> fornecedores = new HashMap<Integer, Fornecedor>();
		Set<Compra> compras = new HashSet<Compra>();
		Set<Venda> vendas = new HashSet<Venda>();

		// Armazena as informacoes

		Produto.addProdutos(produtos, new File(args[indProd]));

		Cliente.addClientes(clientes, new File(args[indCli]));

		Fornecedor.addFornecedores(fornecedores, new File(args[indFor]));

		Compra.addCompra(compras, new File(args[indComp]), fornecedores,
				produtos);

		Venda.addVendas(vendas, clientes, produtos, new File(args[indVend]));

		// Imprime o arquivo apagar e areceber

		Fornecedor.apagar(fornecedores, compras, new File("1-apagar.csv"));

		Cliente.areceber(clientes, vendas, new File("2-areceber.csv"));

		// Cria uma lista a partir dos produtos e seus lucros

		for (Integer i : produtos.keySet()) {
			produtos.get(i).lucro_total(vendas);
		}

		List<Produto> listaProd = new ArrayList<Produto>();
		for (Integer i : produtos.keySet()) {
			listaProd.add(produtos.get(i));
		}

		// Ordena a lista

		Collections.sort(listaProd);

		// Imprime o arquivo de vendas e lucro por produto

		Produto.imprime_produto_lucro(listaProd, new File("3-vendasprod.csv"));

		// Cria uma lista de formas de pagamento a partir de suas receitas e
		// lucros

		List<FormasPagamento> listaFormas = new ArrayList<FormasPagamento>();
		for (FormasPagamento f : FormasPagamento.values()) {
			f.lucro(Venda.lucroPorForma(vendas, f));
			f.receita(Venda.receitaPorForma(vendas, f));
			listaFormas.add(f);
		}

		// Ordena a lista
		Collections.sort(listaFormas, new FormasPagamento.ComparadorFormas());

		// Imprime o arquivo de vendas e lucro por forma de pagamento

		FormasPagamento.vendas_lucro_formas(listaFormas, new File(
				"4-vendaspgto.csv"));

		// Ordena a lista de produtos novamente, pela descricao

		Collections.sort(listaProd, new Produto.ComparaProdutoDescricao());

		// Contabiliza as vendas e compras no estoque

		for (Produto p : listaProd) {
			p.estoque_atual(vendas, compras);
		}

		// Imprime o arquivo de estoque

		Produto.imprime_produto_estoque(listaProd, new File("5-estoque.csv"));
	}
}
