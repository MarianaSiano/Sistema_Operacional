package Atividades;

import java.util.LinkedList;
import java.util.Queue;

//Atividade 5.4
public class Fila {
    private Queue<Integer> fila = new LinkedList<>();

    public synchronized void adicionar(int item) {
        fila.add(item);
        notify(); //Evita starvation
    }

    public synchronized int remover() throws InterruptedException {
        while(fila.isEmpty())
            wait();
        return fila.poll();
    }
}
