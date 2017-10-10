package com.pedrohlc.vac.calendar;

/**
 * Mantém e gerencia uma única Vacina
 * @author Pedro Henrique Lara Campos
 */
public class Vacina {
	
	/*
	 * Protótipos
	 */
	private String name;
	private byte dose;
	private short age[];
	private String disease;
	
	/*
	 * Funções
	 */
	
	/**
	 * Inicializa uma vacina
	 * @param name Nome da Vacina
	 * @param dose Quantidade de doses
	 * @param age Idade de cada dose em meses
	 * @param disease Doença tratada pela vacina
	 * @throws Exception Dados inválidos!
	 */
	public Vacina (String name, byte dose, short age[], String disease) throws Exception {
		this.name = name;
		this.dose = dose;
		this.age = age;
		this.disease = disease;
		if (!this.validate())
			throw (new Exception("Valores de nova vacina inválidos!"));
	}
	
	private boolean validate () {
		return (this.dose <= 3 &&
				this.dose > 0 &&
				age != null &&
				name != null &&
				disease != null &&
				!name.isEmpty() &&
				!disease.isEmpty()
				);
	}
	
	/**
	 * Obtém o nome da vacina
	 * @return Nome da vacina
	 */
	public String getName() {return name;}
	
	/**
	 * Obtém a quantidade de doses da vacina
	 * @return Quantidade de doses da vacina
	 */
	public byte getDose() {return dose;}
	
	/**
	 * Obtém a idade de cada dose em meses da vacina
	 * @return nome Idade de cada dose em meses
	 */
	public short[] getAges() {return age;}
	
	/**
	 * Obtém o nome da doença tratada pela vacina
	 * @return Nome da doença tratada
	 */
	public String getDisease() {return disease;}
	
	/**
	 * Altera o nome da vacina
	 * @param val Novo nome
	 */
	public void setName(String val) {name = val;}
	
	/**
	 * Altera quantidade de doses da vacina
	 * @param val Nova quantidade
	 */
	public void setDose(byte val) {dose = val;}
	
	/**
	 * Altera a idade de cada dose em meses da vacina
	 * @param val Novas idades
	 */
	public void setAges(short[] val) {age = val;}
	
	/**
	 * Altera o nome da doença tratada pela vacina
	 * @param val Novo nome da doença tratada
	 */
	public void setDisease(String val) {disease = val;}
	
	/**
	 * Obtém a idade de cada dose em meses da vacina em texto separado por virgulas
	 * @return nome Idade das doses em meses
	 */
	public String getCommaSepAges() {
		String result = "";
		
		for (int i=0; i < dose-1; i++)
			result += String.valueOf(age[i])+",";
		
		
		result += String.valueOf(age[dose-1]);
		return result;
	}
}
