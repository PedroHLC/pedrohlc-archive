package com.pedrohlc.vac.calendar;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Vector;

/**
 * Salva / Carrega e gerencia uma lista de pacientes
 * @author Pedro Henrique Lara Campos
 */
public class ListaPacientes extends Vector<Paciente> {
	private static final long serialVersionUID = -2956843911371305641L;

	private static SimpleDateFormat dateFmt = new SimpleDateFormat("dd/MM/yyyy");
	
	/**
	 * Procura por um paciente na lista
	 * @param query Id do paciente
	 * @return Paciente encontrado, null se não houve resultado
	 */
	public Paciente search (long query) {
		for (Paciente p: this)
			if (p.getId() == query)
				return p;
		return null;
	}
	
	/**
	 * Salva todas os pacientes em um arquivo txt separado por tabulações e quebras de linha
	 * @param filename Nome do arquivo destino
	 * @return Verdadeiro se salvo sem erros, falso se falhou
	 */
	public boolean save (String filename) {
		// Cria/abre o arquivo para editar
		File file = new File(filename);
		PrintWriter writer;
		try {
			writer = new PrintWriter(file, "UTF-8");
		} catch (IOException e) {
			return false;
		}
		
		// Escrever cada uma das vacinas no arquivo
		for (Paciente p: this) {
			writer.printf("%d\t%s\t%s\t%s\n", p.getId(), p.getName(), outputDate(p.getBirth()), p.getMotherName());
			p.saveVac ();
		}
		
		// Salva e fecha arquivo
		writer.write(0); //EOF (Not needed but interesting)
		writer.close();
		return true;
	}
	
	/**
	 * Carrega uma lista de pacientes de um arquivo
	 * @param filename Nome do arquivo para carregar
	 * @throws Exception Erros nor carregamento do arquivo ou arquivo corrompido
	 */
	public ListaPacientes (String filename) throws Exception {
		File file = new File(filename);
		if (!file.exists())
			return;
		
		FileReader fr = new FileReader(file);
		BufferedReader br = new BufferedReader(fr);
		
		String line;
		while((line = br.readLine()) != null){
			if (line.charAt(0) == 0 || line.isEmpty())
				break;
			if (line.charAt(line.length()-1) == '\n')
				line = line.subSequence(0, line.length()-1).toString();
			String parts[] = line.split("\t");
			if (parts.length != 4) {
				br.close();
			    fr.close();
				throw(new Exception("Corrupted database!"));
			}
			
			this.add(new Paciente(Long.parseLong(parts[0]), parts[1], formatDate(parts[2]), parts[3]));
	    }
		
	    br.close();
	    fr.close();
	}
	
	/**
	 * Interpreta a data
	 * @param datestr Data em formato de texto
	 * @return Data em objeto da classe java.util.Date
	 * @throws ParseException Data irreconhecivel
	 */
	public static Date formatDate (String datestr) throws ParseException {
		dateFmt.setLenient(false);
		return dateFmt.parse(datestr);
	}
	
	/**
	 * Formata data
	 * @param date Instancia de java.util.Date
	 * @return Data em texto
	 */
	public static String outputDate (Date date) {
		return dateFmt.format(date);
	}
}
