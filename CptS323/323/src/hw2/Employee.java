package hw2;

public class Employee implements Division{
	
	private String name;
	private double salary;
	
	public Employee(String name, double salary){
		this.name = name;
		this.salary = salary;
	}

	@Override
	public void printSalary() {
		System.out.println(getName() + " : " + getSalary() + "\n");
	}

	@Override
	public double getSalary() {
		return this.salary;
	}

	@Override
	public String getName() {
		return this.name;
	}

	@Override
	public void addComponent(Division div) {
		// TODO Auto-generated method stub
		
	}
	
}