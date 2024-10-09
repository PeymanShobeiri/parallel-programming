package org.example;

import java.util.HashMap;
import java.util.Map;

public class TopologyBuilder {

    static {
        System.loadLibrary("TopologyBuilder"); // Load the native library
    }
    private long engine;
    // Native method that will interact with SimGrid via JNI
    private native void submitTopologyNative(String topologyName, long engine);
    private native void createSpout(String spoutName);
    private native void createBolt(String boltName);
    public native long init();  // Native init method

    // Holds the topology components (spouts and bolts)
    private Map<String, Spout> spouts = new HashMap<>();
    private Map<String, Bolt> bolts = new HashMap<>();
    private Map<String, String> streamMapping = new HashMap<>();

    // Constructor to initialize the TopologyBuilder and call init method
    public TopologyBuilder() {
        engine = init();
        if (engine == 0) {
            throw new RuntimeException("Failed to initialize engine");
        }
    }

    // Method to add a spout to the topology
    public void addSpout(String spoutId, Spout spout) {
        createSpout(spoutId);
        spouts.put(spoutId, spout);
    }

    // Method to add a bolt to the topology
    public void addBolt(String boltId, Bolt bolt) {
        createBolt(boltId);
        bolts.put(boltId, bolt);
    }

    // Define the stream that connects a spout to a bolt
    public void setStream(String spoutId, String boltId) {
        if (spouts.containsKey(spoutId) && bolts.containsKey(boltId)) {
            streamMapping.put(spoutId, boltId);
        } else {
            throw new IllegalArgumentException("Invalid spout or bolt ID");
        }
    }

    // Submit the topology for execution
    public void submitTopology(String topologyName) {
        // Call native method to run the simulation with JNI
        submitTopologyNative(topologyName,engine);
    }
}
