//Definição dos pinos:

int led_verm = 12;
int led_verd = 5;
int led_azul = 7;
int led_amar = 10;

int botao_verm = 13;
int botao_verd = 6;
int botao_azul = 4;
int botao_amar = 11;

int buzzer = 3;

// --- Variávei Globais ---
int seq[50]; //vetor que grava a sequência dos leds (1 - verm, 2 - verd, 3 - azul, 4 - amar)

int i; //variavel contadora: usada para preencher vetor seq[]
int a; //variavel contadora: avança até alcançar o nivel que o jogador estar
int c; //variavel contadora: é incrementada cada vez que um botão é pressionado

int nivel; //variável que grava o nível máximo que o jogador chegou

boolean jogar; //mantem-se nível logico alto enquanto o jogador acerta a sequencia
boolean verificar; //verificar = 1: jogador ainda não chegou no último nível,
//verificar = 0: jogador chegou no último nível ou errou a sequencia.

int nota_verm = 2280, //nota musical para cor verm
    nota_verd = 2850,
    nota_azul = 3420,
    nota_amar = 4275;

/////////----------------------------------------------
void setup() {
  pinMode(led_verm, OUTPUT);
  pinMode(led_verd, OUTPUT);
  pinMode(led_azul, OUTPUT);
  pinMode(led_amar, OUTPUT);

  pinMode(botao_verm, INPUT_PULLUP);
  pinMode(botao_verd, INPUT_PULLUP);
  pinMode(botao_azul, INPUT_PULLUP);
  pinMode(botao_amar, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  randomSeed(analogRead(0)); // inicia a lista de valores aleatórios

  digitalWrite(led_verm, LOW);
  digitalWrite(led_verd, LOW);
  digitalWrite(led_azul, LOW);
  digitalWrite(led_amar, LOW);
  noTone(buzzer);
}

// --- função  Loop  ---
void loop() {

  digitalWrite(led_verd, 1);
  delay(100);
  digitalWrite(led_verd, 0);
  delay(100);

  if (digitalRead(botao_verd) == 0) { // se botão verde for pressionado
    abertura();  // chama a função de inicialização - leds piscam
    jogo(); // jogo genius
    finalizacao(); // executada quando o jogador erra a sequencia - leds piscam
  }
} // fim loop

////////////////////////////////////////////////////////////////////////
// ----------------------------- FUNÇÕES -----------------------------//
////////////////////////////////////////////////////////////////////////

void abertura() //sinaliza o inicio do jogo
{
  digitalWrite(led_verm,  HIGH);
  digitalWrite(led_verd,  HIGH);
  digitalWrite(led_azul,  HIGH);
  digitalWrite(led_amar,  HIGH);
  delay(500);

  for (int j = 0; j < 3; j++)//repete 3 vezes
  {
    digitalWrite(led_verm,  LOW);
    digitalWrite(led_verd,  HIGH);
    digitalWrite(led_azul,  LOW);
    digitalWrite(led_amar,  HIGH);
    tone(buzzer, nota_amar);
    delay(100);
    noTone(buzzer);

    digitalWrite(led_verm,  HIGH);
    digitalWrite(led_verd,  LOW);
    digitalWrite(led_azul,  HIGH);
    digitalWrite(led_amar,  LOW);
    tone(buzzer, nota_azul);
    delay(100);
    noTone(buzzer);

    digitalWrite(led_verm,  LOW);
    digitalWrite(led_verd,  HIGH);
    digitalWrite(led_azul,  LOW);
    digitalWrite(led_amar,  HIGH);
    tone(buzzer, nota_verd);
    delay(100);
    noTone(buzzer);

    digitalWrite(led_verm,  HIGH);
    digitalWrite(led_verd,  LOW);
    digitalWrite(led_azul,  HIGH);
    digitalWrite(led_amar,  LOW);
    tone(buzzer, nota_verm);
    delay(100);
    noTone(buzzer);

  } //end for

  digitalWrite(led_verm,  LOW);
  digitalWrite(led_verd,  LOW);
  digitalWrite(led_azul,  LOW);
  digitalWrite(led_amar,  LOW);

  delay(500);
} //fim abertura

//////////////////////////***************************************

void jogo() {
  for (i = 1; i < 50;  i++) {
    seq[i] =  random(1, 5);
  }
  nivel = 1;
  jogar = 1;

  while (jogar == 1) {

    for (a = 1; a <= nivel; a++) {

      switch (seq[a]) {
        case 1:
          saida_verm();
          break;
        case 2:
          saida_verd();
          break;
        case 3:
          saida_azul();
          break;
        case 4:
          saida_amar();
          break;


      }

    }

    c = 1;
    verificar = 1;

    while (verificar == 1) {
      if (digitalRead(botao_verm) == 0) {
        saida_verm();
        if (seq[c] == 1) {
          proximo();
        } else {
          verificar = 0;
          jogar = 0;
        }
      }

      if (digitalRead(botao_verd) == 0) {
        saida_verd();
        if (seq[c] == 2) {
          proximo();
        } else {
          verificar = 0;
          jogar = 0;
        }
      }


      if (digitalRead(botao_azul) == 0) {
        saida_azul();
        if (seq[c] == 3) {
          proximo();
        } else {
          verificar = 0;
          jogar = 0;
        }
      }


      if (digitalRead(botao_amar) == 0) {
        saida_amar();
        if (seq[c] == 4) {
          proximo();
        } else {
          verificar = 0;
          jogar = 0;
        }
      }

    }
  }

}

 //fim jogo

void proximo() {
  c = c + 1;
  if (c == nivel + 1) {
    verificar = 0;
    jogar = 1;
    nivel = nivel + 1;
    delay(300);
  }
}

//////////////////////////***************************************

void saida_verm()   //aciona led_verm com nota_verm
{
  digitalWrite(led_verm, HIGH);
  tone(buzzer, nota_verm);
  delay(300);
  digitalWrite(led_verm, LOW);
  noTone(buzzer);
  delay(300);
} //fim saida_verm

void saida_verd()   //aciona led_verd
{
  digitalWrite(led_verd, HIGH);
  tone(buzzer, nota_verd);
  delay(300);
  digitalWrite(led_verd, LOW);
  noTone(buzzer);
  delay(300);
} //fim saida_verd

void saida_azul()   //aciona led_azul
{
  digitalWrite(led_azul, HIGH);
  tone(buzzer, nota_azul);
  delay(300);
  digitalWrite(led_azul, LOW);
  noTone(buzzer);
  delay(300);
} //fim saida_azul

void saida_amar()   //aciona led_amar
{
  digitalWrite(led_amar, HIGH);
  tone(buzzer, nota_amar);
  delay(300);
  digitalWrite(led_amar, LOW);
  noTone(buzzer);
  delay(300);
} //fim saida_amar

//////////////////////////***************************************

void finalizacao() {
  for (int j = 0; j < 3; j++)  {
    digitalWrite(led_verm,  HIGH);
    digitalWrite(led_verd,  HIGH);
    digitalWrite(led_azul,  HIGH);
    digitalWrite(led_amar,  HIGH);
    tone(buzzer, 2200);
    delay(200);
    digitalWrite(led_verm,  LOW);
    digitalWrite(led_verd,  LOW);
    digitalWrite(led_azul,  LOW);
    digitalWrite(led_amar,  LOW);
    noTone(buzzer);
    delay(200);
  }
}


