package application;

import java.awt.GridLayout;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.net.URL;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.time.Instant;
import java.time.ZoneId;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;
import java.util.ResourceBundle;

import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.DatePicker;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.image.Image;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class Controller {
	
	@FXML
    private TextField adressCreate;

    @FXML
    private TextField cnpCreate;

    @FXML
    private TextField contractCreate;

    @FXML
    private Button createButton;

    @FXML
    private TextField emailCreate;

    @FXML
    private TextField emailLogin;

    @FXML
    private TextField firstNameCreate;

    @FXML
    private TextField ibanCreate;

    @FXML
    private TextField lastNameCreate;

    @FXML
    private Button loginButton;

    @FXML
    private AnchorPane pageCreate;

    @FXML
    private AnchorPane pageLogin;

    @FXML
    private PasswordField passwordCreate;

    @FXML
    private PasswordField passwordLogin;

    @FXML
    private ComboBox<String> roleCreate;

    @FXML
    private ComboBox<String> roleLogin;

    @FXML
    private TextField telCreate;
    
    @FXML
	private Button logoutAdmin;
    
    @FXML
	private Button logoutStudent;
    
    @FXML
	private Button logoutProfesor;
    
    @FXML
	private Button logoutSuperadmin;
    
    @FXML
    private Button datePersonaleAdmin;
    
    @FXML
    private AnchorPane adminPanel;
    
    @FXML
    private AnchorPane studentPanel;
    
    @FXML
    private Button dateAdmin;

    @FXML
    private Button dateProfesor;

    @FXML
    private Button dateStudent;

    @FXML
    private Button dateSuperadmin;

    @FXML
    private AnchorPane superadminPanel;
    
    @FXML
    private AnchorPane profesorPanel;
    
    @FXML
    private Button dataUpdateAdmin;
    
    @FXML
    private Button backDataUpdate;
    
    @FXML
    private AnchorPane updateAdminPanel;
    
    @FXML
    private AnchorPane updateSuperadminPanel;
    
    @FXML
    private TextField updateAdresa;

    @FXML
    private TextField updateCNP;

    @FXML
    private TextField updateEmail;

    @FXML
    private TextField updateFirstName;

    @FXML
    private TextField updateIBAN;

    @FXML
    private TextField updateID;

    @FXML
    private TextField updateLastName;

    @FXML
    private TextField updateNumarContract;

    @FXML
    private PasswordField updatePassword;

    @FXML
    private TextField updateTel;
    
    @FXML
    private TextField updateAdresa1;

    @FXML
    private TextField updateCNP1;

    @FXML
    private TextField updateEmail1;

    @FXML
    private TextField updateFirstName1;

    @FXML
    private TextField updateIBAN1;

    @FXML
    private TextField updateID1;

    @FXML
    private TextField updateLastName1;

    @FXML
    private TextField updateNumarContract1;

    @FXML
    private PasswordField updatePassword1;

    @FXML
    private TextField updateTel1;
    
    @FXML
    private Button signUpCourseButton;
    
    @FXML
    private Button giveUpCourseButton;
    
    @FXML
    private Button getStudentGradesButton;
    
    @FXML
    private Button joinGroupButton;
    
    @FXML
    private Button viewGroupMembersButton;
    
    @FXML
    private AnchorPane addActivityPane;
    
    @FXML
    private Button addActivityButton;
    
    @FXML
    private TextField titluActivitate;
    
    @FXML
    private DatePicker dataActivitate;
    
    @FXML
    private TextField durataActivitate;
    
    @FXML
    private TextField numarMinim;
    
    @FXML
    private Button addActivityOptionButton;
    
    @FXML
    private Button backAddActivityButton;
    
    @FXML
    private Label printStudentName;
    
    @FXML
    private Label printAdminName;

    @FXML
    private Label printProfesorName;

    @FXML
    private Label printSuperadminName;
    
    @FXML
    private Button showSendMessageButton;
    
    @FXML
    private Button sendMessageButton;
    
    @FXML
    private Button backSendMessageButton;
    
    @FXML
    private TextArea textMesaj;
    
    @FXML
    private AnchorPane sendMessagePane;
    
    @FXML
    private Button viewMessageButton;
    
    @FXML
    private Label showMessageLabel;
    
    @FXML
    private Button setPercButton;
    
    @FXML
    private Button addProgButton;
    
    @FXML
    private Button showAddProgButton;
    
    @FXML
    private Button backAddProgButton;
    
    @FXML
    private DatePicker dataProgramare;
    
    @FXML
    private TextField oraProgramare;
    
    @FXML
    private TextField tipProgramare;
    
    @FXML
    private AnchorPane addProgPane;
    
    @FXML
    private AnchorPane cataloguePane;
    
    @FXML
    private TableView<StudentData> tableCatalogue;
    
    @FXML
    private Button seeCatalogueButton;
    
    @FXML
    private Button hideCatalogueButton;
    
    @FXML
    private TableColumn<StudentData, String> firstNameColumn;
    
    @FXML
    private TableColumn<StudentData, String> lastNameColumn;
    
    @FXML
    private TableColumn<StudentData, String> materieColumn;
    
    @FXML
    private TableColumn<StudentData, String> tipActivitateColumn;
    
    @FXML
    private TableColumn<StudentData, Float> notaColumn;
    
    @FXML
    private Button addGradeButton;
    
    @FXML
    private Button showGradePane;
    
    @FXML
    private Button hideGradePane;
    
    @FXML
    private AnchorPane addGradePane;
    
    @FXML
    private TextField addGradeLastNameField;
    
    @FXML
    private TextField addGradeFirstNameField;
    
    @FXML
    private TextField addGradeActivitateField;
    
    @FXML
    private TextField addGradeField;
    
    @FXML
    private AnchorPane deleteAdminPanel;
    
    @FXML
    private AnchorPane deleteSuperadminPanel;
    
    @FXML
    private TextField adminDelete;
    
    @FXML
    private TextField superadminDelete;
    
    @FXML
    private Button adminDeleteBack;
    
    @FXML
    private Button superadminDeleteBack;
    
    @FXML
    private Button adminDeleteButton;
    
    @FXML
    private Button superadminDeleteButton;
    
    @FXML
    private Button adminShowDeleteButton;
    
    @FXML
    private Button superadminShowDeleteButton;
    
    @FXML
    private AnchorPane seeAllDataAdminPanel;
    
    @FXML
    private AnchorPane seeAllDataSuperadminPanel;
    
    @FXML
    private TextField adminShowDataNume;
    
    @FXML
    private TextField adminShowDataPrenume;
    
    @FXML
    private TextField superadminShowDataNume;
    
    @FXML
    private TextField superadminShowDataPrenume;
    
    @FXML
    private Button adminShowDataBack;
    
    @FXML
    private Button superadminShowDataBack;
    
    @FXML
    private Button adminShowDataButton;
    
    @FXML
    private Button superadminShowDataButton;
    
    @FXML
    private Button adminShowDataPanelButton;
    
    @FXML
    private Button superadminShowDataPanelButton;
    
    @FXML
    private Button adminShowStudentData;
    
    @FXML
    private Button adminShowProfData;
    
    @FXML
    private Button superadminShowStudentData;
    
    @FXML
    private Button superadminShowProfData;
    
    @FXML
    private Button superadminShowAdminData;
    
    @FXML
    private AnchorPane assPane;
    
    @FXML
    private Button adminShowAssig;
    
    @FXML
    private Button superadminShowAssig;
    
    @FXML
    private Button assigBack;
    
    @FXML
    private TextField numeAss;
    
    @FXML
    private TextField prenumeAss;
    
    @FXML
    private TextField materieAss;
    
    @FXML
    private TextField procentajCurs;
    
    @FXML
    private TextField procentajSeminar;
    
    @FXML
    private TextField procentajLab;
    
    @FXML
    private TextField maxStud;
    
    @FXML
    private Button assButton;
    
    @FXML
    private CheckBox cbCurs;
    
    @FXML
    private CheckBox cbSeminar;
    
    @FXML
    private CheckBox cbLab;
    
    @FXML
    private AnchorPane csPane;
    
    @FXML
    private Button showCS;
    
    @FXML
    private TextField materieCS;
    
    @FXML
    private TableView<CSData> tableCS;
    
    @FXML
    private Button adminSeeCSPane;
    
    @FXML
    private Button superadminSeeCSPane;
    
    @FXML
    private Button backCSPane;
    
    @FXML
    private TableColumn<CSData, String> firstNameColumnCS;
    
    @FXML
    private TableColumn<CSData, String> lastNameColumnCS;
    
    @FXML
    private Label studentTodayLabel;
    
    @FXML
    private Label profTodayLabel;
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    private String emailCopy;
    
    private String roleCopy;
	
    private String role;
    
    Connection conn = null;
    ResultSet rs = null;
    PreparedStatement pst = null;
    
	
    public void loginPageShow(ActionEvent event) {
		pageLogin.setVisible(true);
		pageCreate.setVisible(false);
		lastNameCreate.clear();
		firstNameCreate.clear();
		emailCreate.clear();
		passwordCreate.clear();
		cnpCreate.clear();
		adressCreate.clear();
		telCreate.clear();
		ibanCreate.clear();
		contractCreate.clear();
		roleCreate.getSelectionModel().clearSelection();
		roleCreate.setPromptText("Alegeti rolul"); // nici metoda asta nu merge, ramane de vazut
	}	

    public void createPageShow(ActionEvent event) {
		pageCreate.setVisible(true);
		pageLogin.setVisible(false);
	}
	
	@FXML
	private void login(ActionEvent event) throws Exception {
		conn = MYSQLconnection.ConnectDatabase();
		String sql = "Select * from users where email = ? and parola = ? ";
		try {
			pst = conn.prepareStatement(sql);
			pst.setString(1, emailLogin.getText());
			pst.setString(2, passwordLogin.getText());
			// pst.setString(3, roleLogin.getValue().toString());
			//roleCopy = roleLogin.getValue().toString();
			//emailCopy = emailLogin.getText();
			rs = pst.executeQuery();
			
			if(rs.next())
			{
				
				JOptionPane.showMessageDialog(null, "Autentificare reusita!");
				
				String getRole = "select rol from users where email = ? ";
				PreparedStatement gst = conn.prepareStatement(getRole);
				gst.setString(1, emailLogin.getText());
				ResultSet grs = gst.executeQuery();
				role = "";
				
				if(grs.next())
				{
					role = grs.getString("rol");
				}
				
				String getFirstName = "select prenume from users where email = ? ";
				PreparedStatement nst = conn.prepareStatement(getFirstName);
				nst.setString(1, emailLogin.getText());
				ResultSet nrs = nst.executeQuery();
				String name = "";
				
				if(nrs.next())
				{
					name = nrs.getString("prenume");
				}
				
				String getLastName = "select nume from users where email = ? ";
				PreparedStatement fst = conn.prepareStatement(getLastName);
				fst.setString(1, emailLogin.getText());
				ResultSet frs = fst.executeQuery();
				
				if(frs.next())
				{
					name += " " + frs.getString("nume");
				}
				
				name += "! (" + role + ")";
				
				if(role.equals("admin"))
				{
					pageLogin.setVisible(false);
					adminPanel.setVisible(true);
					printAdminName.setText(name);
				}
				
				if(role.equals("superadmin"))
				{
					pageLogin.setVisible(false);
					superadminPanel.setVisible(true);
					printSuperadminName.setText(name);
				}
				
				if(role.equals("student"))
				{				
					pageLogin.setVisible(false);
					studentPanel.setVisible(true);
					printStudentName.setText(name);
					viewToday();
				}
				
				if(role.equals("profesor"))
				{
					pageLogin.setVisible(false);
					profesorPanel.setVisible(true);
					printProfesorName.setText(name);
					viewToday();
				}
			}
			
			else
				JOptionPane.showMessageDialog(null, "Autentificare esuata!");
				
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
			e.printStackTrace();
		}
	}
	
	public void create(ActionEvent event) {
		conn = MYSQLconnection.ConnectDatabase();
		String sql = "insert into users (nume, prenume, CNP, adresa, telefon, email, IBAN, nr_contract, parola, rol) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
		try {
			pst = conn.prepareStatement(sql);
			pst.setString(1, lastNameCreate.getText());
			pst.setString(2, firstNameCreate.getText());
			pst.setString(3, cnpCreate.getText());
			pst.setString(4, adressCreate.getText());
			pst.setString(5, telCreate.getText());
			pst.setString(6, emailCreate.getText());
			pst.setString(7, ibanCreate.getText());
			pst.setString(8, contractCreate.getText());
			pst.setString(9, passwordCreate.getText());
			pst.setString(10, roleCreate.getValue().toString());
			pst.execute();
			
			JOptionPane.showMessageDialog(null, "Cont creat cu succes!");
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
	}
	
	@FXML
	private void backAdmin(ActionEvent event) {
		try {
			pageLogin.setVisible(true);
			adminPanel.setVisible(false);
			emailLogin.clear();
			passwordLogin.clear();
			roleLogin.valueProperty().setValue("Alegeti rolul"); // nu afiseaza textu asta in combobox, idk might remove alegeti rolul de tot sincer
			
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
	}
	
	@FXML
	private void backStudent(ActionEvent event) {
		try {
			pageLogin.setVisible(true);
			studentPanel.setVisible(false);
			emailLogin.clear();
			passwordLogin.clear();
			roleLogin.valueProperty().setValue("Alegeti rolul"); 
			
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
	}
	
	@FXML
	private void backProfesor(ActionEvent event) {
		try {
			pageLogin.setVisible(true);
			profesorPanel.setVisible(false);
			emailLogin.clear();
			passwordLogin.clear();
			roleLogin.valueProperty().setValue("Alegeti rolul"); 
			
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
	}
	
	@FXML
	private void backSuperadmin(ActionEvent event) {
		try {
			pageLogin.setVisible(true);
			superadminPanel.setVisible(false);
			emailLogin.clear();
			passwordLogin.clear();
			roleLogin.valueProperty().setValue("Alegeti rolul"); 
			
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
	}

	@FXML
	private void showDatePersonale(ActionEvent event) {
		conn = MYSQLconnection.ConnectDatabase();
		String sql = "select nume, prenume, CNP, adresa, telefon, email, IBAN, nr_contract from users where email = ? ";
		try {			 
			pst = conn.prepareStatement(sql);
			pst.setString(1, emailLogin.getText());
			rs = pst.executeQuery();
				 
			while(rs.next())
			{
				String lastName = rs.getString("nume");
				String firstName = rs.getString("prenume");
				String cnp = rs.getString("CNP");
				String adresa = rs.getString("adresa");
				String telefon = rs.getString("telefon");
				String email = rs.getString("email");
				String iban = rs.getString("IBAN");
				String numarContract = rs.getString("nr_contract");
				
			    JOptionPane.showMessageDialog(null, "Nume: " + lastName + " " + firstName + "\nCNP: " 
			    		+ cnp + "\nAdresa: " + adresa + "\nTelefon: " + telefon + 
			    		"\nEmail: " + email + "\nIBAN: " + iban + "\nNumar contract: " + numarContract, "Date personale", 1);
				       
			}
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
	}
	
	public void updatePanelShow(ActionEvent event) {
		if(role.equals("admin"))
		{
			updateAdminPanel.setVisible(true);
			//adminPanel.setVisible(false);
		}
		else if(role.equals("superadmin"))
		{
			updateSuperadminPanel.setVisible(true);
			//adminPanel.setVisible(false);
		}
		
	}
	
	public void updateDatePersonaleAdmin(ActionEvent event) {
		conn = MYSQLconnection.ConnectDatabase();
		
		String sql1 = "update users set nume = ? where id_user = ? and rol != 'superadmin' and rol != 'admin' ";
		String sql2 = "update users set prenume = ? where id_user = ? and rol != 'superadmin' and rol !='admin' "; 
		String sql3 = "update users set cnp = ? where id_user = ? and rol != 'superadmin' and rol != 'admin' ";
		String sql4 = "update users set adresa = ? where id_user = ? and rol != 'superadmin' and rol !='admin' "; 
		String sql5 = "update users set telefon = ? where id_user = ? and rol != 'superadmin' and rol != 'admin' ";
		String sql6 = "update users set email = ? where id_user = ? and rol != 'superadmin' and rol !='admin' "; 
		String sql7 = "update users set iban = ? where id_user = ? and rol != 'superadmin' and rol != 'admin' ";
		String sql8 = "update users set nr_contract = ? where id_user = ? and rol != 'superadmin' and rol !='admin' "; 
		String sql9 = "update users set parola = ? where id_user = ? and rol != 'superadmin' and rol != 'admin' ";
		
		try {
			String role = "";
			String check = "select rol from users where id_user = ? ";
			PreparedStatement checkPst = conn.prepareStatement(check);
			checkPst.setString(1, updateID.getText());
			ResultSet rs = checkPst.executeQuery();
			while(rs.next())
				role = rs.getString("rol");
			if(role.equals("admin") || role.equals("superadmin"))
				JOptionPane.showMessageDialog(null, "Nu aveti privilegii suficiente pentru modificarea datelor acestui user!");
			else
			{
				try {
					PreparedStatement pst1 = conn.prepareStatement(sql1);
					pst1.setString(1, updateLastName.getText());
					pst1.setString(2, updateID.getText());
					pst1.execute();
					
					PreparedStatement pst2 = conn.prepareStatement(sql2);
					pst2.setString(1, updateFirstName.getText());
					pst2.setString(2, updateID.getText());
					pst2.execute();
					
					PreparedStatement pst3 = conn.prepareStatement(sql3);
					pst3.setString(1, updateCNP.getText());
					pst3.setString(2, updateID.getText());
					pst3.execute();
					
					PreparedStatement pst4 = conn.prepareStatement(sql4);
					pst4.setString(1, updateAdresa.getText());
					pst4.setString(2, updateID.getText());
					pst4.execute();
					
					PreparedStatement pst5 = conn.prepareStatement(sql5);
					pst5.setString(1, updateTel.getText());
					pst5.setString(2, updateID.getText());
					pst5.execute();
					
					PreparedStatement pst6 = conn.prepareStatement(sql6);
					pst6.setString(1, updateEmail.getText());
					pst6.setString(2, updateID.getText());
					pst6.execute();
					
					PreparedStatement pst7 = conn.prepareStatement(sql7);
					pst7.setString(1, updateIBAN.getText());
					pst7.setString(2, updateID.getText());
					pst7.execute();
					
					PreparedStatement pst8 = conn.prepareStatement(sql8);
					pst8.setString(1, updateNumarContract.getText());
					pst8.setString(2, updateID.getText());
					pst8.execute();
					
					PreparedStatement pst9 = conn.prepareStatement(sql9);
					pst9.setString(1, updatePassword.getText());
					pst9.setString(2, updateID.getText());
					pst9.execute();
						
					JOptionPane.showMessageDialog(null, "Date modificate cu succes!");
				} catch (Exception e) {
					JOptionPane.showMessageDialog(null, e);
				}
			}
				
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}		
	}	
	
	public void updateDatePersonaleSuperadmin(ActionEvent event) {
		conn = MYSQLconnection.ConnectDatabase();
		
		String sql1 = "update users set nume = ? where id_user = ? ";
		String sql2 = "update users set prenume = ? where id_user = ?"; 
		String sql3 = "update users set cnp = ? where id_user = ? ";
		String sql4 = "update users set adresa = ? where id_user = ?  "; 
		String sql5 = "update users set telefon = ? where id_user = ? ";
		String sql6 = "update users set email = ? where id_user = ?"; 
		String sql7 = "update users set iban = ? where id_user = ? ";
		String sql8 = "update users set nr_contract = ? where id_user = ?"; 
		String sql9 = "update users set parola = ? where id_user = ?";
		
		try {
			PreparedStatement pst1 = conn.prepareStatement(sql1);
			pst1.setString(1, updateLastName1.getText());
			pst1.setString(2, updateID1.getText());
			pst1.execute();
			
			PreparedStatement pst2 = conn.prepareStatement(sql2);
			pst2.setString(1, updateFirstName1.getText());
			pst2.setString(2, updateID1.getText());
			pst2.execute();
			
			PreparedStatement pst3 = conn.prepareStatement(sql3);
			pst3.setString(1, updateCNP1.getText());
			pst3.setString(2, updateID1.getText());
			pst3.execute();
			
			PreparedStatement pst4 = conn.prepareStatement(sql4);
			pst4.setString(1, updateAdresa1.getText());
			pst4.setString(2, updateID1.getText());
			pst4.execute();
			
			PreparedStatement pst5 = conn.prepareStatement(sql5);
			pst5.setString(1, updateTel1.getText());
			pst5.setString(2, updateID1.getText());
			pst5.execute();
			
			PreparedStatement pst6 = conn.prepareStatement(sql6);
			pst6.setString(1, updateEmail1.getText());
			pst6.setString(2, updateID1.getText());
			pst6.execute();
			
			PreparedStatement pst7 = conn.prepareStatement(sql7);
			pst7.setString(1, updateIBAN1.getText());
			pst7.setString(2, updateID1.getText());
			pst7.execute();
			
			PreparedStatement pst8 = conn.prepareStatement(sql8);
			pst8.setString(1, updateNumarContract1.getText());
			pst8.setString(2, updateID1.getText());
			pst8.execute();
			
			PreparedStatement pst9 = conn.prepareStatement(sql9);
			pst9.setString(1, updatePassword1.getText());
			pst9.setString(2, updateID1.getText());
			pst9.execute();
				
			JOptionPane.showMessageDialog(null, "Date modificate cu succes!");
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}	
			
	}	
	
	@FXML
	private void backUpdate(ActionEvent event) {
		if(role.equals("admin"))
		{
			updateAdminPanel.setVisible(false);
			adminPanel.setVisible(true);
		}
		else if(role.equals("superadmin"))
		{
			updateSuperadminPanel.setVisible(false);
			superadminPanel.setVisible(true);
		}
	}
	
	public void signUpCourse(ActionEvent event) {
		
		String getMat = "select distinct nume_materie from materii inner join prof_curs on "
				+ "materii.id_materie = prof_curs.id_materie where id_curs in (select B.id_curs from "
				+ "prof_curs as B inner join curs_student as C on B.id_curs=C.id_curs where C.id_curs"
				+ " not in (select A.id_curs from curs_student as A inner join users as B on A.id_student "
				+ "= B.id_user where email = ?))";
		String[] cursuri = new String[50];
		String cursAles = "";
		
		try {
			int i = 0;
			PreparedStatement gm = conn.prepareStatement(getMat);
			gm.setString(1, emailLogin.getText());
			rs = gm.executeQuery();
			while(rs.next())
			{
				cursAles += rs.getString("nume_materie");
				cursuri[i] = cursAles;
				i++;
				cursAles = "";
			}
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
		
		Object returnValue = JOptionPane.showInputDialog(null, "Alege numele cursului la care doresti sa te inscri", "Inscriere Curs", 1, null, cursuri, cursuri[0]);
		
		if(returnValue != null)
		{
			cursAles = returnValue.toString();
			conn = MYSQLconnection.ConnectDatabase();
			String getCursID = "select id_curs from prof_curs where id_materie = (select id_materie from materii where nume_materie = ?) and nr_stud < max_stud order by nr_stud limit 1";
			String sql1 = "insert into curs_student (id_curs, id_student) values (?, (select id_user from users where email = ?))";
			String sql2 = "update prof_curs set nr_stud = nr_stud + 1 where id_curs = ?";
			try {
					int idCurs = 0;
					
					PreparedStatement pst1 = conn.prepareStatement(getCursID);
					pst1.setString(1, cursAles);
					rs = pst1.executeQuery();
					while(rs.next())
					{			
						idCurs = rs.getInt("id_curs");
					}	
		
					PreparedStatement pst3 = conn.prepareStatement(sql1);
					pst3.setString(1, Integer.toString(idCurs));
					pst3.setString(2, emailLogin.getText());
					pst3.execute();
		
					PreparedStatement pst4 = conn.prepareStatement(sql2);
					pst4.setString(1, Integer.toString(idCurs));
					pst4.execute();
					
					JOptionPane.showMessageDialog(null, "Te-ai inscris cu succes la materia " + cursAles, "Inscriere Curs", 1);
			
			} catch (Exception e) {
				JOptionPane.showMessageDialog(null, e);
			}
		}
	}
	
	public void giveUpCourse(ActionEvent event) {
		String getMat = "select nume_materie from materii inner join (select C.id_materie from (select A.id_materie from prof_curs as A inner join curs_student as B on A.id_curs = "
				+ "B.id_curs where B.id_student = (select id_user from users where email = ?)) as C) as D on materii.id_materie = D.id_materie";
		String[] cursuri = new String[50];
		String cursAles = "";
		
		try {
			int i = 0;
			PreparedStatement gm = conn.prepareStatement(getMat);
			gm.setString(1, emailLogin.getText());
			rs = gm.executeQuery();
			while(rs.next())
			{
				cursAles += rs.getString("nume_materie");
				cursuri[i] = cursAles;
				i++;
				cursAles = "";
			}
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
		
		Object returnValue = JOptionPane.showInputDialog(null, "Alege numele cursului la care doresti sa renunti", "Renuntare Curs", 1, null, cursuri, cursuri[0]);
		
		if(returnValue != null)
		{
			cursAles = returnValue.toString();
			conn = MYSQLconnection.ConnectDatabase();
			String getCursID = "select id_curs from curs_student where id_curs = (select A.id_curs from prof_curs as A inner join materii as B on A.id_materie=B.id_materie where "
					+ "B.nume_materie = ? limit 1) and id_student = (select id_user from users where email = ?)";
			String sql1 = "delete from curs_student where id_student=(select id_user from users where email = ?) and id_curs = ?";
			String sql2 = "update prof_curs set nr_stud = nr_stud - 1 where id_curs = ?";
			try{
					int idCurs = 0;
					
					PreparedStatement pst1 = conn.prepareStatement(getCursID);
					pst1.setString(1, cursAles);
					pst1.setString(2, emailLogin.getText());
					rs = pst1.executeQuery();
					while(rs.next())
					{			
						idCurs = rs.getInt("id_curs");
					}	
		
					PreparedStatement pst3 = conn.prepareStatement(sql1);
					pst3.setString(1, emailLogin.getText());
					pst3.setString(2, Integer.toString(idCurs));
					pst3.execute();
		
					PreparedStatement pst4 = conn.prepareStatement(sql2);
					pst4.setString(1, Integer.toString(idCurs));
					pst4.execute();
				
				JOptionPane.showMessageDialog(null, "Ai renuntat cu succes la materia: " + cursAles, "Renuntare Curs", 1);
			} catch (Exception e) {
				JOptionPane.showMessageDialog(null, e);
			}
		}
	}
	
	public void getStudentGrades(ActionEvent event) {
		conn = MYSQLconnection.ConnectDatabase();
		String q1 = "select A.nota, A.tip_activitate, B.nume_materie from note as A inner join (select C.id_curs, D.nume_materie from prof_curs as C inner join materii as "
				+ "D on C.id_materie = D.id_materie) as B on B.id_curs = A.id_curs where id_student = (select id_user from users where email = ?);";
		try{
				String finalResult = "";
				pst = conn.prepareStatement(q1);
				pst.setString(1, emailLogin.getText());
				rs = pst.executeQuery();
				while(rs.next())
				{
					String nota = rs.getString("nota");
					String activitate = rs.getString("tip_activitate");
					String materie = rs.getString("nume_materie");
					finalResult += "Nota: " + nota + " | Materia: " + materie + " | Tipul de activitate: " + activitate + "\n";
				}
				
				if(finalResult.equals(""))
					JOptionPane.showMessageDialog(null, "Nu ai note!", "Vizualizare note", 1);
				else
					JOptionPane.showMessageDialog(null, finalResult, "Vizualizare note", 1);
			} catch (Exception e) {
				JOptionPane.showMessageDialog(null, e);
			}
	}
	
	public void joinGroup(ActionEvent event) {
		//returneaza numele materiei daca studentul e inscris la ea, sau nimic daca nu (de verificat cu if rs.next() atunci fac urmatorul query, daca nu mesaj de eroare)
		
		String getMat = "select nume_materie from materii inner join (select C.id_materie from (select A.id_materie from prof_curs as A inner join curs_student as B on A.id_curs = "
				+ "B.id_curs where B.id_student = (select id_user from users where email = ?)) as C) as D on materii.id_materie = D.id_materie";
		String[] cursuri = new String[50];
		String cursAles = "";
		
		try {
			int i = 0;
			PreparedStatement gm = conn.prepareStatement(getMat);
			gm.setString(1, emailLogin.getText());
			rs = gm.executeQuery();
			while(rs.next())
			{
				cursAles += rs.getString("nume_materie");
				cursuri[i] = cursAles;
				i++;
				cursAles = "";
			}
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
		
		Object returnValue = JOptionPane.showInputDialog(null, "Alege numele cursului in a carui grup doresti sa intri", "Alaturare la grup", 1, null, cursuri, cursuri[0]);
		
		if(returnValue != null)
		{
			cursAles = returnValue.toString();
			conn = MYSQLconnection.ConnectDatabase();
			String checkCourse = "select A.nume_materie from materii as A inner join (select C.id_materie, D.id_student from prof_curs as C inner join curs_student as D on C.id_curs="
					+ "D.id_curs) as B on A.id_materie=B.id_materie where B.id_student = (select id_user from users where email = ?) and A.nume_materie = ?";
			String q1="insert into grup_student (id_curs, id_student) values ((select B.id_curs from curs_student as A inner join (select C.id_curs, D.nume_materie from prof_curs as "
					+ "C inner join materii as D on C.id_materie = D.id_materie) as B on B.id_curs=A.id_curs where id_student=(select id_user from users where email=?) and "
					+ "B.nume_materie = ?), (select id_user from users where email=?))";
			
			try{
					PreparedStatement cC = conn.prepareStatement(checkCourse);
					cC.setString(1, emailLogin.getText());
					cC.setString(2, cursAles);
					rs = cC.executeQuery();
					
					if(rs.next())
					{
						PreparedStatement insertStudent = conn.prepareStatement(q1);
						insertStudent.setString(1, emailLogin.getText());
						insertStudent.setString(2, cursAles);
						insertStudent.setString(3, emailLogin.getText());
						insertStudent.execute();
						JOptionPane.showMessageDialog(null, "Te-ai alaturat cu succes!", "Alaturare la grup", 1);
						viewToday();
					}
					else
					{
						//mesaj eroare(studentul nu e la curs)
						JOptionPane.showMessageDialog(null, "Nu te poti alatura grupului deoarece nu participi la cursul de " + cursAles + 
								"\nsau esti deja inscris in acest grup", "Alaturare la grup", 0);
					}
					
			} catch (Exception e) {
				JOptionPane.showMessageDialog(null, e);
			}
		}
	}
	
	public void viewGroupMembers(ActionEvent event) {
		String getMat = "select nume_materie from materii inner join (select C.id_materie from (select A.id_materie from prof_curs as A inner join curs_student as B on A.id_curs = "
				+ "B.id_curs where B.id_student = (select id_user from users where email = ?)) as C) as D on materii.id_materie = D.id_materie";
		String[] cursuri = new String[50];
		String cursAles = "";
		
		try {
			int i = 0;
			PreparedStatement gm = conn.prepareStatement(getMat);
			gm.setString(1, emailLogin.getText());
			rs = gm.executeQuery();
			while(rs.next())
			{
				cursAles += rs.getString("nume_materie");
				cursuri[i] = cursAles;
				i++;
				cursAles = "";
			}
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
		
		Object returnValue = JOptionPane.showInputDialog(null, "Alege numele grupului a carui membrii doresti sa-i vizualizei", "Vizualizare membrii grup", 1, null, cursuri, cursuri[0]);
		
		if(returnValue != null)
		{
			cursAles = returnValue.toString();
			conn = MYSQLconnection.ConnectDatabase();
			String q1 = "select distinct A.nume, A.prenume from users as A inner join (select id_student from  grup_student where id_curs = (select id_curs from prof_curs inner "
					+ "join materii on materii.id_materie = prof_curs.id_materie where nume_materie = ?)) as B on B.id_student = A.id_user";
			try{
					String finalResult = "";
					PreparedStatement q = conn.prepareStatement(q1);
					q.setString(1, cursAles);
					rs = q.executeQuery();
					
					while(rs.next())
					{
						String lastName = rs.getString("nume");
						String firstName = rs.getString("prenume");
						finalResult += lastName + " " + firstName + "\n";
       
					}
					if(finalResult.equals(""))
						finalResult = "Grupul selectat nu are membrii!";
					
					JOptionPane.showMessageDialog(null, finalResult, "Vizualizare membrii grup", 1);
					
			} catch (Exception e) {
				JOptionPane.showMessageDialog(null, e);
			}
		}
	}
	
	public void showSendMessage(ActionEvent event) {
		sendMessagePane.setVisible(true);
	}
	
	public void hideSendMessage(ActionEvent event) {
		sendMessagePane.setVisible(false);
		showMessageLabel.setText(null);
		textMesaj.clear();
	}
	
	public void sendMessage(ActionEvent event) {
			String getMat = "select nume_materie from materii inner join (select C.id_materie from (select A.id_materie from prof_curs as A inner join curs_student as B on A.id_curs = "
				+ "B.id_curs where B.id_student = (select id_user from users where email = ?)) as C) as D on materii.id_materie = D.id_materie";
			String[] cursuri = new String[50];
			String cursAles = "";
			
			try {
				int i = 0;
				PreparedStatement gm = conn.prepareStatement(getMat);
				gm.setString(1, emailLogin.getText());
				rs = gm.executeQuery();
				while(rs.next())
				{
					cursAles += rs.getString("nume_materie");
					cursuri[i] = cursAles;
					i++;
					cursAles = "";
				}
			} catch (Exception e) {
				JOptionPane.showMessageDialog(null, e);
			}
			
			Object returnValue = JOptionPane.showInputDialog(null, "Alege numele grupului in care doresti sa trimiti un mesaj", "Trimite mesaj in grup", 1, null, cursuri, cursuri[0]);
		
		if(returnValue != null)
		{
			cursAles = returnValue.toString();
			conn = MYSQLconnection.ConnectDatabase();
			String qM = "insert into mesaje (id_curs, fromId, mesaj, data) values ((select id_materie from "
					+ "materii where nume_materie = ?), (select id_user from users where email=?) , ? , "
					+ "(select now()) )";
			try{
					PreparedStatement q = conn.prepareStatement(qM);
					q.setString(1, cursAles);
					q.setString(2, emailLogin.getText());//sa verificam totusi daca nu merge salvat direct mailul undeva si sa il dam direct ca variabila fara label
					q.setString(3, textMesaj.getText());
					q.execute();
					JOptionPane.showMessageDialog(null, "Mesajul a fost trimis!", "Trimite mesaj in grup", 1);
					textMesaj.clear();
			} catch (Exception e) {
				JOptionPane.showMessageDialog(null, e);
			}
			// getMessage();//merge apelat asa? sau tb trimis ceva sau nush cumva dupa ce trimiti mesaju sa si apara eventual nush cum ii mai usor vezi si tu
			getMessageWithoutChoosing(event, cursAles);
		}
	}
	
	public void getMessageWithoutChoosing(ActionEvent event, String cursAles) {
		conn = MYSQLconnection.ConnectDatabase();
		String qM = "select A.nume, A.prenume, B.mesaj from users as A inner join mesaje as B on "
				+ "A.id_user = B.fromId where id_curs = (select id_materie from materii "
				+ "where nume_materie=? ) order by data desc limit 5";
		try{
				PreparedStatement q=conn.prepareStatement(qM);
				q.setString(1, cursAles);
				rs = q.executeQuery();
				String messages = "";
				
				while(rs.next())
				{
					messages += rs.getString("nume");
					messages += " " + rs.getString("prenume");
					messages += ": " + rs.getString("mesaj") + "\n";
				}
				
				if(messages.equals(""))
					messages = "Nu exista mesaje!";
				
				showMessageLabel.setText(messages);		
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
	}

	public void getMessage(ActionEvent event) {
		String getMat = "select nume_materie from materii inner join (select C.id_materie from (select A.id_materie from prof_curs as A inner join curs_student as B on A.id_curs = "
				+ "B.id_curs where B.id_student = (select id_user from users where email = ?)) as C) as D on materii.id_materie = D.id_materie";
		String[] cursuri = new String[50];
		String cursAles = "";
		
		try {
			int i = 0;
			PreparedStatement gm = conn.prepareStatement(getMat);
			gm.setString(1, emailLogin.getText());
			rs = gm.executeQuery();
			while(rs.next())
			{
				cursAles += rs.getString("nume_materie");
				cursuri[i] = cursAles;
				i++;
				cursAles = "";
			}
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
		
		Object returnValue = JOptionPane.showInputDialog(null, "Alege numele grupului in care doresti sa trimiti un mesaj", "Vezi mesaje din grup", 1, null, cursuri, cursuri[0]);
		
		if(returnValue != null)
		{
			cursAles = returnValue.toString();
			conn = MYSQLconnection.ConnectDatabase();
			String qM = "select A.nume, A.prenume, B.mesaj from users as A inner join mesaje as B on "
					+ "A.id_user = B.fromId where id_curs = (select id_materie from materii "
					+ "where nume_materie=? ) order by data desc limit 5";
			try{
					PreparedStatement q=conn.prepareStatement(qM);
					q.setString(1, cursAles);
					rs = q.executeQuery();
					String messages = "";
					
					while(rs.next())
					{
						messages += rs.getString("nume");
						messages += " " + rs.getString("prenume");
						messages += ": " + rs.getString("mesaj") + "\n";
					}
					
					if(messages.equals(""))
						messages = "Nu exista mesaje!";
					
					showMessageLabel.setText(messages);		
			} catch (Exception e) {
				JOptionPane.showMessageDialog(null, e);
			}
		}
	}
	
	public void showAddActivity(ActionEvent event) {
		addActivityPane.setVisible(true);
	}
	
	public void hideAddActivity(ActionEvent event) {
		addActivityPane.setVisible(false);
		titluActivitate.clear();
		dataActivitate.setValue(null);
		durataActivitate.clear();
		numarMinim.clear();
	}
	
	@FXML
	private TextField numeProfAddAc;
	
	@FXML
	private TextField prenumeProfAddAc;
	
	public void addActivity(ActionEvent event)
	{
		// id_activitate trebuie sa aiba auto increment
		String getMat = "select nume_materie from materii inner join (select C.id_materie from (select A.id_materie from prof_curs as A inner join curs_student as B on A.id_curs = "
				+ "B.id_curs where B.id_student = (select id_user from users where email = ?)) as C) as D on materii.id_materie = D.id_materie";
		String[] cursuri = new String[50];
		String cursAles = "";
		
		try {
			int i = 0;
			PreparedStatement gm = conn.prepareStatement(getMat);
			gm.setString(1, emailLogin.getText());
			rs = gm.executeQuery();
			while(rs.next())
			{
				cursAles += rs.getString("nume_materie");
				cursuri[i] = cursAles;
				i++;
				cursAles = "";
			}
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
		
		Object returnValue = JOptionPane.showInputDialog(null, "Alege numele grupului in care doresti sa adaugi o activitate", "Adauga activitate in grup", 1, null, cursuri, cursuri[0]);
		
		if(returnValue != null)
		{
			cursAles = returnValue.toString();
			conn = MYSQLconnection.ConnectDatabase();
			
			String qA = "insert into activitati_grup (id_curs, titlu, data, durata, nr_min, id_prof) values ((select id_curs from prof_curs inner join materii on "
					+ "materii.id_materie = prof_curs.id_materie where nume_materie = ?), ? , ?, ?, ? , (select profesori.id_profesor from profesori inner join users on "
					+ "users.id_user = profesori.id_profesor where users.nume=? and users.prenume = ?));";
			
			if(Integer.parseUnsignedInt(numarMinim.getText()) != 0)
			{
				try{
						PreparedStatement q=conn.prepareStatement(qA);
						q.setString(1, cursAles);
						q.setString(2, titluActivitate.getText());
						java.util.Date date = java.util.Date.from(dataActivitate.getValue().atStartOfDay(ZoneId.systemDefault()).toInstant());
						java.sql.Date sqlDate = new java.sql.Date(date.getTime());
						q.setDate(3, sqlDate);
						q.setInt(4, Integer.parseInt(durataActivitate.getText()));
						q.setInt(5, Integer.parseUnsignedInt(numarMinim.getText()));
						q.setString(6, numeProfAddAc.getText());
						q.setString(7, prenumeProfAddAc.getText());
						q.execute();
						JOptionPane.showMessageDialog(null, "Activitatea a fost adaugata cu succes la grup!", "Adaugare activitate in grup", 1);
						viewToday();
						
				} catch (Exception e) {
					JOptionPane.showMessageDialog(null, e);
				}
			}
			else
			{	
				JOptionPane.showMessageDialog(null, "Numar insuficient de participanti.", "Adaugare activitate in grup", 0);
			}
		}

	}

	public void setPerc(ActionEvent event) {
		String getMat = "select A.nume_materie from materii as A inner join prof_curs as B on A.id_materie = B.id_materie where id_prof = (select id_user from users where email = ?)";
		String[] cursuri = new String[50];
		String cursAles = "";
		
		try {
			int i = 0;
			PreparedStatement gm = conn.prepareStatement(getMat);
			gm.setString(1, emailLogin.getText());
			rs = gm.executeQuery();
			while(rs.next())
			{
				cursAles += rs.getString("nume_materie");
				cursuri[i] = cursAles;
				i++;
				cursAles = "";
			}
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
		
		Object returnValue = JOptionPane.showInputDialog(null, "Alegeti numele materiei ale carei procentaje doriti sa le modificati", "Modificare procentaje materie", 1, null, cursuri, cursuri[0]);
		
		if(returnValue != null)
		{
			cursAles = returnValue.toString();
			conn = MYSQLconnection.ConnectDatabase();
			
			JPanel pane = new JPanel();
			pane.setLayout(new GridLayout(0, 2, 2, 2));
			
			JTextField pCursField = new JTextField(2);
			JTextField pSeminarField = new JTextField(2);
			JTextField pLabField = new JTextField(2);
			
			pane.add(new JLabel("Introduceti procentajul notei de la curs"));
			pane.add(pCursField);
			pane.add(new JLabel("Introduceti procentajul notei de la seminar"));
			pane.add(pSeminarField);
			pane.add(new JLabel("Introduceti procentajul notei de la laborator"));
			pane.add(pLabField);
			
	        int option = JOptionPane.showConfirmDialog(null, pane, "Introduceti procentajele materiei: ", JOptionPane.OK_CANCEL_OPTION, JOptionPane.INFORMATION_MESSAGE);
	        
	        if (option == JOptionPane.OK_OPTION)
	        {
	        	int pCurs, pSeminar, pLab;
	        	
	        	pCurs = pSeminar = pLab = 0;
	        	
	        	try {
		        		pCurs = Integer.parseInt(pCursField.getText());
			        	pSeminar = Integer.parseInt(pSeminarField.getText());
			        	pLab = Integer.parseInt(pLabField.getText());
	        		//stringCurs = pCursField.getText();
	        		//System.out.println(stringCurs);
	        	} catch (NumberFormatException nfe) {
	        		nfe.printStackTrace();
	        	}
	        	
	        	if(pCurs + pSeminar + pLab != 100)
	        		JOptionPane.showMessageDialog(null, "Procentajele sunt incorecte", "Modificare procentaje materie", 0);
	        	else
	        	{
	        		String sp="update prof_curs set p_seminar=?, p_curs=?, p_lab=? where id_prof=(select id_user from users where email=?) and id_materie = (select id_materie from materii where "
							+ "nume_materie = ?)";
					try {
							PreparedStatement q=conn.prepareStatement(sp);
							q.setInt(1, pSeminar);
							q.setInt(2, pCurs);
							q.setInt(3, pLab);
							q.setString(4, emailLogin.getText());
							q.setString(5, cursAles);
							q.execute();
							
							JOptionPane.showMessageDialog(null, "Procentajele au fost introduse cu succes", "Modificare procentaje materie", 1);
							
					} catch (Exception e) {
						JOptionPane.showMessageDialog(null, e);
					}
	        	}	
	        }
		}
	}
	
	public void showAddProg(ActionEvent event) {
		addProgPane.setVisible(true);
	}
	
	public void hideAddProg(ActionEvent event) {
		addProgPane.setVisible(false);
		dataProgramare.setValue(null);
		tipProgramare.clear();
	}
	
	public void addProg(ActionEvent event)
	{
		// de adus doar cursurile profului in drop down
		String getMat = "select A.nume_materie from materii as A inner join prof_curs as B on A.id_materie = B.id_materie where id_prof = (select id_user from users where email = ?)";
		String[] cursuri = new String[50];
		String cursAles = "";
		
		try {
			int i = 0;
			PreparedStatement gm = conn.prepareStatement(getMat);
			gm.setString(1, emailLogin.getText());
			rs = gm.executeQuery();
			while(rs.next())
			{
				cursAles += rs.getString("nume_materie");
				cursuri[i] = cursAles;
				i++;
				cursAles = "";
			}
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
		
		Object returnValue = JOptionPane.showInputDialog(null, "Alegeti numele materiei la care doriti sa programati activitatea", "Programare activitate", 1, null, cursuri, cursuri[0]);
		
		if(returnValue != null)
		{
			cursAles = returnValue.toString();
			conn = MYSQLconnection.ConnectDatabase();
		
			String ap = "insert into programari (id_curs, data, tip, ora) values ((select id_curs from prof_curs where id_prof = (select id_user from users where email=?) and id_materie = "
					+ "(select id_materie from materii where nume_materie=?)), ?, ?, ?)";
			
			java.util.Date date = java.util.Date.from(dataProgramare.getValue().atStartOfDay(ZoneId.systemDefault()).toInstant());
			Calendar cal = Calendar.getInstance();
			cal.setTime(date);
			cal.set(Calendar.HOUR_OF_DAY, 0);
			java.sql.Date currentDate = new java.sql.Date(cal.getTimeInMillis());
			java.sql.Date sqlDate = new java.sql.Date(date.getTime());
			
			if(sqlDate.compareTo(currentDate) >= 0)
			{
				try{
					PreparedStatement q=conn.prepareStatement(ap);
					q.setString(1, emailLogin.getText());
					q.setString(2, cursAles);
					q.setDate(3, sqlDate);
					q.setString(4, tipProgramare.getText());
					q.setString(5, oraProgramare.getText());
					q.execute();
					JOptionPane.showMessageDialog(null, "Activitate programata cu succes!", "Programare activitate", 1);
					viewToday();
					
				} catch (Exception e) {
					JOptionPane.showMessageDialog(null, e);
				}
			}
			
			else
			{
				JOptionPane.showMessageDialog(null, "Data introdusa este in trecut", "Programare activitate", 0);
			}
		}
	}
	
	public void hideSeeCatalogue(ActionEvent event) {
		cataloguePane.setVisible(false);
	}
	
	@FXML
	public void seeCatalogue(ActionEvent event)
	{
		cataloguePane.setVisible(true);
		
		String getMat = "select A.nume_materie from materii as A inner join prof_curs as B on A.id_materie = B.id_materie where id_prof = (select id_user from users where email = ?)";
		String[] cursuri = new String[50];
		String cursAles = "";
		
		try {
			int i = 0;
			PreparedStatement gm = conn.prepareStatement(getMat);
			gm.setString(1, emailLogin.getText());
			rs = gm.executeQuery();
			while(rs.next())
			{
				cursAles += rs.getString("nume_materie");
				cursuri[i] = cursAles;
				i++;
				cursAles = "";
			}
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
		
		Object returnValue = JOptionPane.showInputDialog(null, "Alegeti numele materiei al carei catalog diriti sa-l vizualizati", "Vizualizare catalog", 1, null, cursuri, cursuri[0]);
		
		if(returnValue != null)
		{
			cursAles = returnValue.toString();
			conn = MYSQLconnection.ConnectDatabase();
			
			String sc="select A.nume, A.prenume, nume_materie, tip_activitate, nota from users as A inner join (select C.id_curs, D.nume_materie, C.tip_activitate, C.nota, "
					+ "C.id_student from note as C inner join (select B.nume_materie, A.id_curs from prof_curs as A inner join materii as B on A.id_materie=B.id_materie where "
					+ "B.nume_materie = ?) as D on C.id_curs = D.id_curs) as B on A.id_user = B.id_student where B.id_curs in (select id_curs from prof_curs where id_prof = "
					+ "(select id_user from users where email = ?))";
			try{
					PreparedStatement q=conn.prepareStatement(sc);
					q.setString(1, cursAles);
					q.setString(2, emailLogin.getText());
					rs = q.executeQuery();
					
					lastNameColumn.setCellValueFactory(new PropertyValueFactory<>("lastName"));
					firstNameColumn.setCellValueFactory(new PropertyValueFactory<>("firstName"));
					materieColumn.setCellValueFactory(new PropertyValueFactory<>("materie"));
					tipActivitateColumn.setCellValueFactory(new PropertyValueFactory<>("tipulActivitatii"));
					notaColumn.setCellValueFactory(new PropertyValueFactory<>("nota"));
						
					ObservableList<StudentData> studentData = FXCollections.observableArrayList();
					
					while(rs.next())
					{
						String lastName = rs.getString("nume");
						String firstName = rs.getString("prenume");
						String materie = rs.getString("nume_materie");
						String activitate = rs.getString("tip_activitate");
						float nota = rs.getFloat("nota");
						studentData.add(new StudentData(lastName, firstName, materie, activitate, nota));	
					}
					tableCatalogue.setItems(studentData);
							
			} catch (Exception e) {
				JOptionPane.showMessageDialog(null, e);
			}
		}
	}
	
	@FXML
	private Button downloadCatalogButton;
	
	@FXML
	public void downloadCatalogue(ActionEvent event)
	{
		
		String getMat = "select A.nume_materie from materii as A inner join prof_curs as B on A.id_materie = B.id_materie where id_prof = (select id_user from users where email = ?)";
		String[] cursuri = new String[50];
		String cursAles = "";
		
		try {
			int i = 0;
			PreparedStatement gm = conn.prepareStatement(getMat);
			gm.setString(1, emailLogin.getText());
			rs = gm.executeQuery();
			while(rs.next())
			{
				cursAles += rs.getString("nume_materie");
				cursuri[i] = cursAles;
				i++;
				cursAles = "";
			}
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
		
		Object returnValue = JOptionPane.showInputDialog(null, "Alegeti numele materiei al carei catalog diriti sa-l vizualizati", "Vizualizare catalog", 1, null, cursuri, cursuri[0]);
		
		if(returnValue != null)
		{
			cursAles = returnValue.toString();
			conn = MYSQLconnection.ConnectDatabase();
			
			String sc="select A.nume, A.prenume, nume_materie, tip_activitate, nota from users as A inner join (select C.id_curs, D.nume_materie, C.tip_activitate, C.nota, "
					+ "C.id_student from note as C inner join (select B.nume_materie, A.id_curs from prof_curs as A inner join materii as B on A.id_materie=B.id_materie where "
					+ "B.nume_materie = ?) as D on C.id_curs = D.id_curs) as B on A.id_user = B.id_student where B.id_curs in (select id_curs from prof_curs where id_prof = "
					+ "(select id_user from users where email = ?))";
			try{
					PreparedStatement q=conn.prepareStatement(sc);
					q.setString(1, cursAles);
					q.setString(2, emailLogin.getText());
					rs = q.executeQuery();
					
					String rf="";
					while(rs.next())
					{
						String lastName = rs.getString("nume");
						String firstName = rs.getString("prenume");
						String materie = rs.getString("nume_materie");
						String activitate = rs.getString("tip_activitate");
						float nota = rs.getFloat("nota");
						rf += lastName + " | " + firstName + " | " + materie + " | " + activitate + " | " + nota + '\n';
						// System.out.println(rf);
						
					}
					Path path = Paths.get("C:\\Users\\andre\\Desktop\\Catalog.txt");
					
					try {					      
						Files.writeString(path, rf, StandardCharsets.UTF_8);
						JOptionPane.showMessageDialog(null, "Catalogul a fost descarcat cu succes", "Descarcare catalog", 1);
						
					    } catch (IOException e) {
					      System.out.println("An error occurred.");
					      e.printStackTrace();
					    }
					
							
			} catch (Exception e) {
				JOptionPane.showMessageDialog(null, e);
			}
		}
	}
	
	
	
	
	public void showAddGrade(ActionEvent event) {
		addGradePane.setVisible(true);
	}
	
	public void hideAddGrade(ActionEvent event) {
		addGradePane.setVisible(false);
		addGradeLastNameField.clear();
		addGradeFirstNameField.clear();
		addGradeField.clear();
	}
	
	public void addGrade(ActionEvent event) {
		
		String getMat = "select A.nume_materie from materii as A inner join prof_curs as B on A.id_materie = B.id_materie where id_prof = (select id_user from users where email = ?)";
		String[] cursuri = new String[50];
		String cursAles = "";
		
		try {
			int i = 0;
			PreparedStatement gm = conn.prepareStatement(getMat);
			gm.setString(1, emailLogin.getText());
			rs = gm.executeQuery();
			while(rs.next())
			{
				cursAles += rs.getString("nume_materie");
				cursuri[i] = cursAles;
				i++;
				cursAles = "";
			}
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
		
		Object returnValue = JOptionPane.showInputDialog(null, "Alegeti numele materiei unde doriti sa introduceti nota", "Introducere note", 1, null, cursuri, cursuri[0]);
		
		if(returnValue != null)
		{
			cursAles = returnValue.toString();
			conn = MYSQLconnection.ConnectDatabase();
			
			String ag = "insert into note ( id_student, id_curs, tip_activitate, nota) values ((select id_user from users where nume=? and prenume=?),(select id_curs from prof_curs as "
					+ "B where B.id_materie = (select id_materie from materii where nume_materie =?) and id_prof = (select id_user from users where email = ?)), ?, ?)";
			try{
					PreparedStatement q=conn.prepareStatement(ag);
					q.setString(1, addGradeLastNameField.getText());
					q.setString(2, addGradeFirstNameField.getText());
					q.setString(3, cursAles);
					q.setString(4, emailLogin.getText());
					q.setString(5, addGradeActivitateField.getText());
					q.setString(6, addGradeField.getText());
					q.execute();
					
					JOptionPane.showMessageDialog(null, "Nota a fost introdusa cu succes!", "Introducere note", 1);
					
					addGradeLastNameField.clear();
					addGradeFirstNameField.clear();
					addGradeActivitateField.clear();
					addGradeField.clear();
				
			} catch (Exception e) {
				JOptionPane.showMessageDialog(null, e);
			}
		}
	}
	
	public void deletePanelShow(ActionEvent event) {
		if(role.equals("admin"))
		{
			deleteAdminPanel.setVisible(true);
			//adminPanel.setVisible(false);
		}
		else if(role.equals("superadmin"))
		{
			deleteSuperadminPanel.setVisible(true);
			//adminPanel.setVisible(false);
		}
		
	}
	
	@FXML
	private void backDelteUser(ActionEvent event) {
		if(role.equals("admin"))
		{
			deleteAdminPanel.setVisible(false);
			adminPanel.setVisible(true);
		}
		else if(role.equals("superadmin"))
		{
			deleteSuperadminPanel.setVisible(false);
			superadminPanel.setVisible(true);
		}
	}
	
	public void deleteUserA(ActionEvent event) {
		// se presupune ca admin stie id-urile
		
		String del="delete from users where id_user = ? and rol != 'superadmin' and rol !='admin'";
		String check = "select rol from users where id_user = ?";
		
		try{
			PreparedStatement ch = conn.prepareStatement(check);
			ch.setString(1, adminDelete.getText());
			rs = ch.executeQuery();
			
			String rolID = "";
			if(rs.next())
				rolID = rs.getString("rol");
			if(rolID.equals("admin") || rolID.equals("superadmin"))
				JOptionPane.showMessageDialog(null, "Nu puteti sterge acest rol!", "Sterge utilizator", 0);
			else
			{
				PreparedStatement q = conn.prepareStatement(del);
				q.setString(1, adminDelete.getText());
				q.execute();
				JOptionPane.showMessageDialog(null, "Utilizator sters cu succes!", "Sterge utilizator", 1);
				adminDelete.clear();
			}
			
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
	}
		
	public void deleteUserSA(ActionEvent event) {
		String del="delete from users where id_user = ? and rol!='superadmin'";
		String check = "select rol from users where id_user = ?";
		
		try{
			PreparedStatement ch = conn.prepareStatement(check);
			ch.setString(1, superadminDelete.getText());
			rs = ch.executeQuery();
			
			String rolID = "";
			if(rs.next())
				rolID = rs.getString("rol");
			if(rolID.equals("superadmin"))
				JOptionPane.showMessageDialog(null, "Nu puteti sterge acest rol!", "Sterge utilizator", 0);
			else
			{
				PreparedStatement q = conn.prepareStatement(del);
				q.setString(1, superadminDelete.getText());
				q.execute();
				JOptionPane.showMessageDialog(null, "Utilizator sters cu succes!", "Sterge utilizator", 1);
				superadminDelete.clear();
			}
			
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
	}
	
	public void allDataShow(ActionEvent event) {
		if(role.equals("admin"))
		{
			seeAllDataAdminPanel.setVisible(true);
			//adminPanel.setVisible(false);
		}
		else if(role.equals("superadmin"))
		{
			seeAllDataSuperadminPanel.setVisible(true);
			//adminPanel.setVisible(false);
		}
		
	}
	
	@FXML
	private void backAllData(ActionEvent event) {
		if(role.equals("admin"))
		{
			seeAllDataAdminPanel.setVisible(false);
			//adminPanel.setVisible(true);
		}
		else if(role.equals("superadmin"))
		{
			seeAllDataSuperadminPanel.setVisible(false);
			//superadminPanel.setVisible(true);
		}
	}
	
	public void seeAllDataA(ActionEvent event)
	{
		String sel = "";	
		
		if(adminShowDataNume.getText().equals("") || adminShowDataPrenume.getText().equals(""))	
			sel = "select * from users where (nume = ? or prenume = ?)";
		else
			sel = "select * from users where (nume = ? and prenume = ?)";
		
		try{
			
			String finalR = "";
			
				PreparedStatement q = conn.prepareStatement(sel);
				q.setString(1, adminShowDataNume.getText());
				q.setString(2, adminShowDataPrenume.getText());
				rs = q.executeQuery();
				while(rs.next())
				{
					finalR += "Nume: " + rs.getString("nume") + " | ";
					finalR += "Prenume: " + rs.getString("prenume") + " | ";
					finalR += "CNP: " + rs.getString("cnp") + " | ";
					finalR += "Adresa: " + rs.getString("adresa") + " | ";
					finalR += "Telefon: " + rs.getString("telefon") + " | ";
					finalR += "Email: " + rs.getString("email") + " | ";
					finalR += "IBAN: " + rs.getString("iban") + " | ";
					finalR += "Numar contract: " + rs.getString("nr_contract") + " | ";
					finalR += "Rol: " + rs.getString("rol") + "\n";
				}
				
				if(finalR.equals(""))
					JOptionPane.showMessageDialog(null, "Nu exista date!", "Vizualizare date", 0);
				else
					JOptionPane.showMessageDialog(null, finalR, "Vizualizare date", 1);
				adminShowDataNume.clear();
				adminShowDataPrenume.clear();
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
	}
	
	public void seeAllDataSA(ActionEvent event)
	{
		String sel = "";	
		
		if(superadminShowDataNume.getText().equals("") || superadminShowDataPrenume.getText().equals(""))	
			sel = "select * from users where (nume = ? or prenume = ?)";
		else
			sel = "select * from users where (nume = ? and prenume = ?)";
		
		try{
			PreparedStatement q = conn.prepareStatement(sel);
			q.setString(1, superadminShowDataNume.getText());
			q.setString(2, superadminShowDataPrenume.getText());
			
			String finalR = "";
			
				rs = q.executeQuery();
				while(rs.next())
				{
					finalR += "Nume: " + rs.getString("nume") + " | ";
					finalR += "Prenume: " + rs.getString("prenume") + " | ";
					finalR += "CNP: " + rs.getString("cnp") + " | ";
					finalR += "Adresa: " + rs.getString("adresa") + " | ";
					finalR += "Telefon: " + rs.getString("telefon") + " | ";
					finalR += "Email: " + rs.getString("email") + " | ";
					finalR += "IBAN: " + rs.getString("iban") + " | ";
					finalR += "Numar contract: " + rs.getString("nr_contract") + " | ";
					finalR += "Rol: " + rs.getString("rol") + "\n";
				}
				
				if(finalR.equals(""))
					JOptionPane.showMessageDialog(null, "Nu exista date!", "Vizualizare date", 0);
				else
					JOptionPane.showMessageDialog(null, finalR, "Vizualizare date", 1);
				superadminShowDataNume.clear();
				superadminShowDataPrenume.clear();
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
	}
	
	public void seeStudentDataA(ActionEvent event)
	{
		String sel = "";	
		
		if(adminShowDataNume.getText().equals("") || adminShowDataPrenume.getText().equals(""))	
			sel = "select * from users where (nume = ? or prenume = ?) and rol = 'student'";
		else
			sel = "select * from users where (nume = ? and prenume = ?) and rol = 'student'";
		
		try{
			PreparedStatement q = conn.prepareStatement(sel);
			q.setString(1, adminShowDataNume.getText());
			q.setString(2, adminShowDataPrenume.getText());
			rs = q.executeQuery();
			
			String finalR = "";
			while(rs.next())
			{
				finalR += "Nume: " + rs.getString("nume") + " | ";
				finalR += "Prenume: " + rs.getString("prenume") + " | ";
				finalR += "CNP: " + rs.getString("cnp") + " | ";
				finalR += "Adresa: " + rs.getString("adresa") + " | ";
				finalR += "Telefon: " + rs.getString("telefon") + " | ";
				finalR += "Email: " + rs.getString("email") + " | ";
				finalR += "IBAN: " + rs.getString("iban") + " | ";
				finalR += "Numar contract: " + rs.getString("nr_contract") + " | ";
				finalR += "Rol: " + rs.getString("rol") + "\n";
			}
			
			if(finalR.equals(""))
				JOptionPane.showMessageDialog(null, "Nu exista date!", "Vizualizare date", 0);
			else
				JOptionPane.showMessageDialog(null, finalR, "Vizualizare date", 1);
			adminShowDataNume.clear();
			adminShowDataPrenume.clear();
			
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}

	}
	
	public void seeProfDataA(ActionEvent event)
	{
		String sel = "";	
		
		if(adminShowDataNume.getText().equals("") || adminShowDataPrenume.getText().equals(""))	
			sel = "select * from users where (nume = ? or prenume = ?) and rol = 'profesor'";
		else
			sel = "select * from users where (nume = ? and prenume = ?) and rol = 'profesor'";
		
		try{
			PreparedStatement q = conn.prepareStatement(sel);
			q.setString(1, adminShowDataNume.getText());
			q.setString(2, adminShowDataPrenume.getText());
			rs = q.executeQuery();
			
			String finalR = "";
			while(rs.next())
			{
				finalR += "Nume: " + rs.getString("nume") + " | ";
				finalR += "Prenume: " + rs.getString("prenume") + " | ";
				finalR += "CNP: " + rs.getString("cnp") + " | ";
				finalR += "Adresa: " + rs.getString("adresa") + " | ";
				finalR += "Telefon: " + rs.getString("telefon") + " | ";
				finalR += "Email: " + rs.getString("email") + " | ";
				finalR += "IBAN: " + rs.getString("iban") + " | ";
				finalR += "Numar contract: " + rs.getString("nr_contract") + " | ";
				finalR += "Rol: " + rs.getString("rol") + "\n";
			}
			
			if(finalR.equals(""))
				JOptionPane.showMessageDialog(null, "Nu exista date!", "Vizualizare date", 0);
			else
				JOptionPane.showMessageDialog(null, finalR, "Vizualizare date", 1);
			adminShowDataNume.clear();
			adminShowDataPrenume.clear();
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
	}
	
	public void seeStudentDataSA(ActionEvent event)
	{
		String sel = "";	
		
		if(superadminShowDataNume.getText().equals("") || superadminShowDataPrenume.getText().equals(""))	
			sel = "select * from users where (nume = ? or prenume = ?) and rol = 'student'";
		else
			sel = "select * from users where (nume = ? and prenume = ?) and rol = 'student'";
		
		try{
			PreparedStatement q = conn.prepareStatement(sel);
			q.setString(1, superadminShowDataNume.getText());
			q.setString(2, superadminShowDataPrenume.getText());
			rs = q.executeQuery();
			
			String finalR = "";
			while(rs.next())
			{
				finalR += "Nume: " + rs.getString("nume") + " | ";
				finalR += "Prenume: " + rs.getString("prenume") + " | ";
				finalR += "CNP: " + rs.getString("cnp") + " | ";
				finalR += "Adresa: " + rs.getString("adresa") + " | ";
				finalR += "Telefon: " + rs.getString("telefon") + " | ";
				finalR += "Email: " + rs.getString("email") + " | ";
				finalR += "IBAN: " + rs.getString("iban") + " | ";
				finalR += "Numar contract: " + rs.getString("nr_contract") + " | ";
				finalR += "Rol: " + rs.getString("rol") + "\n";
			}
			
			if(finalR.equals(""))
				JOptionPane.showMessageDialog(null, "Nu exista date!", "Vizualizare date", 0);
			else
				JOptionPane.showMessageDialog(null, finalR, "Vizualizare date", 1);
			superadminShowDataNume.clear();
			superadminShowDataPrenume.clear();
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}

	}
	
	public void seeProfDataSA(ActionEvent event)
	{
		String sel = "";	
		
		if(superadminShowDataNume.getText().equals("") || superadminShowDataPrenume.getText().equals(""))	
			sel = "select * from users where (nume = ? or prenume = ?) and rol = 'profesor'";
		else
			sel = "select * from users where (nume = ? and prenume = ?) and rol = 'profesor'";
		
		try{
			PreparedStatement q = conn.prepareStatement(sel);
			q.setString(1, superadminShowDataNume.getText());
			q.setString(2, superadminShowDataPrenume.getText());
			rs = q.executeQuery();
			
			String finalR = "";
			while(rs.next())
			{
				finalR += "Nume: " + rs.getString("nume") + " | ";
				finalR += "Prenume: " + rs.getString("prenume") + " | ";
				finalR += "CNP: " + rs.getString("cnp") + " | ";
				finalR += "Adresa: " + rs.getString("adresa") + " | ";
				finalR += "Telefon: " + rs.getString("telefon") + " | ";
				finalR += "Email: " + rs.getString("email") + " | ";
				finalR += "IBAN: " + rs.getString("iban") + " | ";
				finalR += "Numar contract: " + rs.getString("nr_contract") + " | ";
				finalR += "Rol: " + rs.getString("rol") + "\n";
			}
			
			if(finalR.equals(""))
				JOptionPane.showMessageDialog(null, "Nu exista date!", "Vizualizare date", 0);
			else
				JOptionPane.showMessageDialog(null, finalR, "Vizualizare date", 1);
			superadminShowDataNume.clear();
			superadminShowDataPrenume.clear();
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}

	}
	
	public void seeAdminDataSA(ActionEvent event)
	{
		String sel = "";	
		
		if(superadminShowDataNume.getText().equals("") || superadminShowDataPrenume.getText().equals(""))	
			sel = "select * from users where (nume = ? or prenume = ?) and rol = 'admin'";
		else
			sel = "select * from users where (nume = ? and prenume = ?) and rol = 'admin'";
		
		try{
			PreparedStatement q = conn.prepareStatement(sel);
			q.setString(1, superadminShowDataNume.getText());
			q.setString(2, superadminShowDataPrenume.getText());
			rs = q.executeQuery();
			
			String finalR = "";
			while(rs.next())
			{
				finalR += "Nume: " + rs.getString("nume") + " | ";
				finalR += "Prenume: " + rs.getString("prenume") + " | ";
				finalR += "CNP: " + rs.getString("cnp") + " | ";
				finalR += "Adresa: " + rs.getString("adresa") + " | ";
				finalR += "Telefon: " + rs.getString("telefon") + " | ";
				finalR += "Email: " + rs.getString("email") + " | ";
				finalR += "IBAN: " + rs.getString("iban") + " | ";
				finalR += "Numar contract: " + rs.getString("nr_contract") + " | ";
				finalR += "Rol: " + rs.getString("rol") + "\n";
			}
			
			if(finalR.equals(""))
				JOptionPane.showMessageDialog(null, "Nu exista date!", "Vizualizare date", 0);
			else
				JOptionPane.showMessageDialog(null, finalR, "Vizualizare date", 1);
			superadminShowDataNume.clear();
			superadminShowDataPrenume.clear();
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}

	}
	
	public void showAssProf(ActionEvent event) {
		assPane.setVisible(true);
	}
	
	public void backAssProf(ActionEvent event) {
		assPane.setVisible(false);
	}
	
	public void assProf(ActionEvent event)
	{
		String exists = "select id_materie from materii where nume_materie =?";
		String ap = "insert into prof_curs(id_prof, nr_stud, id_materie, p_seminar, p_curs, p_lab, max_stud, seminar, curs, lab) values ((select id_user from users where nume = ? "
				+ "and prenume = ?), 0, (select id_materie from materii where nume_materie = ?), ?, ?, ?, ?, ?, ?, ?) ";
		String cm = "insert into materii (nume_materie) values (?)";
		
		int pSeminar, Seminar;
		int pCurs, Curs;
		int pLab, Lab;
		
		if(cbSeminar.isSelected() == true)
		{
			pSeminar = Integer.parseInt(procentajSeminar.getText());
			Seminar = 1;
		}
		else
		{
			pSeminar = 0;
			Seminar = 0;
		}
		if(cbCurs.isSelected() == true)
		{
			pCurs = Integer.parseInt(procentajCurs.getText());
			Curs = 1;
		}
		else
		{
			pCurs = 0;
			Curs = 0;
		}
		if(cbLab.isSelected() == true)
		{
			pLab = Integer.parseInt(procentajLab.getText());
			Lab = 1;
		}
		else
		{
			pLab = 0;
			Lab = 0;
		}
		if(pCurs + pLab + pSeminar != 100)
            JOptionPane.showMessageDialog(null, "Procentajele nu sunt corecte!", "Asignare materie", 0);
        else
        {
            try{
            	PreparedStatement check = conn.prepareStatement(exists);
    			check.setString(1, materieAss.getText());
    			PreparedStatement create = conn.prepareStatement(cm);
    			create.setString(1, materieAss.getText());
    			PreparedStatement q = conn.prepareStatement(ap);
    			q.setString(1, numeAss.getText());
    			q.setString(2, prenumeAss.getText());
    			q.setString(3, materieAss.getText());
    			q.setInt(4, pSeminar);
    			q.setInt(5, pCurs);
    			q.setInt(6, pLab);
    			q.setInt(7, Integer.parseInt(maxStud.getText()));
    			q.setInt(8, Seminar);
    			q.setInt(9, Curs);
    			q.setInt(10, Lab);
    			
    			rs = check.executeQuery();
    			if(rs.next())
    			{
    				q.execute();
    			}
    			else
    			{
    				create.execute();
    				q.execute();
    			}
    			
    			
    			JOptionPane.showMessageDialog(null, "Materia a fost asignata cu succes!", "Asignare materie", 1);
    			numeAss.clear();
    			prenumeAss.clear();
    			materieAss.clear();
    			maxStud.clear();
    			procentajCurs.clear();
    			procentajSeminar.clear();
    			procentajLab.clear();
    			cbCurs.setSelected(false);
    			cbSeminar.setSelected(false);
    			cbLab.setSelected(false);

            } catch (Exception e) {
                JOptionPane.showMessageDialog(null, e);
            }
        }
		
	}
	
	public void showCS(ActionEvent event) {
		csPane.setVisible(true);
	}
	
	public void backCS(ActionEvent event) {
		csPane.setVisible(false);
		materieCS.clear();
		tableCS.getItems().clear();
	}
	
	public void seeCourseStudents(ActionEvent event)
	{
		String getProf = "select nume, prenume from users where id_user in (select id_prof from prof_curs inner join materii on materii.id_materie = prof_curs.id_materie where "
				+ "nume_materie = ?) ";
		String SS="select A.id_user, A.nume, A.prenume, A.an from (select A.id_user, A.nume, A.prenume, B.an from users as A inner join studenti as B on A.id_user = B.id_student) "
				+ "as A inner join curs_student as B on B.id_student=A.id_user where id_curs = (select id_curs from prof_curs where id_materie = (select id_materie from materii where "
				+ "nume_materie = ?) and id_prof = (select id_user from users where nume = ? and prenume = ? limit 1)) ";
		
		
		String[] profi = new String[10];
		String numeProf = "";
		
		try {
			int i = 0;
			PreparedStatement gp = conn.prepareStatement(getProf);
			gp.setString(1, materieCS.getText());
			rs = gp.executeQuery();
			while(rs.next())
			{
				 numeProf += rs.getString("nume") + " ";
				 numeProf += rs.getString("prenume");
				 profi[i] = numeProf;
				 i++;
				 numeProf = "";
			}
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
		
		Object returnValue = JOptionPane.showInputDialog(null, "Alegeti numele profesorului a carei materie diriti sa-l vizualizati", "Vizualizare studenti la curs", 1, null, profi, 
				profi[0]);
		String profAles = returnValue.toString();
		
		String[] parts = new String[2];
		parts = profAles.split(" ");
		String nume = parts[0];
		String prenume = parts[1];
		
		if(profAles != null)
		{
			profAles = returnValue.toString();
		
			try{
				PreparedStatement q = conn.prepareStatement(SS);
				q.setString(1, materieCS.getText());
				q.setString(2, nume);
				q.setString(3, prenume);
				rs = q.executeQuery();
				
				lastNameColumnCS.setCellValueFactory(new PropertyValueFactory<>("lastName"));
				firstNameColumnCS.setCellValueFactory(new PropertyValueFactory<>("firstName"));
					
				ObservableList<CSData> cSData = FXCollections.observableArrayList();
				
				while(rs.next())
				{
					String lastName = rs.getString("nume");
					String firstName = rs.getString("prenume");
					cSData.add(new CSData(lastName, firstName));	
				}
				tableCS.setItems(cSData);
				
			} catch (Exception e) {
				JOptionPane.showMessageDialog(null, e);
			}
		}
	}
	
	@FXML
	private AnchorPane susPane;
	
	@FXML
	private TextField numeProfSUS;
	
	@FXML
	private TextField prenumeProfSUS;
	
	@FXML
	private TextField materieSUS;
	
	@FXML
	private TextField numeStudSUS;
	
	@FXML
	private TextField prenumeStudSUS;
	
	@FXML
	private Button signUpStud;
	
	@FXML
	private Button backSUSButton;
	
	@FXML
	private Button adminShowSUSButton;
	
	@FXML
	private Button superadminShowSUSButton;
	
	public void showSUS(ActionEvent event) {
		susPane.setVisible(true);
	}
	
	public void backSUS(ActionEvent event) {
		susPane.setVisible(false);
	}
	
	public void signUpStudent(ActionEvent event) {
		String sup = "insert into curs_student (id_curs, id_student, nota_finala) values ((select A.id_curs from prof_curs as A where id_prof = (select id_user from users where nume = ? "
				+ "and prenume = ?) and id_materie = (select id_materie from materii where nume_materie = ?)), (select id_user from users where nume = ? and prenume =?), 0)";
		try{
			PreparedStatement s = conn.prepareStatement(sup);
			s.setString(1, numeProfSUS.getText());
			s.setString(2, prenumeProfSUS.getText());
			s.setString(3, materieSUS.getText());
			s.setString(4, numeStudSUS.getText());
			s.setString(5, prenumeStudSUS.getText());
			s.execute();
			JOptionPane.showMessageDialog(null, "Studentul a fost intregistrat cu succes!", "Integisrare studenti la curs", 1);
			
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
	
	}

	@FXML
	private Button showSuggestedButton;
	
	
	public void showSuggestions(ActionEvent event)
    {
        String suggest = "select nume, prenume from users where id_user in (select id_student from curs_student inner join prof_curs on curs_student.id_curs = prof_curs.id_curs "
        		+ "where prof_curs.id_curs in (select prof_curs.id_materie from prof_curs inner join materii on prof_curs.id_materie = materii.id_materie where nume_materie = ?)) "
        		+ "limit 5;";
        
        String getMat = "select nume_materie from materii inner join (select C.id_materie from (select A.id_materie from prof_curs as A inner join curs_student as B on A.id_curs = "
				+ "B.id_curs where B.id_student = (select id_user from users where email = ?)) as C) as D on materii.id_materie = D.id_materie";
		String[] cursuri = new String[50];
		String cursAles = "";
		
		try {
			int i = 0;
			PreparedStatement gm = conn.prepareStatement(getMat);
			gm.setString(1, emailLogin.getText());
			rs = gm.executeQuery();
			while(rs.next())
			{
				cursAles += rs.getString("nume_materie");
				cursuri[i] = cursAles;
				i++;
				cursAles = "";
			}
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
        
		Object returnValue = JOptionPane.showInputDialog(null, "Alege numele materiei pentru a carei grup vrei sa vezi sugetii de noi membrii", "Sugestii studenti in grup", 1, 
				null, cursuri, cursuri[0]);
		
		if(returnValue != null)
		{
			cursAles = returnValue.toString();
        
	        try{
		            PreparedStatement s = conn.prepareStatement(suggest);
		            s.setString(1, cursAles);
		            rs = s.executeQuery();
		            
		            String finalR = "";
		            
		            while(rs.next())
		            {
		            	finalR += "Nume: " + rs.getString("nume") + " | ";
						finalR += "Prenume: " + rs.getString("prenume") + "\n";
					}
					
					if(finalR.equals(""))
						JOptionPane.showMessageDialog(null, "Nu exista recomandari de studenti!", "Sugestii studenti in grup", 0);
					else
						JOptionPane.showMessageDialog(null, finalR, "Sugestii studenti in grup", 1);
		            
	        } catch (Exception e) {
				JOptionPane.showMessageDialog(null, e);
			}
		}
    }
	
	@FXML
	private Button fgButton;
	
	public void getFinalGrades(ActionEvent event)
	{
		String gfg = "select nume_materie , nota_finala from curs_student inner join (select id_curs, nume_materie from prof_curs inner join materii on "
				+ "prof_curs.id_materie=materii.id_materie) as B on B.id_curs=curs_student.id_curs where id_student=(select id_user from users where email = ?)";
		
		try{
            PreparedStatement s = conn.prepareStatement(gfg);
            s.setString(1, emailLogin.getText());
            rs = s.executeQuery();
            
            String finalR = "";
            
            while(rs.next())
            {
            	finalR += "Materie: " + rs.getString("nume_materie") + " | ";
				finalR += "Nota finala: " + rs.getString("nota_finala") + "\n";
			}
			
			if(finalR.equals(""))
				JOptionPane.showMessageDialog(null, "Nu aveti nici o nota finala!", "Vizualizare note finale", 0);
			else
				JOptionPane.showMessageDialog(null, finalR, "Vizualizare note finale", 1);
            
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
	}
	
	public void viewToday() {
		String va="select distinct A.titlu, A.data from activitati_grup as A inner join grup_student as B on A.id_curs = B.id_curs where date(A.data) = (select DATE(NOW())) and "
				+ "(B.id_student = (select id_user from users where email =?) or A.id_prof = (select id_user from users where email =?));";
		
        String vp="select A.tip, B.nume_materie, date(A.data) from programari as A inner join (select A.nume_materie, B.id_curs from materii as A inner join prof_curs "
        		+ "as B on A.id_materie=B.id_materie where B.id_prof = (select id_user from users where email =?) or B.id_curs in (select id_curs "
        		+ "from curs_student where id_student = (select id_user from users where email =?))) as B on A.id_curs = B.id_curs where date(A.data) = (select date(now()))";
        try{
        	
        	PreparedStatement sva = conn.prepareStatement(va);
        	sva.setString(1, emailLogin.getText());
        	sva.setString(2, emailLogin.getText());
            rs = sva.executeQuery();//activitati grup
            
            String frs = "Activitati astazi:\n";
            
            while(rs.next())
            {
            	frs += rs.getString("titlu") + " | ";
            	frs += rs.getString("data") + "\n";
            }
            
            
            PreparedStatement svp = conn.prepareStatement(vp);
        	svp.setString(1, emailLogin.getText());
        	svp.setString(2, emailLogin.getText());
            rs = svp.executeQuery();//activitati grup
            
            
            while(rs.next())
            {
            	frs += rs.getString("tip") + " | ";
            	frs += rs.getString("nume_materie") + "\n";
            	
            }
            studentTodayLabel.setText(frs);
            profTodayLabel.setText(frs);

        } catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
	}
	
	@FXML
	private AnchorPane assignDepPane;
	
	@FXML
	private TextField numeAssignDep;
	
	@FXML
	private TextField prenumeAssignDep;
	
	@FXML
	private TextField departament;
	
	@FXML
	private Button assignDepButton;
	
	@FXML
	private Button showAssignDepA;
	
	@FXML
	private Button showAssignDepSA;
	
	@FXML
	private Button backAssignDep;
	
	public void showAssignDepPane(ActionEvent event) {
		assignDepPane.setVisible(true);
	}
	
	public void hideAssignDepPane(ActionEvent event) {
		assignDepPane.setVisible(false);
		numeAssignDep.clear();
		prenumeAssignDep.clear();
		departament.clear();
	}
	
	public void assignDep(ActionEvent event) {
		String sd = "update profesori set departament = ? where id_profesor = (select id_user from users where nume=? and prenume=? and rol='profesor') ";
		
		try {
			PreparedStatement sdp = conn.prepareStatement(sd);
			sdp.setString(1, departament.getText());
			sdp.setString(2, numeAssignDep.getText());
			sdp.setString(3, prenumeAssignDep.getText());
			sdp.execute();
			JOptionPane.showMessageDialog(null, "Departamentul a fost asignat cu succes!", "Asignare departament profesor", 1);
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}
		
	}
	
}