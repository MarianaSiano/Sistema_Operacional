# Sistemas Operacionais

* Repositório para as atividades da disciplina DCC062 - Sistemas Operacionais <br>

## Observação

* As atividades da Linguagem C funcionam APENAS no Sistema Operacional Linux <br>

* Linux utilizado para testes foi o Ubuntu 20.04 <br>

* As atividades em Linguagem Java foi testada no Windows 11. 

## Compilando os Programas em Linguagem C

* Para rodar os programas que são da linguagem C, basta ir para a pasta de Atividades com o seguinte comando: <br>
`cd Atividades`  <br>

* Em seguida, faça o comando a seguir, dependendo da atividade que queira compilar: <br>
`gcc nome_do_programa -o nome_arquivo_executavel` <br>

* Onde: `nome_do_programa` é o nome do arquivo que queira compilar e `nome_arquivo_executavel` é o nome do executavel que sera utilizado logo em seguida <br>

* Após isso, para rodar o arquivo compilado, basta digitar o seguinte comando: <br>
`./nome_arquivo_executavel`

* Com isso, o programa irá rodar. <br>

* Mas caso vai direto executar sem antes compilar o programa, o mesmo não irá funcionar.

## Compilando os Programas em Linguagem Java no Windows

* Para rodar as atividades da Linguagem Java, fique no diretório raiz (não entrando no diretório `Atividades`) <br>

* No seu computador, precisa está instalado o JDE e o JDK e esse último, o `bin` tem que está obrigatoriamente no `PATH` em `Ambientes de Trabalho` <br>

* Após as instalações, faça o seguinte comando: <br>
`javac Atividades/nome_do_arquivo.java` <br>

* Com isso, criará um executavel e execute: <br>
`java Atividades/nome_do_arquivo`

## Compilando os Programas em Linguagem Java no Linux Ubuntu
* Primeiro vamos instalar o JDK com o seguinte comando: <br>
`sudo apt install default-jdk` <br>

* Para rodar as atividades da Linguagem Java, fique no diretório raiz (não entrando no diretório `Atividades`) <br>

* Após as instalações, faça o seguinte comando: <br>
`javac Atividades/nome_do_arquivo.java` <br>

* Com isso, criará um executavel e execute: <br>
`java Atividades/nome_do_arquivo`