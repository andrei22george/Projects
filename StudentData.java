package application;

public class StudentData {
	private String lastName;
	private String firstName;
	private String materie;
	private String tipulActivitatii;
	private float nota;
	
	public StudentData(String lastName, String firstName, String materie, String tipulActivitatii, float nota) {
		this.lastName = lastName;
		this.firstName = firstName;
		this.materie = materie;
		this.tipulActivitatii = tipulActivitatii;
		this.nota = nota;
	}

	public String getLastName() {
		return lastName;
	}

	public void setLastName(String lastName) {
		this.lastName = lastName;
	}

	public String getFirstName() {
		return firstName;
	}

	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	public String getMaterie() {
		return materie;
	}

	public void setMaterie(String materie) {
		this.materie = materie;
	}

	public String getTipulActivitatii() {
		return tipulActivitatii;
	}

	public void setTipulActivitatii(String tipulActivitatii) {
		this.tipulActivitatii = tipulActivitatii;
	}

	public float getNota() {
		return nota;
	}

	public void setNota(float nota) {
		this.nota = nota;
	}
	
	
}
