<?php
function inerror(){
	header( 'Location: http://72.21.214.143' . $_SERVER['REDIRECT_URL'] );
}
function main(){
	$mysql_con = mysql_connect('db4free.net', 'amineskins', 'amineskins');
	if (!$mysql_con){
		inerror();
		mysql_close($mysql_con);
		return;
	}
	
	mysql_select_db('amineskins', $mysql_con);
	
	$nick = str_replace (array('/minecraftskins/', '.png') , '', strtolower($_SERVER['REDIRECT_URL']));
	
	$mysql_quest = "SELECT url FROM players WHERE nick='" . $nick . "'";
	$mysql_res = mysql_query($mysql_quest, $mysql_con);
	
        if($mysql_res != false)
          if(mysql_num_rows($mysql_res) >= 1)
            while($mysql_row = mysql_fetch_array($mysql_res))
              header( 'Location: '.$mysql_row['url'] );
	  else{
	    inerror();
	    mysql_close($mysql_con);
	    return;
	  }
	else{
	  inerror();
	  mysql_close($mysql_con);
	  return;
	}
	
	mysql_close($mysql_con);
}
main();
?>