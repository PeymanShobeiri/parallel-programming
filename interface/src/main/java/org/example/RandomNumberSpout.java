package org.example;

import java.util.Random;

public class RandomNumberSpout implements Spout {
    private Random random = new Random();

    @Override
    public void open() {
        System.out.println("RandomNumberSpout is open.");
    }

    @Override
    public void nextTuple() {
        int number = random.nextInt(100);  // Generate a random number
        System.out.println("Spout emitted: " + number);
        // In actual implementation, you'd send this number to the topology
    }

    @Override
    public void close() {
        System.out.println("RandomNumberSpout is closed.");
    }
}
