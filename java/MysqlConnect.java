/*
export CLASSPATH=$CLASSPATH:mysql-connector-java-5.1.35-bin.jar
*/

import java.sql.*;

public class MysqlConnect
{
  public static void main(String args[])
  //向屏幕上写字符串"HelloWorld!"
  {
    System.out.println("HelloWorld!");
    try {  
      Class.forName("com.mysql.jdbc.Driver");  
      Connection ct = DriverManager.getConnection(  
        "jdbc:mysql://localhost:3306/tpcc", "root", "");  
      /*      Statement st = ct.createStatement();  
      ResultSet rs = st.executeQuery("select * from users");  
      while(rs.next()){  
        System.out.println("Id: "+ rs.getString(1)+" Name: "+ rs.getString(2));  
        } */
    } catch (Exception e) {
      // TODO: handle exception  
      System.out.println("异常！"+e.toString()); 
    }  
  }
}