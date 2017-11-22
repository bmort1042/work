package views;

import gov.nasa.worldwind.avlist.AVKey;
import gov.nasa.worldwind.geom.Position;
import gov.nasa.worldwind.layers.*;
import gov.nasa.worldwind.render.PointPlacemark;
import gov.nasa.worldwindx.examples.util.BalloonController;
import gov.nasa.worldwindx.examples.util.HotSpotController;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Observer;
import java.util.Vector;
import java.util.Enumeration;
import java.util.Locale;

import views._severity;
import javax.swing.JFrame;

import java.util.Observable;

public class Map implements Observer {
  
	// all variable kept track of from pannels(should have a singleton)
	protected int typeFlag = -1;// 0 if Search panel 1 if rss pannel update
    protected String search_time;
    protected String search_state;
    protected String search_city;
    protected String add_State;
    protected String remove_State;
    protected String search_severity;
    protected String search_certainty;
	protected int refreshRate; 
	protected String search_event;
	
	// time date to convert time from strings to java date to compare to 
	// Alert times
	protected SimpleDateFormat defaultDateFormat;
	protected java.util.Date search_TimeDate;

	protected ArrayList<ArrayList<SomeAlert>> states_Rendered;
	
	// passed from gui
	protected RenderableLayer layer0 = null;
	protected ArrayList<ArrayList<SomeAlert>> statesList;
	
   //protected Vector<SomeAlert> listOfAlerts; // Using a vector of alerts 
    protected Vector<SomeAlert> renderedList;
	public Map(RenderableLayer layer0) 
	{
		super();
        defaultDateFormat = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ssZ");
		this.layer0 = layer0;
		initializeStateList();
		initializeVaribles();
		
		this.renderedList = new Vector<SomeAlert>();
		//this.listOfAlerts = new Vector<SomeAlert>();
		hardcodedShit();

	}

	@Override
	public void update(Observable o, Object arg) {
	
		if(o instanceof Search_Panel){
			Search_Panel search = (Search_Panel)arg;	
				typeFlag = 0;
				if(true)//search.time != null)
				{
					//search_time = search.time;
/////****************************DEBUG      ***********************2001-07-04T12:08:56.235-0700

					try {
			            this.search_TimeDate =  defaultDateFormat.parse(search_time);
			        }
					catch (java.text.ParseException e) {
			            this.search_TimeDate = null;
			            e.printStackTrace();
					}
				}
				if(search.state != null)
				{
					search_state = search.state;
				}
				else
				{
					if(search_state == null)
						search_state = "Washington";
				}
				
				if(search.city != null)
				{
					search_city = search.city;
				}
				if(search.severity != null)
				{
					search_severity = search.severity;
				}
				if(search.certainty != null)
				{
					search_certainty = search.certainty;
				}
				if(search.event != null)
				{
					search_event = search.event;
				}
				updateMap(typeFlag);
			
		}
		
		if(o instanceof RSS_Panel)
		{
			RSS_Panel rss = (RSS_Panel)arg;
				//layer0.removeAllRenderables();
				//renderedList.clear();
				typeFlag = 1;
				if(rss.remove != null)
				{
					remove_State = rss.remove;
				}
				if(rss.add != null)
				{
					add_State = rss.add;
				}
				for(int i = 0; i < 6; i++)
				{
					if(rss.refreshRate[i] == true)
					{
						refreshRate = i;
						break;
					}
				
			    }
				updateMap(typeFlag);
			
			
			}
	}
		
	
	protected void initializeVaribles()
	{
		search_time = "2017-01-21T19:00:00-0700";
		search_state = "Washington";
		search_city = null;
		add_State = null;
		remove_State = null;
		search_severity = null;
		search_certainty = null;
		refreshRate = 0; 
		search_event = null;
	}
	
	protected void initializeStateList()
	{
		statesList = new ArrayList<ArrayList<SomeAlert>>() ;
		ArrayList<SomeAlert> Alabama = new ArrayList<SomeAlert>();
		statesList.add(Alabama);
		ArrayList<SomeAlert> Alaska = new ArrayList<SomeAlert>();
	    statesList.add(Alaska);
	    ArrayList<SomeAlert> Arizona = new ArrayList<SomeAlert>();
		statesList.add(Arizona);
		ArrayList<SomeAlert> Arkansas = new ArrayList<SomeAlert>();
		statesList.add(Arkansas);
		ArrayList<SomeAlert> California = new ArrayList<SomeAlert>();
		statesList.add(California);
		ArrayList<SomeAlert> Colorado = new ArrayList<SomeAlert>();
		statesList.add(Colorado);
		ArrayList<SomeAlert> Connecticut = new ArrayList<SomeAlert>();
		statesList.add(Connecticut);
		ArrayList<SomeAlert> Delaware = new ArrayList<SomeAlert>();
		statesList.add(Delaware);
		ArrayList<SomeAlert> Florida = new ArrayList<SomeAlert>();
		statesList.add(Florida);
		ArrayList<SomeAlert> Georgia = new ArrayList<SomeAlert>();
		statesList.add(Georgia);
		ArrayList<SomeAlert> Hawaii = new ArrayList<SomeAlert>();
		statesList.add(Hawaii);
		ArrayList<SomeAlert> Idaho = new ArrayList<SomeAlert>();
		statesList.add(Idaho );
		ArrayList<SomeAlert> Illinois = new ArrayList<SomeAlert>();
		statesList.add(Illinois );
		ArrayList<SomeAlert> Indiana = new ArrayList<SomeAlert>();
		statesList.add(Indiana );
		ArrayList<SomeAlert> Iowa = new ArrayList<SomeAlert>();
		statesList.add(Iowa);
		ArrayList<SomeAlert> Kansas = new ArrayList<SomeAlert>();
		statesList.add(Kansas);
		ArrayList<SomeAlert> Kentucky = new ArrayList<SomeAlert>();
		statesList.add( Kentucky);
		ArrayList<SomeAlert> Louisiana = new ArrayList<SomeAlert>();
		statesList.add( Louisiana);
		ArrayList<SomeAlert> Maine = new ArrayList<SomeAlert>();
		statesList.add(Maine );
		ArrayList<SomeAlert> Maryland = new ArrayList<SomeAlert>();
		statesList.add( Maryland);
		ArrayList<SomeAlert> Massachusetts = new ArrayList<SomeAlert>();
		statesList.add(Massachusetts);
		ArrayList<SomeAlert> Michigan = new ArrayList<SomeAlert>();
		statesList.add( Michigan);
		ArrayList<SomeAlert> Minnesota = new ArrayList<SomeAlert>();
		statesList.add(Minnesota );
		ArrayList<SomeAlert> Mississippi = new ArrayList<SomeAlert>();
		statesList.add( Mississippi);
		ArrayList<SomeAlert>Missouri  = new ArrayList<SomeAlert>();
		statesList.add( Missouri);
		ArrayList<SomeAlert> Montana = new ArrayList<SomeAlert>();
		statesList.add( Montana);
		ArrayList<SomeAlert> Nebraska = new ArrayList<SomeAlert>();
		statesList.add(Nebraska );
		ArrayList<SomeAlert> Nevada = new ArrayList<SomeAlert>();
		statesList.add( Nevada);
		ArrayList<SomeAlert> New_Hampshire = new ArrayList<SomeAlert>();
		statesList.add(New_Hampshire );
		ArrayList<SomeAlert> New_Jersey = new ArrayList<SomeAlert>();
		statesList.add(New_Jersey );
		ArrayList<SomeAlert> New_Mexico = new ArrayList<SomeAlert>();
		statesList.add(New_Mexico );
		ArrayList<SomeAlert> New_York = new ArrayList<SomeAlert>();
		statesList.add(New_York );
		ArrayList<SomeAlert> North_Carolina = new ArrayList<SomeAlert>();
		statesList.add(North_Carolina );
		ArrayList<SomeAlert> North_Dakota = new ArrayList<SomeAlert>();
		statesList.add(North_Dakota );
		ArrayList<SomeAlert> Ohio = new ArrayList<SomeAlert>();
		statesList.add( Ohio);
		ArrayList<SomeAlert> Oklahoma = new ArrayList<SomeAlert>();
		statesList.add(Oklahoma );
		ArrayList<SomeAlert> Oregon = new ArrayList<SomeAlert>();
		statesList.add(	Oregon );
		ArrayList<SomeAlert> Pennsylvania = new ArrayList<SomeAlert>();
		statesList.add(Pennsylvania );
		ArrayList<SomeAlert> Rhode_Island = new ArrayList<SomeAlert>();
		statesList.add(Rhode_Island );
		ArrayList<SomeAlert> South_Carolina = new ArrayList<SomeAlert>();
		statesList.add(South_Carolina );
		ArrayList<SomeAlert> South_Dakota = new ArrayList<SomeAlert>();
		statesList.add(South_Dakota );
		ArrayList<SomeAlert> Tennessee = new ArrayList<SomeAlert>();
		statesList.add( Tennessee);
		ArrayList<SomeAlert> Texas = new ArrayList<SomeAlert>();
		statesList.add(Texas );
		ArrayList<SomeAlert> Utah = new ArrayList<SomeAlert>();
		statesList.add(Utah );
		ArrayList<SomeAlert> Vermont = new ArrayList<SomeAlert>();
		statesList.add( Vermont);
		ArrayList<SomeAlert> Virginia = new ArrayList<SomeAlert>();
		statesList.add(Virginia );
		ArrayList<SomeAlert> Washington = new ArrayList<SomeAlert>();
		statesList.add(Washington );
		ArrayList<SomeAlert> West_Virginia = new ArrayList<SomeAlert>();
		statesList.add( West_Virginia);
		ArrayList<SomeAlert> Wisconsin = new ArrayList<SomeAlert>();
		statesList.add(Wisconsin );
		ArrayList<SomeAlert> Wyoming = new ArrayList<SomeAlert>();
		statesList.add(Wyoming );
		
	};

	public int state_Mask(String state)
	{
		switch(state)
		{
		case "Alabama":
			return 1;
			
		case "Alaska":
			return 2;
			
		case "Arizona":
			return 3;
			
		case "Arkansas":
			return 4;
			
		case "California":
			return 5;
			
		case "Colorado":
			return 6;
			
		case "Connecticut":
			return 7;
			
		case "Delaware":
			return 8;
			
		case "Florida":
			return 9;
			
		case "Georgia":
			return 10;
		
		case "Hawaii":
			return 11;
			
		case "Idaho":
			return 12;
			
		case "Illinois":
			return 13;
			
		case "Indiana":
			return 14;
			
		case "Iowa":
			return 15;
			
		case "Kansas":
			return 16;
		
		case "Kentucky":
			return 17;
		
		case "Louisiana":
			return 18;
			
		case "Maine":
			return 19;
		
		case "Maryland":
			return 20;
			
		case "Massachusetts":
			return 21;
			
		case "Michigan":
			return 22;
			
		case "Minnesota":
			return 23;
			
		case "Mississippi":
			return 24;
			
		case "Missouri":
			return 25;
			
		case "Montana":
			return 26;
			
		case "Nebraska":
			return 27;
			
		case "Nevada":
			return 28;
		
		case "New Hampshire":
			return 29;
			
		case "New Jersey":
			return 30;
			
		case "New Mexico":
			return 31;
			
		case "New York":
			return 32;
			
		case "North Carolina":
			return 33;
		
		case "North Dakota":
			return 34;
			
		case "Ohio":
			return 35;
			
		case "Oklahoma":
			return 36;
			
		case "Oregon":
			return 37;
			
		case "Pennsylvania":
			return 38;
			
		case "Rhode Island":
			return 39;
			
		case "South Carolina":
			return 40;
			
		case "South Dakota":
			return 41;
			
		case "Tennessee":
			return 42;
			
		case "Texas":
			return 43;
		
		case "Utah":
			return 44;
			
		case "Vermont":
			return 45;
			
		case "Virginia":
			return 46;
			
		case "Washington":
			return 47;
			
		case "West Virginia":
			return 48;
			
		case "Wisconsin":
			return 49;
			
		case "Wyoming":
			return 50;
			
		default:
		    return -1;
		
		}
		
	}
	
	
	public void updateMap(int type_Flag){
	 
	
		//here is where I will check the singleton values to update the layer acordingly
		// I am planning on adjusting the vector only when the feed is updated. 
		// maybe have the feed object update/maintain the vector of alerts
		// This class will only need to search the vector(lol) and add/remove apropriatly
		// from the layer0
	
		// Two switch cases for alert type and severity
	
		System.out.print("in updateMap\n\n");

		switch(type_Flag)
		{
			case -1:
				break;
				
			case 0: // Search Pannel updated
				if( search_state != null)
				{
					System.out.print(search_state);
	
					// boolean to see if alert was added to map
					boolean added = false;
					// Clear render list & layer to fill again
					if(!(renderedList.isEmpty()))
							renderedList.clear();
					layer0.removeAllRenderables();
	
					// Walk through arrayList of alerts for selected state
					for(SomeAlert a: statesList.get(state_Mask(search_state)))
					{
						
						System.out.print(a.getEvent());
						// check alert severity
						if(search_severity != null)
							if(a.getSeverity() == search_severity)
								added = true;
					
						//check alert event
						if(search_event != null)
							if(a.getEvent() == search_event)
								added = true;
						
						//check alert certainty
						if(search_certainty != null)
							if(a.getCertainty() == search_certainty)
								added = true;
						
						// check if alert expires before users requested 
						// filter time
						if(search_time != null)
						{
							if(search_TimeDate.before(a.getTimeExpires()))
							{
								added = true;
							}
							else
								added = false;
						} 
						 if(added)
						 {	
							 // check allert a and add polygon & placemark
							 if(a.getSomePoly() != null)
							 {
								   layer0.addRenderable(a.getSomePoly());
							 }
							 if(a.getSomeBalloon() != null)
							 {  
								 layer0.addRenderable(a.getSomeBalloon());
								 layer0.addRenderable(a.getSomePlacemark());
							 }
							  renderedList.add(a);
						  }
					}
					return;
				}
				else
					return;
				
			case 1: // RSS panel updated
				if( remove_State != null)
				{
	//				states_Rendered.remove(remove_State);
	//				for(String a: states_Rendered)
	//				{
	//					
	//				}
	//				
	//				for(SomeAlert a: statesList.get(statesList.indexOf(remove_State)))
	//				{
	//										
	//				}
				}
				if(add_State != null)
				{
	//				for(SomeAlert a: statesList.get(statesList.indexOf(add_State)))
	//				{
	//					if(a.getSeverity() != severity)
	//					{
	//						if(!listOfAlerts.remove(a))
	//							System.out.print("failed to remove Alert");
	//					}
	//				}
				}
			
				break;
			default:
			   break;
			}
		
		
		
		
	
		
			
					
	

		  // walk through vector of Alerts adding polygons & balloons to layer
//		   for(SomeAlert a: statesList.get(state_Mask("Washington")))
//		   {    
//			   if(a.getSomePoly() != null)
//			   {
//				   layer0.addRenderable(a.getSomePoly());
//			   }
//			   if(a.getSomeBalloon() != null)
//			   {  
//				   layer0.addRenderable(a.getSomeBalloon());
//			       layer0.addRenderable(a.getSomePlacemark());
//			    }
//		    
//		    // Add polygon to layer
//		    }
	
		}
	
	
	
	// Bad Ass function to return an ArrayList of position from a variable(mulitple of 2)
	// number of double arguments. /***/// TOdo error checking!!
	public ArrayList<Position> positionArrayFromDegrees(Double...args){
		
		if(args.length < 2)
		{
			return null;
		}
		// create an arrayList of position out of an even number of lat/long parameters
		ArrayList<Position> pathLocations = new ArrayList<Position>();
		pathLocations.add(Position.fromDegrees(args[0], args[1], 0));			
		for(int i = 2; i < args.length; i++)
		{
			pathLocations.add(Position.fromDegrees(args[i], args[++i], 100e3));			
		}
		return pathLocations;
		
		}

	


		public RenderableLayer getLayer0() {
			return layer0;
		}


		public void setLayer0(RenderableLayer layer0) {
			this.layer0 = layer0;
		}


//		public Vector<SomeAlert> getListOfAlerts() {
//			return listOfAlerts;
//		}
//
//
//		public void setListOfAlerts(Vector<SomeAlert> listOfAlerts) {
//			this.listOfAlerts = listOfAlerts;
//		}
//     
//        
	

		
		
		// What follows is an attempt at hardcoding what is needed from the RSS feed. 
		protected void 	hardcodedShit()
		{
		
			//  public SomeAlert(String summary,String link,String event,
			//	String urgency, String severity, String timeExpires,
			//  ArrayList<Position> positions)
			//  public SomeAlert(String summary,String link,String event, String urgency, 
			//	String severity, String timeExpires,ArrayList<Position> positions)
			
			SomeAlert oneAlert = new SomeAlert("...WIND ADVISORY NOW IN EFFECT UNTIL" +
					" 8 PM PDT THIS EVENING ABOVE 2000 FEET... * WINDS...Gusts up to 50 " +
					"mph across exposed ridges. * LOCATIONS INCLUDE...Kneeland. *" +
					" HIGHWAY(S) IMPACTED...Hwy 299 over Berry Summit. * FOR A DETAILED " +
					"VIEW OF THE HAZARD AREA...visit", "https://alerts.weather.gov/cap/wwacapget.php?" +
					"x=CA125844C5C868.WindAdvisory.125844D1EB70CA.EKANPWEKA.830676a3c9b48d" +
					"c4647a750cdbeb6dd7", "Wind Advisory","Expected","Minor","2017-03-20T20:00:00-07:00","2017-03-21T19:00:00-07:00",
					positionArrayFromDegrees(41.2704,-122.1846));
					
			statesList.get(state_Mask("Washington")).add(oneAlert);
			
			SomeAlert twoAlert = new SomeAlert("...Stormy Spring Weather Pattern Returns" +
					" Through the Week... After recent very warm spring weather, stormy " +
					"weather will return this week with periods of gusty winds, " +
					"rain, mountain snow, and much cooler temperatures." +
					" The first storm is expected Tuesday with a second, " +
					"potentially stronger storm, for the end of the week. * " +
					"Timing: Precipitation will begin in the Sierra late tonight with",
					"https://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/1.0_week_age_link.kml",
					"Special Weather Statement","Future","Minor", 
					"2017-03-21T19:00:00-07:00","2017-03-21T19:00:00-07:00", positionArrayFromDegrees(38.7829,
							-119.3423,39.7829,-120.3423,37.939,-118.8867,38.7829,
							-120.3423,39.2829,-121.3423));
			statesList.get(state_Mask("Washington")).add(twoAlert);
			
			SomeAlert threeAlert = new SomeAlert("Well, the balloon is rendered, poly drawn, I do believe thats an A!", 
					"https://google.com", "Special Weather Statement", "Future", "Uknown", "2017-03-21T19:00:00-07:00",
					"2017-03-21T19:00:00-07:00", positionArrayFromDegrees(40.1971,-121.3501,41.8639,
							-122.9371,40.1971,-123.3501,38.7829,-120.3423));
			statesList.get(state_Mask("Washington")).add(threeAlert);
			
		}

}

