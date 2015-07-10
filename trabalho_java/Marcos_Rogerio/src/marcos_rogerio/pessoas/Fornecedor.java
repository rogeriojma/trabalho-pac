package marcos_rogerio.pessoas;

import java.io.*;
import java.text.NumberFormat;
import java.util.*;

import marcos_rogerio.produtos.Compra;

//Classe que representa um forncedor de produtos associado à padaria

public class Fornecedor implements Serializable{

	protected int identificador;
	protected String nome;
	protected String endereco;
	protected String telefone;
	private String cnpj;
	private String contato;

	// Construtor da classe

	public Fornecedor(int identificador, String nome, String endereco,
			String telefone, String cnpj, String contato) {

		this.identificador = identificador;
		this.nome = nome;
		this.endereco = endereco;
		this.telefone = telefone;
		this.cnpj = cnpj;
		this.contato = contato;

	}

	// Sobrescrita do método toString()

	@Override
	public String toString() {
		return this.nome;
	}

	// Método para adcionar fornecedores a um Map de fornecedores, a partir de
	// um arquivo

	public static void addFornecedores(Map<Integer, Fornecedor> mapa,
			File arquivo) {

		try (Scanner scanner = new Scanner(new BufferedReader(new FileReader(
				arquivo)))) {

			scanner.useDelimiter(";|\\n");
			scanner.useLocale(new Locale("pt", "BR"));

			// pula a linha de cabeçalho do arquivo
			scanner.nextLine();

			while (scanner.hasNext()) {
				int identificador = scanner.nextInt();
				mapa.put(
						identificador,
						new Fornecedor(identificador, scanner.next(), scanner
								.next(), scanner.next(), scanner.next(),
								scanner.next()));

			}

			scanner.close();
		} catch (Exception e) {
			System.out.println("Erro de I/O");
		}

	}

	// Método que retorna o número identificador do fornecedor

	public int identificador() {
		return this.identificador;
	}

	// Método que retorna uma linha, relacionada à instância que o executou, do
	// arquivo "1-apagar"

	public String divida(Set<Compra> conjunto) {

		double divida = 0;

		for (Compra c : conjunto) {
			if (this.identificador == c.fornecedor())
				divida = divida + c.custo();
		}

		NumberFormat nf = NumberFormat.getCurrencyInstance(new Locale("pt",
				"BR"));

		return (this.nome + ";" + this.cnpj + ";" + this.contato + ";"
				+ this.telefone + ";" + nf.format(divida));

	}

	// Método estático, que imprime o arquivo "1-apagar", usando as linhas do
	// método divida()

	public static void apagar(Map<Integer, Fornecedor> mapa,
			Set<Compra> conjunto, File arquivo) {

		String[] linhas = new String[mapa.size()];
		int ind = 0;

		for (Integer i : mapa.keySet()) {
			linhas[ind] = mapa.get(i).divida(conjunto);
			ind++;
		}

		Arrays.sort(linhas);

		try {
			PrintWriter writer = new PrintWriter(arquivo);

			if (!arquivo.exists()) {
				arquivo.createNewFile();
			}

			// imprime o cabeçalho
			writer.println("Fornecedor;CNPJ;Pessoa de contato ;Telefone;Total a pagar");

			for (int i = 0; i < mapa.size(); i++) {
				writer.println(linhas[i]);
			}

			writer.close();
		} catch (IOException e) {
			System.out.println("Erro de I/O.");
		}
	}

}
