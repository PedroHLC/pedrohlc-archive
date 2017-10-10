print "Insira o nome do arquivo: "
$inputpath = "00001.vcf"#gets
$inf =  File.new($inputpath, "rb")
$outf =  File.new($inputpath+".sql", "wb")

$outf.write("CREATE TABLE registros("+
  "nome varchar(60) not null,"+
  "celular varchar(15) default 'null',"+
  "email varchar(60) default 'null' );\n")

class Contact
  @nome = nil;
  @celular = 'null';
  @email = 'null';
  def initialize
    @nome = 'null'
  end
  def setname(name)
    @nome = name
  end  
  def setcellphone(cellphone)
    @celular = cellphone
  end
  def setemail(email)
    @email = email
  end
  def isvalid?
    return (@nome != nil && @nome.to_s.size > 0 && @celular.to_s != 'null' && @celular.to_s.size > 1)
  end
  def tosqlvals
    return "'#{@nome}', '#{@celular}', '#{@email}'"
  end
end

$contacts = []
$actual_contact = nil
$inf.read.each_line{|line|
  case line
  when /END:VCARD/
    if $actual_contact != nil
	$contacts.push($actual_contact.dup)
	$actual_contact = nil
    end
  when /BEGIN:(.*)/
    $actual_contact = Contact.new
  when /VERSION:(.*)/
    #do nothing
  when /N:(.*)/
    n = $1.strip
    $actual_contact.setname n if n != '2.1'
  when /EMAIL:(.*)/
    $actual_contact.setemail $1.strip if $actual_contact != nil
  when /TEL;CELL;PREF:(.*)/
    $actual_contact.setcellphone $1.strip if $actual_contact != nil
  end
}

$inf.close

$contacts.each{|contact|
  next if contact == nil
  if contact.isvalid?
    $outf.write "INSERT INTO registros VALUES("
    $outf.write contact.tosqlvals
    $outf.write ");\n"
  end
}

$outf.close