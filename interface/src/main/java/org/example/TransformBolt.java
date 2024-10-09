package org.example;

public class TransformBolt implements Bolt {
    @Override
    public void prepare() {
        System.out.println("TransformBolt is prepared.");
    }

    @Override
    public void execute(Object tuple) {
        if (tuple instanceof Integer) {
            Integer number = (Integer) tuple;
            Integer transformed = number * 2;
            System.out.println("TransformBolt transformed " + number + " to " + transformed);
        } else {
            System.out.println("Invalid tuple received.");
        }
    }

    @Override
    public void cleanup() {
        System.out.println("TransformBolt cleanup.");
    }
}
