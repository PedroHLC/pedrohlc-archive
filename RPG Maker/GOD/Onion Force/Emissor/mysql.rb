# Objetos da database

class MySQL_DB
  def initialize(host, user, pass, dbname)
    @sock = Mysql.new(host, user, pass, dbname)
  end
  
  def load_all(table, name, value)
    return @sock.query("SELECT * FROM #{table} WHERE #{name}=#{value.to_db}")
  end
  
  def creat(table, name,value)
    @sock.query("INSERT INTO #{table}(#{name}) VALUES(#{value.to_db})")
  end
  
  def save(table, name,value, where, is)
    @sock.query("UPDATE #{table} SET #{name}=#{value.to_db} WHERE #{where}=#{is.to_db}")
  end
  
  def load(table, name, where, is)
    return @sock.query("SELECT #{name} FROM #{table} WHERE #{where}=#{is.to_db}")
  end
  
  def exist(var)
    return true if var.num_rows() < 1
    return false
  end
  
  def close
    @sock.close
  end
end

class MySQL_Client
  def initialize
    @login = ''
    @pass = ''
    @char_id = 0
  end
  
  def user_register(login, pass)
    $database.creat('users', 'login, pass', "#{login.to_db}, #{pass.to_db}")
  end
  
  def user_login(login, pass)
    userinfo = $database.load_all('users', 'login', login)
    userinfo.fetch_hash
    if $database.exist?(userinfo)
      if userinfo['pass'].to_s != pass
        return []
      end
    else
      user_register(login, pass)
    end
  end
end