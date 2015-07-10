package marcos_rogerio.produtos;

import java.io.*;
import java.text.NumberFormat;
import java.util.*;

// Tipo enumerado que caracteriza as formas de pagamento possíveis.

public enum FormasPagamento implements Comparable<FormasPagamento>, Serializable {
	$("$"), X("X"), D("D"), C("C"), T("T"), F("F");

	private String forma;
	private double receita;
	private double lucro;

	FormasPagamento(String forma) {
		this.forma = forma;
	}

	// Sobrescrita do método toString()

	@Override
	public String toString() {
		NumberFormat nf = NumberFormat.getCurrencyInstance();
		return (this.forma + ";" + nf.format(this.receita) + ";" + nf
				.format(this.lucro));
	}

	// Método que cria uma uma nova forma do tipo especificado

	public static FormasPagamento novaForma(String forma_nova) {
		for (FormasPagamento formas : FormasPagamento.values())
			if (formas.forma.equals(forma_nova))
				return formas;
		return null;
	}

	// Método que retorna o lucro da padaria pelo qual a forma foi responsável

	public void lucro(double lucro) {
		this.lucro = lucro;
	}

	// Método que retorna a receita da padaria pelo qual a forma foi responsável

	public void receita(double receita) {
		this.receita = receita;
	}

	// Comparador entre formas a partir do lucro que cada uma gerou

	public static class ComparadorFormas implements Comparator<FormasPagamento> {
		public int compare(FormasPagamento f1, FormasPagamento f2) {
			if (f1.lucro > f2.lucro)
				return -1;
			else if (f1.lucro < f2.lucro)
				return 1;
			return f1.forma.compareTo(f2.forma);
		}
	}

	//Método que imprime o arquivo "4-vendaspgto"
	
	public static void vendas_lucro_formas(List<FormasPagamento> lista,
			File arquivo) {
		try {
			PrintWriter writer = new PrintWriter(arquivo);

			if (!arquivo.exists()) {
				arquivo.createNewFile();
			}

			// imprime o cabeçalho
			writer.println("Modo de pagamento;Receita bruta;Lucro");

			for (FormasPagamento f : lista) {
				writer.println(f);
			}

			writer.close();
		} catch (IOException e) {
			System.out.println("Erro de I/O.");
		}
	}

}