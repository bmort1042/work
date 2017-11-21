package wickham_branch;

import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Vector;

import javax.net.ssl.HttpsURLConnection;

import com.sun.syndication.feed.synd.SyndContentImpl;
import com.sun.syndication.feed.synd.SyndEntry;
import com.sun.syndication.feed.synd.SyndFeed;
import com.sun.syndication.io.SyndFeedInput;
import com.sun.syndication.feed.synd.SyndCategoryImpl;
import com.sun.syndication.feed.synd.SyndLinkImpl;
import com.sun.syndication.io.XmlReader;

import gov.nasa.worldwind.geom.Position;

public class RSS_Parser{
	
	@SuppressWarnings("rawtypes")
	
	protected Map map;
	
	public RSS_Parser(Map map)
	{
		this.map = map;
	}
	
	public void Refresh(String State)
	/*
	 * Currently pulls all active alerts from a state and turns them into
	 * SomeAlerts,and adds them to the vector. Eventually needs to add to
	 * the ArrayList for each state, but this will do for now.
	 * 
	 * TODO: For Logan: Above notes and FIPS translations.
	 */
	{
		URL url;
		String url_addr = getURLAddr(State);
		try {
			
			url = new URL(url_addr);
			HttpsURLConnection httpcon = (HttpsURLConnection)url.openConnection();
			SyndFeedInput st_input = new SyndFeedInput();
			SyndFeed st_feed = st_input.build(new XmlReader(httpcon));
			List entries = st_feed.getEntries();
			Iterator itEntries = entries.iterator();
			Vector<SomeAlert> listOfAlerts = map.getListOfAlerts();
			while (itEntries.hasNext()) {
				SomeAlert newAlert = MakeAlert((SyndEntry)itEntries.next());
				listOfAlerts.add(newAlert);
			}
			map.setListOfAlerts(listOfAlerts);
		} 
		catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	private static String getURLAddr(String state)
	/*
	 * Stupid but effective switch statement to build the URL for the feed
	 * based on the State.
	 */
	{
		String state_abbrev;
		switch (state) {
		case "Alabama":
			state_abbrev = "al";
			break;
		case "Alaska":
			state_abbrev = "ar";
			break;
		case "Arizona":
			state_abbrev = "az";
			break;
		case "Arkansas":
			state_abbrev = "ar";
			break;
		case "California":
			state_abbrev = "ca";
			break;
		case "Colorado":
			state_abbrev = "co";
			break;
		case "Connecticut":
			state_abbrev = "ct";
			break;
		case "Delaware":
			state_abbrev = "de";
			break;
		case "Florida":
			state_abbrev = "fl";
			break;
		case "Georgia":
			state_abbrev = "ga";
			break;
		case "Hawaii":
			state_abbrev = "hi";
			break;
		case "Idaho":
			state_abbrev = "id";
			break;
		case "Illinois":
			state_abbrev = "il";
			break;
		case "Indiana":
			state_abbrev = "in";
			break;
		case "Iowa":
			state_abbrev = "ia";
			break;
		case "Kansas":
			state_abbrev = "ks";
			break;
		case "Kentucky":
			state_abbrev = "ky";
			break;
		case "Louisiana":
			state_abbrev = "la";
			break;
		case "Maine":
			state_abbrev = "me";
			break;
		case "Maryland":
			state_abbrev = "md";
			break;
		case "Massachusetts":
			state_abbrev = "ma";
			break;
		case "Michigan":
			state_abbrev = "mi";
			break;
		case "Minnesota":
			state_abbrev = "mn";
			break;
		case "Mississippi":
			state_abbrev = "ms";
			break;
		case "Missouri":
			state_abbrev = "mo";
			break;
		case "Montana":
			state_abbrev = "mt";
			break;
		case "Nebraska":
			state_abbrev = "ne";
			break;
		case "Nevada":
			state_abbrev = "nv";
			break;
		case "New Hampshire":
			state_abbrev = "nh";
			break;
		case "New Jersey":
			state_abbrev = "nj";
			break;
		case "New Mexico":
			state_abbrev = "nm";
			break;
		case "New York":
			state_abbrev = "ny";
			break;
		case "North Carolina":
			state_abbrev = "nc";
			break;
		case "North Dakota":
			state_abbrev = "nd";
			break;
		case "Ohio":
			state_abbrev = "oh";
			break;
		case "Oklahoma":
			state_abbrev = "ok";
			break;
		case "Oregon":
			state_abbrev = "or";
			break;
		case "Pennsylvania":
			state_abbrev = "pa";
			break;
		case "Rhode Island":
			state_abbrev = "ri";
			break;
		case "South Carolina":
			state_abbrev = "sc";
			break;
		case "South Dakota":
			state_abbrev = "sd";
			break;
		case "Tennessee":
			state_abbrev = "tn";
			break;
		case "Texas":
			state_abbrev = "tx";
			break;
		case "Utah":
			state_abbrev = "ut";
			break;
		case "Vermont":
			state_abbrev = "vt";
			break;
		case "Virginia":
			state_abbrev = "va";
			break;
		case "Washington":
			state_abbrev = "wa";
			break;
		case "West Virginia":
			state_abbrev = "wv";
			break;
		case "Wisconsin":
			state_abbrev = "wi";
			break;
		case "Wyoming":
			state_abbrev = "wy";
			break;
		default:
			state_abbrev = "us";
		}
		String url_addr_a = String.join("/", "https://alerts.weather.gov/cap", state_abbrev);
		return String.join(".", url_addr_a, "php?x=0");
	}
	
	private SomeAlert MakeAlert(SyndEntry event)
	/*
	 * Pulls data from the alert fields and uses the alert's constructor.
	 * ONLY handles Lat/Long pairs. Needs database for FIPS conversions,
	 * and uses a singular Lat/Long pair otherwise. Use w/ caution. :D 
	 */
	{
		ArrayList alert_specs = (ArrayList)event.getForeignMarkup();
		String summary = (event.getDescription()).getValue();
		String alert_type = (String)alert_specs.get(0);
		String severity = (String)alert_specs.get(7);
		String certainty = (String)alert_specs.get(8);
		String start_time = (String)alert_specs.get(1);
		String expire_time = (String)alert_specs.get(2);
		Double LatLongs_array[] = {361., 361.};
		if(alert_specs.get(10)!= null)
		{
			String locations = (String)alert_specs.get(10);
			String locations_a = locations.replace(' ', ',');
			String LongLats[] = locations_a.split(",");
			ArrayList<Double> LatLongs = new ArrayList<Double>();
			for(String coord: LongLats)
			{
				LatLongs.add(Double.parseDouble(coord));
			}
			LatLongs_array = (Double[])LatLongs.toArray();
		}
		ArrayList<Position> coords = map.positionArrayFromDegrees(LatLongs_array);
		String link = event.getLink();
		return new SomeAlert(summary, link, alert_type,
										   severity, certainty, start_time,
										   expire_time, coords);
	}
}
	