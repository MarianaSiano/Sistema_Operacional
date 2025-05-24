package Atividades;

//4 - Monitores
import java.util.*;

public class BlockingQueue<T> {
    private final Queue<T> queue = new LinkedList<>();
    private final int maxSize;

    public BlockingQueue(int size) {
        this.maxSize = size;
    }

    public synchronized void put(T item) throws InterruptedException {
        while(queue.size() == maxSize)
            wait();

        queue.add(item);
        notify();
    }

    public synchronized T take() throws InterruptedException {
        while(queue.isEmpty())
            wait();

        T item = queue.poll();
        notify();
        return item;
    }
}