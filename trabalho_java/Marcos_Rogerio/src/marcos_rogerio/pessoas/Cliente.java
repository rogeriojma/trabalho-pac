package marcos_rogerio.pessoas;

import java.io.*;
import java.text.DateFormat;
import java.util.*;

import marcos_rogerio.produtos.Venda;

//Classe abstrata que representa uma pessoa qualquer

public abstract class Cliente implements Serializable{

	protected int identificador;
	protected String nome;
	protected String endereco;
	protected String telefone;
	protected Date dataInicio;

	// Construtor da classe abstrata

	public Cliente(int identificador, String nome, String endereco,
			String telefone, Date dataInicio) {

		this.identificador = identificador;
		this.nome = nome;
		this.endereco = endereco;
		this.telefone = telefone;
		this.dataInicio = dataInicio;

	}

	// Sobrescrita do método toString() da classe Object

	@Override
	public String toString() {
		return this.nome;
	}

	// Método que adciona clientes a um Map de clientes, a partir da leitura de
	// um arquivo

	public static void addClientes(Map<Integer, Cliente> mapa, File arquivo) {

		try (Scanner scanner = new Scanner(new BufferedReader(new FileReader(
				arquivo)))) {

			scanner.useDelimiter(";|\\n");
			scanner.useLocale(new Locale("pt", "BR"));

			// Pula a linha das descricoes do arquivo
			scanner.nextLine();

			while (scanner.hasNext()) {
				int identificador = scanner.nextInt();
				String nome = scanner.next();
				String endereco = scanner.next();
				String telefone = scanner.next();

				// formatando e armazenando a data
				DateFormat df = DateFormat.getDateInstance(DateFormat.MEDIUM);
				Date data = df.parse(scanner.next());

				// verificando se a pessoa e fisica ou juridica e armazenando o
				// cliente
				switch (scanner.next()) {

				case "F":
					String cpf = scanner.next();
					mapa.put(identificador, new PessoaFisica(identificador,
							nome, endereco, telefone, data, cpf));

					// descarta o ponto e virgula excedente
					if (scanner.hasNext())
						scanner.next();
					break;
				case "J":
					String cnpj = scanner.next();
					int inscricao = scanner.nextInt();
					mapa.put(identificador, new PessoaJuridica(identificador,
							nome, endereco, telefone, data, cnpj, inscricao));
					break;
				default:
					throw new IOException();

				}

			}

			scanner.close();
		} catch (Exception e) {
			System.out.println("Erro de I/O.");

		}

	}

	// Método abstrato que será implementado pelas subclasses, para uso do
	// polimorfismo

	public abstract String lucro(Set<Venda> conjunto);

	// Método que retorna o identificador do Cliente

	public int identificador() {
		return this.identificador;
	}

	// Método que escreve o arquivo "2-areceber"

	public static void areceber(Map<Integer, Cliente> mapa,
			Set<Venda> conjunto, File arquivo) {

		String[] linhas = new String[mapa.size()];
		int ind = 0;

		for (Integer i : mapa.keySet()) {
			linhas[ind] = mapa.get(i).lucro(conjunto);
			ind++;
		}

		Arrays.sort(linhas);

		try {
			PrintWriter writer = new PrintWriter(arquivo);

			if (!arquivo.exists()) {
				arquivo.createNewFile();
			}

			// imprime o cabeçalho
			writer.println("Cliente;Tipo;CPF/CNPJ;Telefone;Data de cadastro;Total a pagar");

			for (int i = 0; i < mapa.size(); i++) {
				writer.println(linhas[i]);
			}

			writer.close();
		} catch (IOException e) {
			System.out.println("Erro de I/O.");
		}

	}
}
