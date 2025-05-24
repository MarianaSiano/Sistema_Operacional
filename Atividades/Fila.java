package Atividades;

import java.util.LinkedList;
import java.util.Queue;

//Atividade 5.4
public class Fila {
    private final Queue<Integer> fila = new LinkedList<>();

    public synchronized void adicionar(int item) {
        fila.add(item);
        notifyAll(); //Evita starvation para múltiplos consumidores
    }

    public synchronized int remover() throws InterruptedException {
        while(fila.isEmpty()) {
            wait();
        }
        return fila.poll();
    }

    //Método main para teste com produtor e consumidor
    public static void main(String[] args) {
        Fila fila = new Fila();

        //Thread produtora
        Thread produtor = new Thread(() -> {
            for(int i = 1; i <= 5; i++) {
                fila.adicionar(i);
                System.out.println("Adicionado: " + i);
                try {
                    Thread.sleep(1000); //Simula tempo de produção
                } catch(InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });

        //Thread consumidora
        Thread consumidor = new Thread(() -> {
            for(int i = 1; i <= 5; i++) {
                try {
                    int valor = fila.remover();
                    System.out.println("Removido: " + valor);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });

        produtor.start();
        consumidor.start();

        try {
            produtor.join();
            consumidor.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Fim da execução.");
    }
}
