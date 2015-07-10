package marcos_rogerio.produtos;

import java.io.*;
import java.text.NumberFormat;
import java.util.*;

// Classe que caracteriza um produto qualquer no estoque (ou não) da padaria

public class Produto implements Comparable<Produto>, Serializable {

	private int codigo;
	private String descricao;
	private int estoque_min;
	private int estoque;
	private double valor_custo;
	private int percent_lucro;
	private double receita;
	private double lucro_total;

	// Construtor da classe Produto

	public Produto(int codigo, String descricao, int estoque_min, int estoque,
			double valor_custo, int percent_lucro) {

		this.codigo = codigo;
		this.descricao = descricao;
		this.estoque_min = estoque_min;
		this.estoque = estoque;
		this.valor_custo = valor_custo;
		this.percent_lucro = percent_lucro;

	}

	// Método que retorna o valor de venda de uma unidade com base no custo e no
	// percentual de lucro do produto

	public double valor_venda() {
		return valor_custo * ((double) 1.0 + percent_lucro / 100.0);
	}

	// Método que retorna o valor de custo de uma unidade do produto

	public double valor_custo() {
		return this.valor_custo;
	}

	// Método que retorna o lucro obtido pela padaria na venda de uma unidade do
	// produto

	public double lucro() {
		return (this.valor_venda() - this.valor_custo());
	}

	// Método que, a partir das vendas feitas pela padaria, retorna o lucro
	// total obtido pelo produto

	public double lucro_total(Set<Venda> conjunto) {
		double lucro = 0;
		this.receita = 0;

		for (Venda v : conjunto) {
			if (this.codigo == v.produto()) {
				lucro = lucro + v.lucro();
				this.receita = receita + v.receita();
			}

		}
		this.lucro_total = lucro;
		return lucro;

	}

	// Método que, a partir das compras e vendas feitas pela padaria, retorna o
	// estoque atual do produto.

	public int estoque_atual(Set<Venda> vendas, Set<Compra> compras) {

		for (Compra c : compras) {
			if (this.codigo == c.produto())
				this.estoque = this.estoque + c.quantidade();
		}

		for (Venda v : vendas) {
			if (v.produto() == this.codigo)
				this.estoque = this.estoque - v.quantidade();
		}

		return this.estoque;

	}

	// Método que verifica se o número de produtos no estoque está baixo

	public boolean comprar_mais() {
		return (this.estoque < this.estoque_min);
	}

	// Sobrescrita do método toString()

	@Override
	public String toString() {
		NumberFormat nf = NumberFormat.getCurrencyInstance();

		return (this.codigo + ";" + this.descricao + ";"
				+ nf.format(this.receita) + ";" + nf.format(this.lucro_total));
	}

	// Método que retorna uma linha do arquivo "5-estoque"

	public String linhaEstoque() {
		return (this.codigo + ";" + this.descricao + ";" + this.estoque);
	}

	// Método que retorna o código do produto

	public int codigo() {
		return this.codigo;
	}

	// Método que adciona produtos a um Map<Integer, Produto> a partir de um
	// arquivo

	public static void addProdutos(Map<Integer, Produto> mapa, File arquivo) {

		try (Scanner scanner = new Scanner(new BufferedReader(new FileReader(
				arquivo)))) {

			scanner.useDelimiter(";|\\n");
			scanner.useLocale(new Locale("pt", "BR"));

			// Pula a linha das descricoes do arquivo
			scanner.nextLine();

			while (scanner.hasNext()) {
				int codigo = scanner.nextInt();
				mapa.put(codigo,
						new Produto(codigo, scanner.next(), scanner.nextInt(),
								scanner.nextInt(), scanner.nextDouble(),
								scanner.nextInt()));

			}

			scanner.close();
		} catch (IOException e) {
			System.out.println("Erro de I/O.");

		}
	}

	// Implementação do método compareTo() para compara produtos pelo lucro
	// total

	public int compareTo(Produto p) {
		if (this.lucro_total > p.lucro_total)
			return -1;
		else if (this.lucro_total < p.lucro_total)
			return 1;

		return this.codigo - p.codigo;
	}

	// Comparador para produtos segundo sua descrição

	public static class ComparaProdutoDescricao implements Comparator<Produto> {
		public int compare(Produto p1, Produto p2) {
			return p1.descricao.compareTo(p2.descricao);
		}
	}

	// Método que imprime o arquivo "3-vendasprod"
	
	public static void imprime_produto_lucro(List<Produto> lista, File arquivo) {

		try {
			PrintWriter writer = new PrintWriter(arquivo);

			if (!arquivo.exists()) {
				arquivo.createNewFile();
			}

			// imprime o cabeçalho
			writer.println("Código;Produto;Receita bruta;Lucro");

			for (Produto p : lista) {
				writer.println(p);
			}

			writer.close();
		} catch (IOException e) {
			System.out.println("Erro de I/O.");
		}
	}

	// Método que imprime o arquivo "5-estoque"
	
	public static void imprime_produto_estoque(List<Produto> lista, File arquivo) {

		try {
			PrintWriter writer = new PrintWriter(arquivo);

			if (!arquivo.exists()) {
				arquivo.createNewFile();
			}

			// imprime o cabeçalho
			writer.println("Código;Produto;Quantidade em estoque;Observações");

			for (Produto p : lista) {
				writer.print(p.linhaEstoque());
				if (p.comprar_mais())
					writer.println(";COMPRAR MAIS");
				else
					writer.println(";");
			}

			writer.close();
		} catch (IOException e) {
			System.out.println("Erro de I/O.");
		}
	}
}
