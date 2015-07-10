package marcos_rogerio.pessoas;

import java.text.*;
import java.util.*;

import marcos_rogerio.produtos.Venda;

// Classe que representa um Cliente do tipo PessoaJuridica

public class PessoaJuridica extends Cliente{
	
	private String cnpj;
	private int inscricao;

	// Construtor da classe PessoaJuridica
	
	PessoaJuridica(int identificador, String nome, String endereco,
			String telefone, Date dataInicio, String cnpj, int inscricao){
		
		super(identificador, nome, endereco, telefone, dataInicio);
		this.cnpj = cnpj;
		this.inscricao = inscricao;
		
	}
	
	// Método que retorna uma linha do arquivo "2-areceber"
	
	public String lucro(Set<Venda> conjunto) {

		double lucro = 0;
		for (Venda v : conjunto) {
			if (this.identificador == v.cliente())
				lucro = lucro + v.receita();
		}

		DateFormat df = DateFormat.getDateInstance(DateFormat.MEDIUM);
		NumberFormat nf = NumberFormat.getCurrencyInstance();
		return (this.nome + ";J;" + this.cnpj + ";" + this.telefone + ";"
				+ df.format(this.dataInicio)+ ";" + nf.format(lucro) );

	}
}
