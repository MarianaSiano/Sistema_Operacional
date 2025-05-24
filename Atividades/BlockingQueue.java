package Atividades;

//Atividade 4 - Monitores
import java.util.LinkedList;
import java.util.Queue;

public class BlockingQueue<T> {
    private final Queue<T> queue = new LinkedList<>();
    private final int maxSize;

    public BlockingQueue(int size) {
        this.maxSize = size;
    }

    public synchronized void put(T item) throws InterruptedException {
        while(queue.size() == maxSize) {
            wait();
        }

        queue.add(item);
        notifyAll(); //Acorda consumidores
    }

    public synchronized T take() throws InterruptedException {
        while(queue.isEmpty()) {
            wait();
        }

        T item = queue.poll();
        notifyAll(); //Acorda produtores
        return item;
    }

    public static void main(String[] args) {
        BlockingQueue<Integer> fila = new BlockingQueue<>(3);

        //Produtor
        Thread produtor = new Thread(() -> {
            try {
                for(int i = 1; i <= 5; i++) {
                    fila.put(i);
                    System.out.println("Produtor colocou: " + i);
                    Thread.sleep(1000);
                }
            } catch(InterruptedException e) {
                e.printStackTrace();
            }
        });

        //Consumidor
        Thread consumidor = new Thread(() -> {
            try {
                for(int i = 1; i <= 5; i++) {
                    int valor = fila.take();
                    System.out.println("Consumidor pegou: " + valor);
                    Thread.sleep(1500);
                }
            } catch(InterruptedException e) {
                e.printStackTrace();
            }
        });

        produtor.start();
        consumidor.start();

        try {
            produtor.join();
            consumidor.join();
        } catch(InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Fim da execução.");
    }
}