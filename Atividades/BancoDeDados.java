package Atividades;

public class BancoDeDados {
    private int leitores = 0;
    private boolean escrevendo = false;

    public synchronized void IniciarLeitura() throws InterruptedException {
        while(escrevendo)
            wait();

        leitores++;
    }

    public synchronized void terminarLeitura() {
        leitores--;
        if(leitores == 0)
            notifyAll();
    }

    public synchronized void iniciarEscrita() throws InterruptedException {
        while(escrevendo || leitores > 0)
            wait();
        escrevendo = true;
    }

    public synchronized void terminarEscrita() {
        escrevendo = false;
        notifyAll();
    }
}
