package com.pedrohlc.vac.calendar;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Vector;

/** Carrega / Salva e gerencia uma lista com vacinas.
 * @author Pedro Henrique Lara Campos
 */
public class ListaVacinas extends Vector<Vacina> {
	private static final long serialVersionUID = 5528888782963994624L;

	/**
	 * Procura uma vacina pelo seu nome
	 * @param query Nome da vacina que será procurada
	 * @return Vacina encontrada ou nulo caso não exista
	 */
	public Vacina search (String query) {
		for (Vacina v: this)
			if (v.getName().equals(query))
				return v;
		return null;
	}
	
	/**
	 * Salva todas as vacinas em um arquivo txt separado por tabulações e quebras de linha
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
		for (Vacina v: this)
			writer.printf("%s\t%d\t%s\t%s\n", v.getName(), v.getDose(), v.getCommaSepAges(), v.getDisease());
		
		// Salva e fecha arquivo
		writer.write(0); //EOF (Not needed but interesting)
		writer.close();
		return true;
	}
	
	/**
	 * Carrega uma lista de vacina de um arquivo
	 * @param filename Nome do arquivo para carregar
	 * @throws Exception Erros nor carregamento do arquivo ou arquivo corrompido
	 */
	public ListaVacinas (String filename) throws Exception {
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
			
			String[] part2txt = parts[2].split(",");
			short[] part2 = new short[part2txt.length];
			for (byte i = 0; i < part2txt.length; i++)
				part2[i] = Short.parseShort(part2txt[i]);
			
			this.add(new Vacina(parts[0], Byte.parseByte(parts[1]), part2, parts[3]));
	    }
		
	    br.close();
	    fr.close();
	}
}
