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
