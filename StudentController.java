public void signUpCourse(ActionEvent event) {

  String getMat = "select A.nume_materie from materii as A outer "
      + "join (select A.id_materie from prof_curs as A inner join "
      + "curs_student as B on A.id_curs=B.id_curs where B.id_student = "
      + "(select id_user from users where mail =?)) as C on C.id_materie = A.id_materie";
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
