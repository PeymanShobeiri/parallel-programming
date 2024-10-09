package org.example;

public interface Spout {
    // Method to generate tuples (in Storm, this would be emit)
    void nextTuple();

    // Preparation method for the spout (if needed)
    void open();

    // Cleanup method
    void close();
}
