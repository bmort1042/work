package views;

import gov.nasa.worldwind.WorldWind;
import gov.nasa.worldwind.render.*;
import gov.nasa.worldwind.avlist.AVKey;
import gov.nasa.worldwind.geom.Position;
import gov.nasa.worldwind.layers.RenderableLayer;
import gov.nasa.worldwind.render.AbstractBrowserBalloon;
import gov.nasa.worldwind.render.Balloon;
import gov.nasa.worldwind.render.BalloonAttributes;
import gov.nasa.worldwind.render.BasicBalloonAttributes;
import gov.nasa.worldwind.render.BasicShapeAttributes;
import gov.nasa.worldwind.render.GlobeBrowserBalloon;
import gov.nasa.worldwind.render.Material;
import gov.nasa.worldwind.render.PointPlacemark;
import gov.nasa.worldwind.render.Polygon;
import gov.nasa.worldwind.render.ShapeAttributes;
import gov.nasa.worldwind.render.Size;
import gov.nasa.worldwind.util.Logging;
import gov.nasa.worldwind.util.WWIO;
import java.util.Enumeration;
import java.util.Locale;

import com.sun.org.apache.xerces.internal.impl.xpath.regex.ParseException;

import views._severity;


import java.io.InputStream;
import java.sql.Date;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
public class SomeAlert {
	
	
	// will create a vector of alert objects conaiting polygons and balloons
	protected Polygon somePoly;
	protected AbstractBrowserBalloon someBalloon = null;
    protected PointPlacemark somePlacemark = null; 

	
	// all data needed from feed. 
	protected String summary; // alert summary 'Text'
	protected String link; // html link
	protected String event; // Alert Type
	protected String certainty; // Possibility of alert happening
	protected String severity; 
	//protected String timeExpires; // exipire time? not sure on format
	//protected String effectiveTime; // effective time
    protected ArrayList<Position> positions; // Arraylist of postions
	protected java.util.Date timeExpires;
	protected java.util.Date effectiveTime;
	protected SimpleDateFormat defaultDateFormat;
	
	public SomeAlert(String summary,String link,String event,
			String certainty, String severity, String timeExpires, String effectiveTime,
			ArrayList<Position> positions) {
		
		super();
        defaultDateFormat = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ssZ", Locale.getDefault());
       
		this.summary = summary;
		this.link = link;
		this.event = event;
		this.certainty = certainty;
		this.severity = severity;
		this.positions = positions;
		this.somePoly = createPolygon(positions);
		makeBrowserBalloon(positions);
		try {
	            this.timeExpires =  defaultDateFormat.parse(parseTimeString(timeExpires));
	        }
		catch (java.text.ParseException e) {
	            this.timeExpires = null;
	            e.printStackTrace();
		}
		try {
                this.effectiveTime = defaultDateFormat.parse(parseTimeString(effectiveTime));
        } catch (java.text.ParseException e) {
                this.effectiveTime = null;
                e.printStackTrace();
        }
	}
	
	
	protected String parseTimeString(String time)
	{
		for (int i = 0, j = 0; i < time.length(); i++){
			if(time.charAt(i) == ':')
			{
		    	 j++; 
		    	 if(j == 3)
		    	 {
		    		 StringBuilder sb = new StringBuilder(time);
		    		 sb.deleteCharAt(i);
		    		 time = sb.toString();
		    		 break;
		    	 }
			}
		}
		
		return time;
	}


	protected void makeBrowserBalloon(ArrayList<Position> positions)
    {
       String balloonText = summary +"\n<a href='" + link + "'>" + link + "</a>";
       
       
        // Create a Browser Balloon attached to the globe
        // We use the balloon page's URL as its resource resolver to handle relative paths in the page content.
        AbstractBrowserBalloon balloon = new GlobeBrowserBalloon(balloonText, positions.get(0));
        // Size the balloon to provide enough space for its content.
        BalloonAttributes attrs = new BasicBalloonAttributes();
        attrs.setSize(new Size(Size.NATIVE_DIMENSION, 0d, null, Size.NATIVE_DIMENSION, 0d, null));
        balloon.setAttributes(attrs);
        balloon.setPickEnabled(true);
        balloon.setAlwaysOnTop(true);
        balloon.setVisible(false);  //////************************TEMP FIX for Balloon Close button
        this.someBalloon = balloon;
        
        // Create a placemark on the globe that the user can click to open the balloon.
        //somePlacemark = new PointPlacemark(positions.get(0));
        //somePlacemark.setLabelText(this.event);
       
        this.somePlacemark = new PointPlacemark(positions.get(0));
        this.somePlacemark.setLabelText(this.event);
        this.somePlacemark.setValue(AVKey.BALLOON, someBalloon);
        this.somePlacemark.setValue(AVKey.TARGET, "_blank");

    }

	
	
    // Function called by the constructor to create polygon
    public Polygon createPolygon( ArrayList<Position> pathLocations)
    {
    	if(pathLocations.size() < 4)
    	{
    		return null;
    	}

        ShapeAttributes normalAttributes = new BasicShapeAttributes();
        normalAttributes.setInteriorMaterial(Material.YELLOW);
        normalAttributes.setOutlineOpacity(0.5);
        normalAttributes.setInteriorOpacity(0.8);
        normalAttributes.setOutlineMaterial(Material.GREEN);
        normalAttributes.setOutlineWidth(2);
        normalAttributes.setDrawOutline(true);
        normalAttributes.setDrawInterior(true);
        normalAttributes.setEnableLighting(true);

        ShapeAttributes highlightAttributes = new BasicShapeAttributes(normalAttributes);
        highlightAttributes.setOutlineMaterial(Material.WHITE);
        highlightAttributes.setOutlineOpacity(1);

    
        Polygon pgon= new Polygon(pathLocations);
        pgon.setValue(AVKey.DISPLAY_NAME, event);
        normalAttributes = new BasicShapeAttributes(normalAttributes);
        normalAttributes.setDrawInterior(true);
        normalAttributes.setInteriorMaterial(Material.RED);
        pgon.setAttributes(normalAttributes);
        pgon.setHighlightAttributes(highlightAttributes);
        pgon.setAltitudeMode(WorldWind.RELATIVE_TO_GROUND);
        
        return pgon;
    }

    
    
	public Polygon getSomePoly() {
		return somePoly;
	}
	public void setSomePoly(Polygon somePoly) {
		this.somePoly = somePoly;
	}
	public Balloon getSomeBalloon() {
		return someBalloon;
	}
	public void setSomeBalloon(AbstractBrowserBalloon someBalloon) {
		this.someBalloon = someBalloon;
	}
	public String getEvent() {
		return event;
	}
	public void setEvent(String event) {
		this.event = event;
	}
	public String getCertainty() {
		return certainty;
	}
	public void setUrgency(String certainty) {
		this.certainty = certainty;
	}
	public String getSeverity() {
		return severity;
	}
	public void setSeverity(String severity) {
		this.severity = severity;
	}
	public java.util.Date getTimeExpires() {
		return timeExpires;
	}
	public void setTimeExpires(java.util.Date timeExpires) {
		this.timeExpires = timeExpires;
	}
	public ArrayList<Position> getPositions() {
		return positions;
	}
	public void setPositions(ArrayList<Position> positions) {
		this.positions = positions;
	}


	public String getSummary() {
		return summary;
	}


	public void setSummary(String summary) {
		this.summary = summary;
	}


	public String getLink() {
		return link;
	}


	public void setLink(String link) {
		this.link = link;
	} 
	
	public  PointPlacemark getSomePlacemark(){
		return somePlacemark;
	}
	
	public void setSomePlacemark(PointPlacemark somePlacemark){
		this.somePlacemark = somePlacemark;
	}

	public java.util.Date getEffectiveTime() {
		return effectiveTime;
	}

	public void setEffectiveTime(java.util.Date effectiveTime) {
		this.effectiveTime = effectiveTime;
	}

	public void setCertainty(String certainty) {
		this.certainty = certainty;
	}
	

	
	
	
	

}
