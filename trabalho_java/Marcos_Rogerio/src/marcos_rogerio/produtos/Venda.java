package marcos_rogerio.produtos;

import java.io.*;
import java.text.*;
import java.util.*;

import marcos_rogerio.pessoas.Cliente;

//Classe que representa uma venda feita pela padaria

public class Venda implements Comparable<Venda>, Serializable {

	private Cliente cliente;
	private Date data;
	private Produto produto;
	private int quantidade;
	private FormasPagamento forma_pag;

	// Construtor da classe Venda

	public Venda(Cliente cliente, Date data, Produto produto, int quantidade,
			FormasPagamento forma_pag) {
		this.cliente = cliente;
		this.data = data;
		this.produto = produto;
		this.quantidade = quantidade;
		this.forma_pag = forma_pag;

	}

	// Implementação do método compareTo()

	public int compareTo(Venda v) {
		if (this.lucro() > v.lucro())
			return 1;
		else if (this.lucro() < v.lucro())
			return -1;
		return 0;

	}

	// Método que adciona vendas a um conjunto de vendas, relacionando com o
	// cliente que comprou e os produtos comprados, a partir de um arquivo

	public static void addVendas(Set<Venda> conj,
			Map<Integer, Cliente> clientes, Map<Integer, Produto> produtos,
			File arquivo) {

		try (Scanner scanner = new Scanner(new BufferedReader(new FileReader(
				arquivo)))) {

			scanner.useDelimiter(";|\\n");
			scanner.useLocale(new Locale("pt", "BR"));

			// Pula a linha de cabeçalho
			scanner.nextLine();

			while (scanner.hasNext()) {
				int cliente = -1;
				if (scanner.hasNextInt())
					cliente = scanner.nextInt();
				else
					scanner.next();

				// formatando e armazenando a data
				DateFormat df = DateFormat.getDateInstance(DateFormat.MEDIUM);
				Date data = df.parse(scanner.next());

				int produto = scanner.nextInt();
				int quantidade = scanner.nextInt();
				FormasPagamento fp = FormasPagamento.novaForma(scanner.next());

				Cliente ninguem = null;
				if (cliente == -1) {
					conj.add(new Venda(ninguem, data, produtos.get(produto),
							quantidade, fp));
				} else {
					conj.add(new Venda(clientes.get(cliente), data, produtos
							.get(produto), quantidade, fp));
				}

			}

			scanner.close();
		} catch (Exception e) {
			System.out.println("Erro de I/O.");
		}

	}

	// Sobrescrita do método toString()

	@Override
	public String toString() {
		NumberFormat nf = NumberFormat.getCurrencyInstance();
		return ("" + nf.format(this.lucro()));
	}

	// Método que retorna a receita da venda

	public double receita() {
		return this.produto.valor_venda() * this.quantidade;
	}

	// Método que retorna o lucro da venda

	public double lucro() {
		return this.produto.lucro() * this.quantidade;
	}

	// Método que retorna o identificador do cliente que comprou

	public int cliente() {
		if (this.cliente == null)
			return -1;
		return this.cliente.identificador();
	}

	// Método que retorna o código do produto comprado
	
	public int produto() {
		return this.produto.codigo();
	}

	// Método que retorna a quantidade de produtos comprada
	
	public int quantidade() {
		return this.quantidade;
	}

	// Método que retorna a forma de pagamento utilizada na venda
	
	public FormasPagamento forma_pagamento() {
		return this.forma_pag;
	}

	// Método que atribui o devido lucro para as formas
	
	public static double lucroPorForma(Set<Venda> conjunto,
			FormasPagamento forma) {

		double lucro = 0;

		for (Venda v : conjunto) {
			if (forma == v.forma_pag) {
				lucro = lucro + v.lucro();
			}
		}

		return lucro;
	}

	// Método que atribui a devida receita para as formas
	
	public static double receitaPorForma(Set<Venda> conjunto,
			FormasPagamento forma) {

		double receita = 0;

		for (Venda v : conjunto) {
			if (forma == v.forma_pag) {
				receita = receita + v.receita();
			}
		}

		return receita;
	}

}
