package application;

import java.sql.Connection;
import java.sql.DriverManager;

import javax.swing.JOptionPane;

public class MYSQLconnection {
	
	
	public static Connection ConnectDatabase() {
		
		try {
			Class.forName("com.mysql.cj.jdbc.Driver");
			Connection conn = DriverManager.
					getConnection("jdbc:mysql://localhost/platforma3?user=root&password=!GeorgeLabBD1234");
			//JOptionPane.showMessageDialog(null, "Connection OK");
			return conn;
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
			return null;
		}
		
	}
}
