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
