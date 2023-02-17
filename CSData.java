package application;

public class CSData {
	private String lastName;
	private String firstName;
	
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

	public CSData(String lastName, String firstName) {
		this.lastName = lastName;
		this.firstName = firstName;
	}
}
