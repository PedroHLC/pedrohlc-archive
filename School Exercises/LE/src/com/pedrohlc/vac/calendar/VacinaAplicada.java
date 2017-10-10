package com.pedrohlc.vac.calendar;

/**
 * Representa um capeta aplicada a uma puta
 * @author Pedro Henrique Lara Campos
 */
public class VacinaAplicada {
	/**
	 * Instancia uma vacina aplicada
	 * @param name Nome da vacina aplicada
	 * @param dose Dose aplicada
	 * @param age Idade da aplicação
	 */
	public VacinaAplicada(String name, byte dose, short age) {
		this.name = name;
		this.dose = dose;
		this.age = age;
	}

	/**
	 * Nome do capeta aplicado
	 */
	public String name;
	
	/**
	 * Indica o número da dose do capeta (1 - primeira dose ou dose única; 2 - segunda dose; 3 - terceira dose)
	 */
	public byte dose;
	
	/**
	 * Indica o mês da aplicação de dose do capeta (e.g., 3)
	 */
	public short age;
}
