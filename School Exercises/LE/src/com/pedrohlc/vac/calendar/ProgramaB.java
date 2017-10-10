package com.pedrohlc.vac.calendar;

import java.io.File;
import java.text.ParseException;
import java.util.Date;
import java.util.Scanner;

/**
 * Gerenciador de Pacientes e Doses para terminal
 * @author Pedro Henrique Lara Campos
 */
public class ProgramaB {
	private static ListaVacinas VACLISTA;
	private static String VACLISTA_FNAME="vacauto.dat";
	private static ListaPacientes PACLISTA;
	private static String PACLISTA_FNAME="pacauto.dat";
	private static boolean PACLISTA_AUTOSAVE=true;
	private static Scanner consolein;
	
	/**
	 * Pasta de vacinas do paciente
	 */
	public static final String pacvacs="./pacientes/";
	
	/**
	 * Pergunta ao usuário as informações e cadastra uma nova vacina.
	 */
	private static void newPac () {		
		String pac_name=null, pac_mother=null, tmp=null;
		Date pac_birth=null;
		
		while (pac_name==null) {
			System.out.printf ("Lindão, digite o nome do paciente: ");
			tmp = consolein.nextLine();
			if (tmp.isEmpty())
				System.out.printf("Digite algum valor valido!\n");
			else
				pac_name = tmp;
		}
		
		while (pac_mother==null) {
			System.out.printf ("Ai mais um pouco, digite o nome da mãe: ");
			tmp = consolein.nextLine();
			if (tmp.isEmpty())
				System.out.printf("Digite algum valor valido!\n");
			else
				pac_mother = tmp;
		}
		
		while (pac_birth==null) {
			System.out.printf ("Ai mais um pouco, digite a data de nascimento: ");
			tmp = consolein.nextLine();
			if (tmp.isEmpty())
				System.out.printf("Digite algum valor valido!\n");
			else {
				try {
					pac_birth = ListaPacientes.formatDate(tmp);
				} catch (ParseException e) {
					System.out.printf("Digite uma data no formato \"dd/mm/yyyy\"!\n");
				}
			}
		}
		
		try {
			Paciente novo = new Paciente(pac_name, pac_birth, pac_mother);
			PACLISTA.add(novo);
			System.out.printf("Paciente adicionado, identificação: %d\n", novo.getId());
		} catch (Exception e) {
			e.printStackTrace();
			System.out.printf("Paciente não adicionado!");
		}
	}
	
	/**
	 * Cadastra aplicação de uma vacina
	 */
	private static void newVacToDo () {
		Long pac_id=0L;
		Paciente pac_resultado=null;
		while (true) {
			System.out.printf ("Lindão, digite a id do paciente: ");
			pac_id = Long.parseLong(consolein.nextLine());
			if (pac_id <= 0)
				return;
			else if((pac_resultado = PACLISTA.search(pac_id)) == null)
				System.out.printf("Nenhum paciente encontrada com o id: %s\n", pac_id);
			else break;
		}
		if (pac_resultado==null) return;
		
		String vac_name=null;
		Vacina vac_resultado=null;
		while (true) {
			System.out.printf ("Lindão, digite o nome da vacina pra tomar (vazio para sair): ");
			vac_name = consolein.nextLine();
			if (vac_name.isEmpty())
				return;
			else if((vac_resultado = VACLISTA.search(vac_name)) == null)
				System.out.printf("Nenhuma vacina encontrada com o nome: %s\n", vac_name);
			else break;
		}
		if (vac_resultado==null) return;
		
		byte lastDose = pac_resultado.getLastDoseNum(vac_resultado);
		if (lastDose >= vac_resultado.getDose()) {
				System.out.printf("O paciente já conclui todas as doses dessa vacina anteriormente.");
				return;
		}
		
		pac_resultado.applyVac(vac_resultado);
		System.out.printf("O paciente já pode prosseguir e tomar essa vacina!");
	}
	
	/**
	 * Lista as vacinas pendentes
	 */
	private static void lsMissingVac () {
		Long pac_id=0L;
		Paciente pac_resultado=null;
		while (true) {
			System.out.printf ("Lindão, digite a id do paciente: ");
			pac_id = Long.parseLong(consolein.nextLine());
			if (pac_id <= 0)
				return;
			else if((pac_resultado = PACLISTA.search(pac_id)) == null)
				System.out.printf("Nenhum paciente encontrada com o id: %s\n", pac_id);
			else break;
		}
		if (pac_resultado==null) return;
		
		short pac_age = pac_resultado.getActualAge();
		byte last_dose;
		for (Vacina v: VACLISTA)
			if ((last_dose = pac_resultado.getLastDoseNum(v)) < v.getDose())
				if (pac_age >= v.getAges()[last_dose])
					System.out.printf ("O paciente precisa tomar a dose %d da %s\n", last_dose+1, v.getName());
	}
	
	/**
	 * Lista as vacinas tomadas
	 */
	private static void lsDoneVac () {
		Long pac_id=0L;
		Paciente pac_resultado=null;
		while (true) {
			System.out.printf ("Lindão, digite a id do paciente: ");
			pac_id = Long.parseLong(consolein.nextLine());
			if (pac_id <= 0)
				return;
			else if((pac_resultado = PACLISTA.search(pac_id)) == null)
				System.out.printf("Nenhum paciente encontrada com o id: %s\n", pac_id);
			else break;
		}
		if (pac_resultado==null) return;
		
		System.out.println("NOME DA VACINA - ÚLTIMA DOSE APLICADA");
		for (VacinaAplicada va: pac_resultado)
			System.out.printf("%s - %d\n", va.name, va.dose);
	}
	
	/**
	 * Executa o programa 
	 * @param args Vetor de strings que pode incluir o nome do arquivo com que o programa irá trabalhar
	 */
	public static void main(String[] args) {
		new File(pacvacs).mkdirs();
		System.out.printf(
				"# -------------------------------------------------"+"\n"+
				"# Programa de gerenciamento de pacientes e doses"+"\n"+
				"# To Léo"+"\n"+
				"# Version 1.0.0-1"+"\n"+
				"# -------------------------------------------------"+"\n"
		);
		
		if (args.length > 1 && args[1] != null && !args[1].isEmpty())
			VACLISTA_FNAME = args[1];
		else
			System.out.printf("Nome do arquivo de vacinas não informado usando o padrão: %s\n\n", VACLISTA_FNAME);
		
		if (args.length > 0 && args[0] != null && !args[0].isEmpty())
			PACLISTA_FNAME = args[0];
		else
			System.out.printf("Nome do arquivo de pacientes não informado usando o padrão: %s\n\n", PACLISTA_FNAME);
		
		try {
			PACLISTA = new ListaPacientes(PACLISTA_FNAME);
			VACLISTA = new ListaVacinas(VACLISTA_FNAME);
		} catch (Exception e) {
			e.printStackTrace();
			return;
		}
		
		consolein = new Scanner(System.in);
		char chosenopt;
		
		do {
			System.out.printf("\n"+
					"O capeta do programa precias que vc escolha uma das seguintes opções:"+"\n"+
					"\t\t1\tCadastrar um receptaculo"+"\n"+
					"\t\t2\tAgendar receptaculo para um demônios"+"\n"+
					"\t\t3\tListar reservas"+"\n"+
					"\t\t4\tListar reservas finalizadas"+"\n"+
					"\t\tA\t%s o salvamento automático"+"\n"+
					"\t\tE\tSalvar o inferno e sair"+"\n"+
					"\t\tQ\tSair do inferno sem salvar"+"\n"+
					"Que opção tu vais selecionar: ",
					(PACLISTA_AUTOSAVE ? "Desabilitar" : "Habilitar")
			);
			chosenopt = consolein.nextLine().charAt(0);
			
			switch(chosenopt){
			case 'Q': // Faz nada para sair
				break;
			case 'E':
				PACLISTA.save (PACLISTA_FNAME);
				chosenopt = 'Q';
				break;
			case 'A':
				PACLISTA_AUTOSAVE = !PACLISTA_AUTOSAVE;
				break;
			case '1':
				newPac ();
				break;
			case '2':
				newVacToDo ();
				break;
			case '3':
				lsMissingVac ();
				break;
			case '4':
				lsDoneVac ();
				break;
			default:
				System.out.printf("~ Opção '%c' não reconhecida. Tente novamente!\n\n", chosenopt);
			}
			// Salvar o inferno
			if(PACLISTA_AUTOSAVE)
				PACLISTA.save (PACLISTA_FNAME);
		} while(chosenopt != 'Q');
		
		consolein.close ();
	}
}
