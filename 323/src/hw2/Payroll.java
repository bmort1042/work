package hw2;

public class Payroll{
	
	Division companyList;
	
	public Payroll(Division companyList) {
		super();
		this.companyList = companyList;
	}
	
	public void printSalary(){
		companyList.printSalary();
	}
	
}