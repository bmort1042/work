package views;

// File Name: Singleton.java
public class Singleton {

   private static Singleton singleton = new Singleton( );

   /* A private Constructor prevents any other
    * class from instantiating.
    */
   private Singleton() { }

   /* Static 'instance' method */
   public static Singleton getInstance( ) {
      return singleton;
   }
   
	protected String states[] = {"Alabama", "Alaska", "Arizona", "Arkansas", "Califronia", "Connecticut",
			"Delaware", "Florida", "Georgia", "Hawaii", "Idaho", "Illinois", "Indiana", "Iowa",
			"Kansas", "Kentucky", "Louisiana", "Maine", "Maryland", "Massachusetts", "Michigan",
			"Minnesota", "Mississippi", "Missouri", "Montana", "Nebraska", "Nevada", "New Hampshire",
			"New Jersey", "New Mexico", "New York", "North Carolina", "North Dakota", "Ohio",
			"Oklahoma", "Oregon", "Pennsylvania", "Rhode Island", "South Carolina", "South Dakota",
			"Tennessee", "Texans", "Utah", "Vermont", "Virginia", "Washington", "West Virginia",
			"Wisconsin", "Wyoming"
	};

   /* Other methods protected by singleton-ness */
   protected static void demoMethod( ) {
      System.out.println("demoMethod for singleton");
   }
}