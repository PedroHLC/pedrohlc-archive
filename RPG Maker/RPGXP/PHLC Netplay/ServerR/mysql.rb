# Objetos da database

class MySQL_DB
  def initialize(host, user, pass, dbname)
    @sock = Mysql.new(host, user, pass, dbname)
  end
  
  def load_all(table, name, value)
    return @sock.query("SELECT * FROM #{table} WHERE #{name}=#{value}")
  end
  
  def creat(table, name,value)
    @sock.query("INSERT INTO #{table}(#{name}) VALUES(#{value})")
  end
  
  def save(table, name,value, where, is)
    @sock.query("UPDATE #{table} SET #{name}=#{value} WHERE #{where}=#{is}")
  end
  
  def load(table, name, where, is)
    return @sock.query("SELECT #{name} FROM #{table} WHERE #{where}=#{is}")
  end
  
  def exist?(var)
    return true if var.num_rows() >= 1
    return false
  end
  
  def close
    @sock.close
  end
end

class MySQL_Client
  attr_accessor('char_id')
  def initialize
    @uid = 0
    @login = ''
    @pass = ''
    @char_id = 0
    @acc_type = 0
  end
  
  def user_register(login, pass)
    $database.creat('users', "login, pass", "#{login.to_db}, #{pass.to_db}")
  end
  
  def user_login(login, pass)
    userteste = $database.load_all('users', 'login', login.to_db)
    if $database.exist?(userteste)
      userinfo = userteste.fetch_hash
      if userinfo['pass'].to_s != pass
        return 1
      elsif userinfo['loggedin'].to_i == 1
        return 2
      else
        @uid = userinfo['id'].to_i
        @login = login
        @pass = pass
        @acc_type = userinfo['acc_type'].to_i
      end
    else
      user_register(login, pass)
      return user_login(login, pass)
    end
    return 0
  end
  
  def logoff
    @uid = 0
    @login = ''
    @pass = ''
    @char_id = 0
    @acc_type = 0
    $database.save('users', 'loggedin', (0).to_db, 'id', @uid.to_db) if @uid > 0
  end
  
  def user_load(var_name)
    return @uid if var_name == 'id'
    return @login if var_name == 'login'
    return @pass if var_name == 'pass'
    return @acc_type if var_name == 'type'
    return $database.load('users', var_name.to_db, 'id', @uid.to_db).fetch_row().to_s
  end
  
end