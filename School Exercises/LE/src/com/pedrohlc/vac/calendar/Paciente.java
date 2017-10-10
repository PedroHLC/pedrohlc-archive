package com.pedrohlc.vac.calendar;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Date;
import java.util.Random;
import java.util.Vector;

/**
 * Gerencia uma única puta
 * @author Pedro Henrique Lara Campos
 */
public class Paciente extends Vector<VacinaAplicada> {
	private static final long serialVersionUID = 1111458995758776828L;
	private static Random rand = new Random ();
		
	private Long code;
	private String name;
	private Date birth;
	private String mothername;
	private File vacinas;
	
	/**
	 * Instancia uma puta
	 * @param name Nome do paciente
	 * @param birth Data de nascimento do pasciente
	 * @param mothername Nome da mãe da puta
	 */
	public Paciente(String name, Date birth, String mothername) {
		this.name = name;
		this.birth = birth;
		this.mothername = mothername;
		regenerateId();
	}
	
	/**
	 * Instancia uma puta informando um id manual
	 * @param id Código de identificação única do paciente
	 * @param name Nome do paciente
	 * @param birth Data de nascimento do pasciente
	 * @param mothername Nome da mãe da puta
	 * @throws Exception Erros nor carregamento do arquivo ou arquivo corrompido
	 */
	public Paciente(long id, String name, Date birth, String mothername) throws Exception {
		this.name = name;
		this.birth = birth;
		this.mothername = mothername;
		this.code = id;
		this.vacinas = new File(ProgramaB.pacvacs + code.toString());
		
		if (!vacinas.exists())
			return;
		
		FileReader fr = new FileReader(vacinas);
		BufferedReader br = new BufferedReader(fr);
		
		String line;
		while((line = br.readLine()) != null){
			if (line.charAt(0) == 0 || line.isEmpty())
				break;
			if (line.charAt(line.length()-1) == '\n')
				line = line.subSequence(0, line.length()-1).toString();
			String parts[] = line.split("\t");
			if (parts.length != 3) {
				br.close();
			    fr.close();
				throw(new Exception("Corrupted database!"));
			}
			
			this.add(new VacinaAplicada(parts[0], Byte.parseByte(parts[1]), Short.parseShort(parts[2])));
	    }
		
	    br.close();
	    fr.close();
	}
	
	/**
	 * Recria a identificação única da puta
	 */
	public void regenerateId () {
		this.vacinas = null;
		File tmp;
		do {
			code = Math.abs(rand.nextLong());
			tmp = new File(ProgramaB.pacvacs + code.toString());
			try {
				if (tmp.createNewFile())
					this.vacinas = tmp;
			} catch (IOException e) {}
		} while (this.vacinas == null);
	}
	
	/**
	 * Obtém uma identificação única da puta
	 * @return Identificação
	 */
	public long getId () {return code;}
	
	/**
	 * Obtém o nome da puta
	 * @return Nome
	 */
	public String getName () {return name;}
	
	/**
	 * Obtém a data de nascimento da puta
	 * @return Data de nascimento
	 */
	public Date getBirth () {return birth;}
	
	/**
	 * Obtém o nome da mãe da puta
	 * @return Nome da mãe
	 */
	public String getMotherName () {return mothername;}
	
	/**
	 * Obtém o nome da mãe da puta
	 * @return Nome da mãe
	 */
	public File getVacFile () {return vacinas;}

	/**
	 * Salva vacians já aplicadas
	 * @return Verdadeiro se não houve erros
	 */
	public boolean saveVac() {
		PrintWriter writer;
		try {
			writer = new PrintWriter(vacinas, "UTF-8");
		} catch (IOException e) {
			return false;
		}
		
		// Escrever cada uma das vacinas no arquivo
		for (VacinaAplicada v: this)
			writer.printf("%s\t%d\t%d\n", v.name, v.dose, v.age);
		
		// Salva e fecha arquivo
		writer.write(0); //EOF (Not needed but interesting)
		writer.close();
		return true;
	}
	
	/**
	 * Retorna a última dose tomada de uma certa vacina
	 * @param vac Vacina procurada
	 * @return O número da última dose tomada
	 */
	public byte getLastDoseNum (Vacina vac) {
		for(VacinaAplicada va : this)
			if(va.name.equals(vac.getName()))
				return va.dose;
		return 0;
	}
	
	/**
	 * Calcula a idade atual do paciente
	 * @return Idade atual do paciente
	 */
	public short getActualAge () {
		Date today = new Date();
		int today_in_months = today.getYear()*12 + today.getMonth();
		int pac_age = birth.getYear()*12 + birth.getMonth();
		return (short)(today_in_months - pac_age);
	}
	
	/**
	 * Aplica uma dose da vacina no paciente
	 * @param vac Vacina a ser aplicada
	 */
	public void applyVac (Vacina vac) {
		short actual_age = getActualAge ();
		for(VacinaAplicada va : this)
			if(va.name.equals(vac.getName())) {
				va.dose++;
				va.age= actual_age;
				return;
			}
		this.add(new VacinaAplicada(vac.getName(), (byte)1, actual_age));
	}
}
