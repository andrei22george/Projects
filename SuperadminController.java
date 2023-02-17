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
