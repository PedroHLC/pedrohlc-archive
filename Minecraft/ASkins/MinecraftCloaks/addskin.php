<?php
function inerror($cause){
	echo( 'Ops, algo deu errado, parece que ' . $cause . "...\n<br />" );
}
function validate_url($filename){
	$size = getimagesize($filename);
	if($size[2] != IMAGETYPE_PNG){
		inerror('sua imagem não é do tipo PNG ou não foi encontrada.');
		echo('Veja este exeplo de url: http://s3.amazonaws.com/MinecraftCloaks/Steve.png'."\n<br />");
		return 1;
	}
	if(($size[0] != 64) or ($size[1] != 32)){
		inerror('sua imagem não tem tamanho de uma capa.');
		echo('Veja este exeplo de imagem: http://s3.amazonaws.com/MinecraftCloaks/Steve.png'."\n<br />");
		return 2;
	}
	return 0;
}
function main(){
	if(!isset($_POST['nick'])){
		inerror('seu nick está vazio');
		return;
	}$nick = strtolower($_POST['nick']);
	
	if(!isset($_POST['url'])){
		inerror('sua url está vazia');
		return;
	}$url = $_POST['url'];
	
	$url_validation = validate_url($url);
	if($url_validation != 0){
		return;
	}
	
	$mysql_con = mysql_connect('db4free.net', 'aminecloaks', 'aminecloaks');
	if (!$mysql_con){
		inerror('não foi possível conectar na DB');
		return;
	}
	
	mysql_select_db('aminecloaks', $mysql_con);
	
	$mysql_quest = "INSERT INTO players VALUES ('" . $nick . "', '" . $url . "');";
	$mysql_res = mysql_query($mysql_quest, $mysql_con);
	
        if($mysql_res != false)
          echo( 'Done *-* - Inserido.' );
	else{
		$mysql_quest = "UPDATE players SET url=\"" . $url . "\" WHERE nick=\"" . $nick . "\";";
		$mysql_res = mysql_query($mysql_quest, $mysql_con);
		if($mysql_res != false)
			echo( 'Done *-* - Atualizado.' );
		else{
			inerror('o comando para inserir na DB falhou');
			mysql_close($mysql_con);
			return;
		}
	}
	
	mysql_close($mysql_con);
}
main();
?>