package teama;

import gov.nasa.worldwind.avlist.AVKey;
import gov.nasa.worldwind.geom.Position;
import gov.nasa.worldwind.layers.*;
import gov.nasa.worldwind.render.PointPlacemark;
import gov.nasa.worldwindx.examples.util.BalloonController;
import gov.nasa.worldwindx.examples.util.HotSpotController;

import java.util.ArrayList;
import java.util.Observer;
import java.util.Vector;
import java.util.Enumeration;
import views._severity;
import javax.swing.JFrame;

import java.util.Observable;

public class Map implements Observer {
  
	protected int typeFlag = -1;// 0 if Search panel 1 if rss pannel update
	protected RenderableLayer layer0 = null;
	protected ArrayList<ArrayList<SomeAlert>> statesList;
    protected Vector<SomeAlert> listOfAlerts; // Using a vector of alerts 
    protected Vector<SomeAlert> renderedList;
	public Map(RenderableLayer layer0) 
	{
		super();
		this.layer0 = layer0;
		this.listOfAlerts = new Vector<SomeAlert>(); 
	}

	@Override
	public void update(Observable o, Object arg) {
	
		if(o instanceof Search_Panel){
			Search_Panel search = (Search_Panel)arg;
			
			if(true)
			{	
				//layer0.removeAllRenderables();
				//renderedList.clear();
				typeFlag = 0;
				updateMap();
			}
		}
		
		if(o instanceof RSS_Panel)
		{
			RSS_Panel rss = (RSS_Panel)arg;
			if(true)
			{
				//layer0.removeAllRenderables();
				//renderedList.clear();
				typeFlag = 0;
				if(true)
				{
					
				}
				if(true)
				{
				
				}
				for(int i = 0; i < 6; i++)
				{
					if(true)
					{
						
					}
				
			    }
				updateMap();
			}
			
		}
	}
		
	
	
	public void updateMap(){
	;
		
//		_alertType alert_Some = null;
//		_severity Severity = null;
//		String severity = null;
//		String alertType = null;
//	
//		//here is where I will check the singleton values to update the layer acordingly
		// I am planning on adjusting the vector only when the feed is updated. 
		// maybe have the feed object update/maintain the vector of alerts
		// This class will only need to search the vector(lol) and add/remove apropriatly
		// from the layer0
	
//		switch(type_Flag)
//		{
//		case -1:
//			break;
//			
//		case 0: // Search Pannel updated
//			if()
//			if( != null)
//			{
//				for(SomeAlert a: listOfAlerts)
//				{
//					if(a.getSeverity() != severity)
//					{
//						if(!listOfAlerts.remove(a))
//							System.out.print("failed to remove Alert");
//					}
//				}
//			}
//			
//			
//			
//			
//			
//			
//			break;
//		case 1: // RSS panel updated
//			
//		
//			break;
//		default:
//		   break;
//		}
//		
//		
//		
//		
//		// Two switch cases for alert type and severity
//		switch(Severity){
//		
//		case EXTREME:
//			severity = "Extreme";
//		case SEVERE:
//			severity = "Severe";
//		case MODERATE:
//			severity = "Moderate";
//		case MINOR:
//			severity = "Minor";
//		case UNKNOWN:
//			severity = "Unkown";
//			default: 
//				break;
//		}
//		
//		switch(alert_Some){
//		case WIND:
//			alertType = "Wind";
//		case HYDROLOGIC:
//			alertType = "Hydrolic";
//		case SPECIAL_WEATHER_STATEMENT:
//			alertType = "Special Weather Statement";
//		case WINTER:
//			alertType = "Winter";
//		case SURF:
//			alertType = "Surf";
//		case FLOOD:
//			alertType = "Flood";
//			default:
//				break;
//		}
//		
//		if(severity != null)
//		{
//			for(SomeAlert a: listOfAlerts)
//			{
//				if(a.getSeverity() != severity)
//				{
//					if(!listOfAlerts.remove(a))
//						System.out.print("failed to remove Alert");
//				}
//			}
//		}
//		// search for alert keyword in event
//		if(alertType != null)
//		{
//			for(SomeAlert b: listOfAlerts)
//			{
//				if(b.getEvent().indexOf(alertType) != -1)
//				{
//					if(!listOfAlerts.remove(b))
//						System.out.print("faild to remove Alert");
//				}
//			}
//		}
//		
//		
		
		
		
		
		
		hardcodedShit();

		  // walk through vector of Alerts adding polygons & balloons to layer
		   for(SomeAlert a: listOfAlerts)
		   { 
			   if(a.getSomePoly() != null)
			   {
				   layer0.addRenderable(a.getSomePoly());
			   }
			   if(a.getSomeBalloon() != null)
			   {  
				   layer0.addRenderable(a.getSomeBalloon());
			       layer0.addRenderable(a.getSomePlacemark());
			      }
		    
		    // Add polygon to layer
		    }
	
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


		public Vector<SomeAlert> getListOfAlerts() {
			return listOfAlerts;
		}


		public void setListOfAlerts(Vector<SomeAlert> listOfAlerts) {
			this.listOfAlerts = listOfAlerts;
		}
     
        
	

		
		
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
					
			listOfAlerts.add(oneAlert);
			
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
			listOfAlerts.add(twoAlert);
			
			SomeAlert threeAlert = new SomeAlert("Something about your mom, I think" +
					"she found the buffet again, you better get down there!", 
					"https://google.com", "Special Weather Statement", "Future", "Uknown", "2017-03-21T19:00:00-07:00",
					"2017-03-21T19:00:00-07:00", positionArrayFromDegrees(40.1971,-121.3501,41.8639,
							-122.9371,40.1971,-123.3501,38.7829,-120.3423));
			listOfAlerts.add(threeAlert);
			
		}

}
