package marcos_rogerio.produtos;

import java.io.*;
import java.text.DateFormat;
import java.util.*;

import marcos_rogerio.pessoas.Fornecedor;

// Classe que representa uma compra feita pela padaria

public class Compra implements Serializable {

	private int notaFiscal;
	private Fornecedor fornecedor;
	private Date dataCompra;
	private Produto produto;
	private int quantidade;

	// Construtor da classe

	public Compra(int notaFiscal, Fornecedor fornecedor, Date dataCompra,
			Produto produto, int quantidade) {

		this.notaFiscal = notaFiscal;
		this.fornecedor = fornecedor;
		this.dataCompra = dataCompra;
		this.produto = produto;
		this.quantidade = quantidade;

	}

	// Sobrescrita do método toString()

	@Override
	public String toString() {
		DateFormat formatador = DateFormat.getDateInstance(DateFormat.MEDIUM);
		return ("Comprou " + this.produto + " de " + this.fornecedor + " , "
				+ this.quantidade + " unidades em " + formatador
					.format(dataCompra));
	}

	// Método que adciona compras a um Set<Compra>, a partir de um arquivo,
	// relacionando as compras com o produto comprado e com o fornecedor de quem
	// foi comprado.

	public static void addCompra(Set<Compra> conj, File arquivo,
			Map<Integer, Fornecedor> mapaFornecedores,
			Map<Integer, Produto> mapaProdutos) {
		try (Scanner scanner = new Scanner(new BufferedReader(new FileReader(
				arquivo)))) {

			scanner.useDelimiter(";|\\n");
			scanner.useLocale(new Locale("pt", "BR"));

			// Pula a linha de cabeçalho
			scanner.nextLine();

			while (scanner.hasNextLine()) {

				int notaFiscal = scanner.nextInt();
				int num_fornecedor = scanner.nextInt();

				// formatando e armazenando a data
				DateFormat df = DateFormat.getDateInstance(DateFormat.MEDIUM);
				Date data = df.parse(scanner.next());

				int num_produto = scanner.nextInt();
				int quantidade = scanner.nextInt();

				// armazena a compra no conjunto, ja associada ao fornecedor e
				// ao produto
				conj.add(new Compra(notaFiscal, mapaFornecedores
						.get(num_fornecedor), data, mapaProdutos
						.get(num_produto), quantidade));
			}

			scanner.close();
		} catch (Exception e) {
			System.out.println("Erro de I/O.");
		}

	}

	// Método que retorna o quanto custou a compra.
	
	public double custo() {
		return (this.produto.valor_custo()) * (this.quantidade);
	}

	// Método que retorna o numero que identifica o fornecedor da compra.
	
	public int fornecedor() {
		return (this.fornecedor.identificador());
	}

	// Método que retorna o código do produto comprado.
	
	public int produto() {
		return this.produto.codigo();
	}

	// Método que retorna a quantidade comprada.
	
	public int quantidade() {
		return this.quantidade;
	}
}
