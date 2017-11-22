package hw2;

import java.util.ArrayList;

import hw2.Groups;

public class Company{
	public static void main(String[] args){
		
		Division emp0 = new Employee("Kenny", 115000);
		Division emp1 = new Employee("Kesh", 300000);
		Division emp2 = new Employee("Tayler", 100000);
		Division emp3 = new Employee("Bri", 10000000);
		Division emp4 = new Employee("Royal", 85000);
		Division emp5 = new Employee("Mikael", 10000000);
		Division emp6 = new Employee("Wade", 15000);
		
		Division com = new Groups("Evil");
		Division hr = new Groups("Human Resources");
		Division pr = new Groups("Payroll");
		Division div = new Groups("Divison");
		Division sw = new Groups("Software");
		Division admin = new Groups("Administration");
		
		com.addComponent(hr);
		com.addComponent(pr);
		com.addComponent(div);
		com.addComponent(sw);
		com.addComponent(admin);
		com.addComponent(emp2);
		hr.addComponent(emp0);
		pr.addComponent(emp1);
		div.addComponent(emp3);
		sw.addComponent(emp3);
		sw.addComponent(emp4);
		sw.addComponent(emp5);
		admin.addComponent(emp6);
		
		
		Payroll roll = new Payroll(com);
		
		roll.printSalary();
			
		
	}
}