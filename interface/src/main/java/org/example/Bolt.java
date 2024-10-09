package org.example;

public interface Bolt {
    // Method to process data, similar to Storm's execute()
    void execute(Object tuple);

    // Method to prepare the Bolt, if needed (like in Storm)
    void prepare();

    // Method to clean up the Bolt when the simulation finishes
    void cleanup();
}
