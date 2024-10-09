package org.example;

public class Main {
    public static void main(String[] args) {
        // Create the TopologyBuilder
        TopologyBuilder builder = new TopologyBuilder();

        // Add a spout
        Spout spout = new RandomNumberSpout();
        builder.addSpout("randomSpout", spout);

        // Add a bolt
        Bolt transformBolt = new TransformBolt();
        builder.addBolt("transformBolt", transformBolt);

        // Define the stream from the spout to the bolt
        builder.setStream("randomSpout", "transformBolt");

        // Submit the topology for execution
        builder.submitTopology("TestTopology");
    }
}
