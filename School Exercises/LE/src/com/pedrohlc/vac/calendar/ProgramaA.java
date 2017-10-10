package com.pedrohlc.vac.calendar;

import java.util.Arrays;
import java.util.Scanner;

/**
 * Gerenciador de Vacinas para terminal
 * @author Pedro Henrique Lara Campos
 */
public class ProgramaA {
	private static ListaVacinas LISTA;
	private static String LISTA_FNAME="vacauto.dat";
	private static boolean LISTA_AUTOSAVE=true;
	private static Scanner consolein;
	
	/**
	 * Pergunta ao usuário as informações e cadastra uma nova vacina.
	 */
	private static void newVac () {		
		String vac_name=null, vac_disease=null, tmp=null;
		byte vac_dose=(byte)255;
		short vac_ages[] = null;
		
		while (vac_name==null) {
			System.out.printf ("Lindão, digite o nome da vacina: ");
			tmp = consolein.nextLine();
			if (tmp.isEmpty())
				System.out.printf("Digite algum valor valido!\n");
			else if(LISTA.search(tmp) != null)
				System.out.printf("Capeta já cadastrada!\n");
			else
				vac_name = tmp;
		}
		
		while (vac_dose==(byte)255) {
			System.out.printf ("Gostoso, agora digite a dosagem: ");
			tmp = consolein.nextLine();
			vac_dose = Byte.parseByte(tmp);
			if (vac_dose <= 0 || vac_dose > 3) {
				System.out.printf("Digite algum valor valido (entre 1 e 3)!\n");
				vac_dose = (byte)255;
			}
		}
		
		vac_ages = new short[vac_dose];
		for (byte agi = 0; agi < vac_dose; agi++) {
			vac_ages[agi] = (byte)255; // I really hope valac will optimize this variable
			while (vac_ages[agi]==(byte)255) {
				System.out.printf ("*-* Agora digite a idade da dosagem %d: ", agi+1);
				tmp = consolein.nextLine();
				vac_ages[agi] = Byte.parseByte(tmp);
				if (vac_ages[agi] <= 0 || vac_ages[agi] > 2400) {
					System.out.printf("Digite algum valor valido (entre 1 e 2400)!\n");
					vac_ages[agi]=(byte)255;
				}
			}
		}
		
		while (vac_disease==null) {
			System.out.printf ("Ai mais um pouco, digite a doença sendo tratada: ");
			tmp = consolein.nextLine();
			if (tmp.isEmpty())
				System.out.printf("Digite algum valor valido!\n");
			else
				vac_disease = tmp;
		}
		
		try {
			Arrays.sort(vac_ages);
			Vacina nova = new Vacina(vac_name, vac_dose, vac_ages, vac_disease);
			LISTA.add(nova);
		} catch (Exception e) {
			e.printStackTrace();
			System.out.printf("Vacina não adicionada!");
		}
	}
	
	/**
	 * Lista todas as vacinas
	 */
	private static void lsVac () {
		for (Vacina v: LISTA)
			System.out.printf("%s\t%d\t%s\t%s\n", v.getName(), v.getDose(), v.getCommaSepAges(), v.getDisease());
	}
	
	/**
	 * Pergunta ao usuário vacina e permite ele editar
	 */
	private static void editVac () {
		String vac_name=null;
		Vacina resultado=null;
		while (true) {
			System.out.printf ("Lindão, digite o nome da vacina pra alterar (vazio para sair): ");
			vac_name = consolein.nextLine();
			if (vac_name.isEmpty())
				return;
			else if((resultado = LISTA.search(vac_name)) == null)
				System.out.printf("Nenhuma vacina encontrada com o nome: %s\n", vac_name);
			else break;
		}
		
		System.out.printf("*Vacina escolhida: %s\t%d\t%s\t%s\n", resultado.getName(), resultado.getDose(), resultado.getCommaSepAges(), resultado.getDisease());
		
		String vac_disease=null, tmp=null;
		byte vac_dose=(byte)255;
		short vac_ages[] = null;
		
		while (vac_dose==(byte)255) {
			System.out.printf ("Gostoso, agora digite a dosagem: ");
			tmp = consolein.nextLine();
			vac_dose = Byte.parseByte(tmp);
			if (vac_dose <= 0 || vac_dose > 3) {
				System.out.printf("Digite algum valor valido (entre 1 e 3)!\n");
				vac_dose = (byte)255;
			}
		}
		
		vac_ages = new short[vac_dose];
		for (byte agi = 0; agi < vac_dose; agi++) {
			vac_ages[agi] = (byte)255; // I really hope valac will optimize this variable
			while (vac_ages[agi]==(byte)255) {
				System.out.printf ("*-* Agora digite a idade da dosagem %d: ", agi+1);
				tmp = consolein.nextLine();
				vac_ages[agi] = Byte.parseByte(tmp);
				if (vac_ages[agi] <= 0 || vac_ages[agi] > 2400) {
					System.out.printf("Digite algum valor valido (entre 1 e 2400)!\n");
					vac_ages[agi]=(byte)255;
				}
			}
		}
		
		while (vac_disease==null) {
			System.out.printf ("Ai mais um pouco, digite a doença sendo tratada (vazio para manter o original): ");
			tmp = consolein.nextLine();
			if (tmp.isEmpty())
				vac_disease = resultado.getDisease();
			else
				vac_disease = tmp;
		}
		
		resultado.setDose(vac_dose);
		resultado.setAges(vac_ages);
		resultado.setDisease(vac_disease);
		System.out.printf("Atualizada com sucesso!");
	}
	
	/**
	 * Exclui uma vacina escolhida pelo usuário
	 */
	private static void rmVac () {
		String vac_name=null;
		Vacina resultado=null;
		while (true) {
			System.out.printf ("Lindão, digite o nome da vacina (vazio para sair): ");
			vac_name = consolein.nextLine();
			if (vac_name.isEmpty())
				return;
			else if((resultado = LISTA.search(vac_name)) == null)
				System.out.printf("Nenhuma vacina encontrada com o nome: %s\n", vac_name);
			else break;
		}
		LISTA.remove(resultado);
		System.out.printf("Apagado com sucesso!");
	}
	
	/**
	 * Executa o programa 
	 * @param args Vetor de strings que pode incluir o nome do arquivo com que o programa irá trabalhar
	 */
	public static void main(String[] args) {
		System.out.printf(
				"# -------------------------------------------------"+"\n"+
				"# Programa de gerenciamento de vacinas"+"\n"+
				"# To Léo"+"\n"+
				"# Version 1.0.0-1"+"\n"+
				"# -------------------------------------------------"+"\n"+
				"\n"
		);
		
		if (args.length > 0 && args[0] != null && !args[0].isEmpty())
			LISTA_FNAME = args[0];
		else
			System.out.printf("Nome do arquivo não informado usando o padrão: %s\n\n", LISTA_FNAME);
		
		try {
			LISTA = new ListaVacinas(LISTA_FNAME);
		} catch (Exception e) {
			e.printStackTrace();
			return;
		}
		
		consolein = new Scanner(System.in);
		char chosenopt;
		
		do {
			System.out.printf(
					"O capeta do programa precias que vc escolha uma das seguintes opções:"+"\n"+
					"\t\t1\tCadastrar um demônio"+"\n"+
					"\t\t2\tListar todos os demônios"+"\n"+
					"\t\t3\tAlterar um demônio"+"\n"+
					"\t\t4\tExcluir um demônio"+"\n"+
					"\t\tA\t%s o salvamento automático"+"\n"+
					"\t\tE\tSalvar o inferno e sair"+"\n"+
					"\t\tQ\tSair do inferno sem salvar"+"\n"+
					"Que opção tu vais selecionar: ",
					(LISTA_AUTOSAVE ? "Desabilitar" : "Habilitar")
			);
			chosenopt = consolein.nextLine().charAt(0);
			
			switch(chosenopt){
			case 'Q': // Faz nada para sair
				break;
			case 'E':
				LISTA.save (LISTA_FNAME);
				chosenopt = 'Q';
				break;
			case 'A':
				LISTA_AUTOSAVE = !LISTA_AUTOSAVE;
				break;
			case '1':
				newVac ();
				break;
			case '2':
				lsVac ();
				break;
			case '3':
				editVac ();
				break;
			case '4':
				rmVac ();
				break;
			default:
				System.out.printf("~ Opção '%c' não reconhecida. Tente novamente!\n\n", chosenopt);
			}
			// Salvar o inferno
			if(LISTA_AUTOSAVE)
				LISTA.save (LISTA_FNAME);
		} while(chosenopt != 'Q');
		
		consolein.close ();
	}
}
