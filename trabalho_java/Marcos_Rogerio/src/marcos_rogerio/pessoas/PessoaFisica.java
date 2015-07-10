package marcos_rogerio.pessoas;

import java.text.DateFormat;
import java.text.NumberFormat;
import java.util.Date;
import java.util.Map;
import java.util.Set;

import marcos_rogerio.produtos.Venda;

// Classe que representa um Cliente do tipo PessoaFisica

public class PessoaFisica extends Cliente {

	private String cpf;

	// Construtor da classe PessoaFisica
	
	public PessoaFisica(int identificador, String nome, String endereco,
			String telefone, Date dataInicio, String cpf) {
		super(identificador, nome, endereco, telefone, dataInicio);
		this.cpf = cpf;
	}

	//Método que retorna uma linha do arquivo "2-areceber"
	
	public String lucro(Set<Venda> conjunto) {

		double lucro = 0;
		for (Venda v : conjunto) {
			if (this.identificador == v.cliente())
				lucro = lucro + v.receita();
		}

		DateFormat df = DateFormat.getDateInstance(DateFormat.MEDIUM);
		NumberFormat nf = NumberFormat.getCurrencyInstance();
		return (this.nome + ";F;" + this.cpf + ";" + this.telefone + ";"
				+ df.format(this.dataInicio) + ";" + nf.format(lucro));

	}

}
