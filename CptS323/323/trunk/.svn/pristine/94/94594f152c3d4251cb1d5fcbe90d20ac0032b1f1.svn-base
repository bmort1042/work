/*
 * Team A Application!
 */

package teama;


import gov.nasa.worldwind.Configuration;
import gov.nasa.worldwind.avlist.AVKey;
import gov.nasa.worldwind.layers.RenderableLayer;
import gov.nasa.worldwind.util.*;
import gov.nasa.worldwindx.examples.util.*;
import gov.nasa.worldwind.*;
import java.awt.*;
import gov.nasa.worldwind.awt.WorldWindowGLCanvas;
import gov.nasa.worldwind.event.*;
import gov.nasa.worldwind.exception.WWAbsentRequirementException;
import gov.nasa.worldwind.layers.*;
import gov.nasa.worldwind.layers.placename.PlaceNameLayer;
import javax.swing.*;
import gov.nasa.worldwindx.examples.ClickAndGoSelectListener;
import gov.nasa.worldwindx.examples.FlatWorldPanel;
import gov.nasa.worldwindx.examples.LayerPanel;
import javax.swing.border.CompoundBorder;
import javax.swing.border.TitledBorder;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;



public class TeamAGUI
{
	
	public static class AppPanel extends JPanel
    {
        protected WorldWindow wwd;
        protected StatusBar statusBar;
        protected ToolTipController toolTipController;
        protected HighlightController highlightController;
       
        public AppPanel(Dimension canvasSize, boolean includeStatusBar)
        {
            super(new BorderLayout());

            this.wwd = this.createWorldWindow();
            ((Component) this.wwd).setPreferredSize(canvasSize);

            // Create the default model as described in the current worldwind properties.
            Model m = (Model) WorldWind.createConfigurationComponent(AVKey.MODEL_CLASS_NAME);
            this.wwd.setModel(m);

            // Setup a select listener for the worldmap click-and-go feature
            this.wwd.addSelectListener(new ClickAndGoSelectListener(this.getWwd(), WorldMapLayer.class));

            this.add((Component) this.wwd, BorderLayout.CENTER);
            if (includeStatusBar)
            {
                this.statusBar = new StatusBar();
                this.add(statusBar, BorderLayout.PAGE_END);
                this.statusBar.setEventSource(wwd);
            }

            // Add controllers to manage highlighting and tool tips.
            this.toolTipController = new ToolTipController(this.getWwd(), AVKey.DISPLAY_NAME, null);
            this.highlightController = new HighlightController(this.getWwd(), SelectEvent.ROLLOVER);
            

        }

        protected WorldWindow createWorldWindow()
        {
            return new WorldWindowGLCanvas();
        }

        public WorldWindow getWwd()
        {
            return wwd;
        }

        public StatusBar getStatusBar()
        {
            return statusBar;
        }
    }

    protected static class AppFrame extends JFrame
    {
        private Dimension canvasSize = new Dimension(1000, 800);

 ///***************** adding map object, controlers and a layer
        protected Map myMap;
        protected Configuration_Panel configs;
        protected BalloonController balloonController;
        protected HotSpotController hotSpotController;
        protected RenderableLayer layer0;
//////////******************************************************               	

        protected AppPanel wwjPanel;
        protected JPanel controlPanel;
        protected LayerPanel layerPanel;
        protected StatisticsPanel statsPanel;


        public AppFrame()
        {
            this.initialize(true, true, false);
        }

        public AppFrame(Dimension size)
        {
            this.canvasSize = size;
            this.initialize(true, true, false);
        }

        public AppFrame(boolean includeStatusBar, boolean includeLayerPanel, boolean includeStatsPanel)
        {
            this.initialize(includeStatusBar, includeLayerPanel, includeStatsPanel);
        }

        protected void initialize(boolean includeStatusBar, boolean includeLayerPanel, boolean includeStatsPanel)
        {
            // Create the WorldWindow.
            this.wwjPanel = this.createAppPanel(this.canvasSize, includeStatusBar);
            this.wwjPanel.setPreferredSize(canvasSize);
            this.balloonController = new BalloonController(this.getWwd());
            this.hotSpotController = new HotSpotController(this.getWwd());
 ///*************************            
            //________________ Adding Layer for polygons and balloons __________________
            this.layer0 = new RenderableLayer();
            this.layer0.setName("Polygons");
            // ____________________Insert layer before compass ____________________________
            insertBeforeCompass(getWwd(), layer0);
           
            // create Map object and pass polygon layer
            myMap = new Map(layer0);
            configs = new Configuration_Panel();
              
//************************* 
            
            // Put the pieces together.
            this.getContentPane().add(wwjPanel, BorderLayout.EAST);
            if (includeLayerPanel)
            {
                this.controlPanel = new JPanel();
                controlPanel.setLayout(new BoxLayout(controlPanel, BoxLayout.Y_AXIS));
                this.layerPanel = new LayerPanel(this.getWwd());
                this.controlPanel.add(new FlatWorldPanel(this.getWwd())); //This is the top pan
                controlPanel.add(this.getLabel());

                
                this.getContentPane().add(this.controlPanel, BorderLayout.WEST);//This is the whole panel on the left
            }

            if (includeStatsPanel || System.getProperty("gov.nasa.worldwind.showStatistics") != null)
            {
                this.statsPanel = new StatisticsPanel(this.wwjPanel.getWwd(), new Dimension(250, canvasSize.height));
                this.getContentPane().add(this.statsPanel, BorderLayout.EAST);
            }

            // Create and install the view controls layer and register a controller for it with the World Window.
            ViewControlsLayer viewControlsLayer = new ViewControlsLayer();
            insertBeforeCompass(getWwd(), viewControlsLayer);
            this.getWwd().addSelectListener(new ViewControlsSelectListener(this.getWwd(), viewControlsLayer));

            // Register a rendering exception listener that's notified when exceptions occur during rendering.
            this.wwjPanel.getWwd().addRenderingExceptionListener(new RenderingExceptionListener()
            {
                @Override
				public void exceptionThrown(Throwable t)
                {
                    if (t instanceof WWAbsentRequirementException)
                    {
                        String message = "Computer does not meet minimum graphics requirements.\n";
                        message += "Please install up-to-date graphics driver and try again.\n";
                        message += "Reason: " + t.getMessage() + "\n";
                        message += "This program will end when you press OK.";

                        JOptionPane.showMessageDialog(AppFrame.this, message, "Unable to Start Program",
                            JOptionPane.ERROR_MESSAGE);
                        System.exit(-1);
                    }
                }
            });
            
            
            // Search the layer list for layers that are also select listeners and register them with the World
            // Window. This enables interactive layers to be included without specific knowledge of them here.
            for (Layer layer : this.wwjPanel.getWwd().getModel().getLayers())
            {
                if (layer instanceof SelectListener)
                {
                    this.getWwd().addSelectListener((SelectListener) layer);
                }
            }

            this.pack();

            // Center the application on the screen.
            WWUtil.alignComponent(null, this, AVKey.CENTER);
            this.setResizable(true);
        }

        protected AppPanel createAppPanel(Dimension canvasSize, boolean includeStatusBar)
        {
            return new AppPanel(canvasSize, includeStatusBar);
        }

        public Dimension getCanvasSize()
        {
            return canvasSize;
        }

        public AppPanel getWwjPanel()
        {
            return wwjPanel;
        }

        public WorldWindow getWwd()
        {
            return this.wwjPanel.getWwd();
        }
        
        public JPanel getLabel(){
        	
    		// The panel for the buttons.
            JPanel controlPanel = new JPanel();
            controlPanel.setLayout(new BoxLayout(controlPanel, BoxLayout.Y_AXIS));
            controlPanel.setAlignmentY(Component.TOP_ALIGNMENT);


            	// Add/Remove Feed (button) - Calls the tool bar element to open a JFrame of Add/Remove Feed.
            JPanel CS_Panel = new JPanel(new GridLayout(0, 1, 0, 0));
            CS_Panel.setBorder(BorderFactory.createEmptyBorder(4, 4, 4, 4));
            
            JButton CS_AddRemove = new JButton("Add/Remove Feeds");
            
            	// The function to be called when the button is pressed.
            CS_AddRemove.addActionListener(new ActionListener(){
                public void actionPerformed(ActionEvent event){
                    RSS_Panel rss = new RSS_Panel();
                    rss.addObserver(myMap);
                    rss.addObserver(configs);
                    rss.create_frame();
                }
            });
            
            	// Add to the container.
            CS_Panel.add(CS_AddRemove);        
            controlPanel.add(CS_Panel);
            
            
            	// Configuration Settings (button) - Calls the tool bar element to open a JFrame of Configuration Settings.    
            JPanel Add_and_Remove_Panel = new JPanel(new GridLayout(0, 1, 0, 0));
            Add_and_Remove_Panel.setBorder(BorderFactory.createEmptyBorder(4, 4, 4, 4));
            
            JButton Add_and_Remove = new JButton("Configuration Settings");
            
            	// The function to be called when the button is pressed.
            Add_and_Remove.addActionListener(new ActionListener(){
                @Override
				public void actionPerformed(ActionEvent event){
                	///Have to add observer to list that observable will notify
 //////////******************************************************               	

 //////////******************************************************               	

                	configs.create_frame();                    
                }

            });
            
            	// Add to the container.
            Add_and_Remove_Panel.add(Add_and_Remove);        
            controlPanel.add(Add_and_Remove_Panel);
            
            
         		// Search Button (button) - Calls the tool bar element to open a JFrame of Search.   
            JPanel Search_Panel = new JPanel(new GridLayout(0, 1, 0, 0));
            Search_Panel.setBorder(BorderFactory.createEmptyBorder(4, 4, 4, 4));
            
            JButton Search = new JButton("Search");
            
                // The function to be called when the button is pressed.
            Search.addActionListener(new ActionListener(){
                public void actionPerformed(ActionEvent event){
                    Search_Panel search = new Search_Panel();
                    search.addObserver(myMap);
                    search.create_frame();
                }
            });
            
            	// Add to the container.
            Search_Panel.add(Search);        
            controlPanel.add(Search_Panel);
            

            	// Create a outline for the buttons and title it.
            controlPanel.setBorder( new CompoundBorder(BorderFactory.createEmptyBorder(9, 9, 9, 9), new TitledBorder("Settings")));            
            controlPanel.setToolTipText("For thugs only.");
            
            return controlPanel;
        }
        


        public StatusBar getStatusBar()
        {
            return this.wwjPanel.getStatusBar();
        }

        /**
         * @deprecated Use getControlPanel instead.
         * @return This application's layer panel.
         */
        @Deprecated
		public LayerPanel getLayerPanel()
        {
            return this.layerPanel;
        }

        public JPanel getControlPanel()
        {
            return this.controlPanel;
        }

        public StatisticsPanel getStatsPanel()
        {
            return statsPanel;
        }

        public void setToolTipController(ToolTipController controller)
        {
            if (this.wwjPanel.toolTipController != null)
                this.wwjPanel.toolTipController.dispose();

            this.wwjPanel.toolTipController = controller;
        }

        public void setHighlightController(HighlightController controller)
        {
            if (this.wwjPanel.highlightController != null)
                this.wwjPanel.highlightController.dispose();

            this.wwjPanel.highlightController = controller;
        }
    }

    //this inserts the nav tool on the bottom left
    /**
     * @wbp.parser.entryPoint
     */
    public static void insertBeforeCompass(WorldWindow wwd, Layer layer)
    {
        // Insert the layer into the layer list just before the compass.
        int compassPosition = 0;
        LayerList layers = wwd.getModel().getLayers();
        for (Layer l : layers)
        {
            if (l instanceof CompassLayer)
                compassPosition = layers.indexOf(l);
        }
        layers.add(compassPosition, layer);
    }
    
    public static void insertBeforePlacenames(WorldWindow wwd, Layer layer)
    {
        // Insert the layer into the layer list just before the placenames.
        int compassPosition = 0;
        LayerList layers = wwd.getModel().getLayers();
        for (Layer l : layers)
        {
            if (l instanceof PlaceNameLayer)
                compassPosition = layers.indexOf(l);
        }
        layers.add(compassPosition, layer);
    }

    /**
     * @wbp.parser.entryPoint
     */
    public static void insertAfterPlacenames(WorldWindow wwd, Layer layer)
    {
        // Insert the layer into the layer list just after the placenames.
        int compassPosition = 0;
        LayerList layers = wwd.getModel().getLayers();
        for (Layer l : layers)
        {
            if (l instanceof PlaceNameLayer)
                compassPosition = layers.indexOf(l);
        }
        layers.add(compassPosition + 1, layer);
    }

    public static void insertBeforeLayerName(WorldWindow wwd, Layer layer, String targetName)
    {
        // Insert the layer into the layer list just before the target layer.
        int targetPosition = 0;
        LayerList layers = wwd.getModel().getLayers();
        for (Layer l : layers)
        {
            if (l.getName().indexOf(targetName) != -1)
            {
                targetPosition = layers.indexOf(l);
                break;
            }
        }
        layers.add(targetPosition, layer);
    }

    static
    {
        System.setProperty("java.net.useSystemProxies", "true");
        if (Configuration.isMacOS())
        {
            System.setProperty("apple.laf.useScreenMenuBar", "true");
            System.setProperty("com.apple.mrj.application.apple.menu.about.name", "World Wind Application");
            System.setProperty("com.apple.mrj.application.growbox.intrudes", "false");
            System.setProperty("apple.awt.brushMetalLook", "true");
        }
        else if (Configuration.isWindowsOS())
        {
            System.setProperty("sun.awt.noerasebackground", "true"); // prevents flashing during window resizing
        }
    }

    /**
     * @wbp.parser.entryPoint
     */
    public static AppFrame start(String appName, Class appFrameClass)
    {
        if (Configuration.isMacOS() && appName != null)
        {
            System.setProperty("com.apple.mrj.application.apple.menu.about.name", appName);
        }

        try
        {
            final AppFrame frame = (AppFrame) appFrameClass.newInstance();
            frame.setTitle(appName);
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            java.awt.EventQueue.invokeLater(new Runnable()
            {
                @Override
				public void run()
                {
                    frame.setVisible(true);
                }
            });

            return frame;
        }
        catch (Exception e)
        {
            e.printStackTrace();
            return null;
        }
    }

    /**
     * @wbp.parser.entryPoint
     */
    public static void main(String[] args)
    {
        // Call the static start method like this from the main method of your derived class.
        // Substitute your application's name for the first argument.
    	//Search_Panel search = new Search_Panel();
        TeamAGUI.start("World Wind Application", AppFrame.class);
    }
}
