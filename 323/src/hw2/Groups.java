package hw2;

import java.util.ArrayList;

import hw2.Division;

public class Groups implements Division{
	
	String groupName;
	ArrayList<Division> division = new ArrayList<>();
	
	public Groups(String groupName) {
		super();
		this.groupName = groupName;
	}

	@Override
	public void printSalary() {
		System.out.println("Group Name: " + getName() + "\n");
		System.out.println("Salaries");
		
		for(Division d : division){
			d.printSalary();
		}
		System.out.println("-------------------------------------------------------------");
		
	}

	@Override
	public double getSalary() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public String getName() {
		return this.groupName;
	}

	@Override
	public void addComponent(Division div) {
		division.add(div);
		
	}
	
}