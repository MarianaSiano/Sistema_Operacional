package Atividades;
//Atividade 5.7

public class BancoDeDados {
    private int leitores = 0;
    private boolean escrevendo = false;

    public synchronized void iniciarLeitura() throws InterruptedException {
        while(escrevendo) {
            wait();
        }
        leitores++;
    }

    public synchronized void terminarLeitura() {
        leitores--;
        if(leitores == 0) {
            notifyAll();
        }
    }

    public synchronized void iniciarEscrita() throws InterruptedException {
        while(escrevendo || leitores > 0) {
            wait();
        }
        escrevendo = true;
    }

    public synchronized void terminarEscrita() {
        escrevendo = false;
        notifyAll();
    }

    public static void main(String[] args) {
        BancoDeDados banco = new BancoDeDados();

        //Criando leitores
        for(int i = 1; i <= 3; i++) {
            int id = i;

            new Thread(() -> {
                try {
                    banco.iniciarLeitura();
                    System.out.println("Leitor " + id + " lendo...");
                    Thread.sleep(1000); //Simula leitura
                    System.out.println("Leitor " + id + " terminou de ler.");
                    banco.terminarLeitura();
                } catch(InterruptedException e) {
                    e.printStackTrace();
                }
            }).start();
        }

        //Escritor
        new Thread(() -> {
            try {
                Thread.sleep(500); //Espera leitores começarem
                banco.iniciarEscrita();
                System.out.println("Escritor escrevendo...");
                Thread.sleep(2000); //Simula escrita
                System.out.println("Escritor terminou de escrever.");
                banco.terminarEscrita();
            } catch 
            (InterruptedException e) {
                e.printStackTrace();
            }
        }).start();
    }
}