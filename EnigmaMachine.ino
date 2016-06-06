#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//Usado como base os rotores do modelo German Railway (Rocket) de 1941:
//https://en.wikipedia.org/wiki/Enigma_rotor_details
char* Rotor1[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ","JGDQOXUSCAMIFRVTPNEWKBLZYH"};
char* Rotor2[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ","NTZPSFBOKMWRCJDIVLAEYUXHGQ"};
char* Rotor3[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ","JVIUBHTCDYAKEQZPOSGXNRMWFL"};
char* Rotor4[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ","QYHOGNECVPUZTFDJAXWMKISRBL"};
char* Rotor5[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ","QWERTZUIOASDFGHJKPYXCVBNML"};

char* RotorNumeroUm[2];
char* RotorNumeroDois[2];
char* RotorNumeroTres[2];

int valorDelay = 200;

int PosicaoX, PosicaoY;

int PosicaoUm = 1, PosicaoDois = 2, PosicaoTres = 3;
int LetraUm = 3, LetraDois = 7, LetraTres = 12;

char alfabetoCompleto[30] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int numeroPaginaLCD = 1;
int montaPagina = 0;

char alfabetoLinha1[15] = "ABCDEFGHIJKLM";
char alfabetoLinha2[15] = "NOPQRSTUVWXYZ";

byte Seta[8] = {   
        B00100,   
        B01110,   
        B11111,   
        B00100,   
        B00100,   
        B00100,   
        B00100, 
};  

void setup() {
    Serial.begin(9600);//Serial.print(PosicaoX);
    lcd.begin(16, 2);
    lcd.createChar(0, Seta); 
    apresentacao();
    delay(500);
}

void loop() {

   //######################################
   //## Pagina Numero Rotores
   //## numeroPaginaLCD = 1
   //######################################

   if (numeroPaginaLCD == 1) {
       if (montaPagina == 0) {
          PosicaoX = 13;
          lcd.clear();
          sequenciaDosRotores();
          montaPagina = 1;
       }
       int botao;  
       botao = analogRead(0); 
       if (botao < 100) { //Direita
          if (PosicaoX < 15) {
            PosicaoX = PosicaoX + 1;
            delay(valorDelay);
          }
       } else if (botao < 200) { //Acima
          mudaRotor(1);
          delay(valorDelay);
       } else if (botao < 400) { //Abaixo
          mudaRotor(-1);
          delay(valorDelay);
       }  else if (botao < 600) { //Esquerda
          if (PosicaoX > 13) {
            PosicaoX = PosicaoX - 1;
            delay(valorDelay);
          }
       } else if (botao < 800) { //Select
          if ((PosicaoUm == PosicaoDois) || (PosicaoDois == PosicaoTres) || (PosicaoUm == PosicaoTres)) {
            lcd.noBlink();
            lcd.setCursor(12,1);
            lcd.print("erro");
            delay(1000);
            lcd.setCursor(12,1);
            lcd.print("    ");
            lcd.blink();
          } else {
            numeroPaginaLCD = numeroPaginaLCD + 1;
            montaPagina = 0;
          }
          delay(valorDelay);
       }
       lcd.setCursor(PosicaoX,0);
   } //fim numeroPaginaLCD == 1

   //######################################
   //## Pagina Sequencia Inicial
   //## numeroPaginaLCD = 2
   //######################################
   
   if (numeroPaginaLCD == 2) {
       if (montaPagina == 0) {
          PosicaoX = 13;
          lcd.clear();
          sequenciaInicial();
          montaPagina = 1;
       }
       int botao;  
       botao = analogRead(0);    
       if (botao < 100) { //Direita
          if (PosicaoX < 15) {
            PosicaoX = PosicaoX + 1;
            delay(valorDelay);
          }        
       } else if (botao < 200) { //Acima
          mudaLetra(1);
          delay(valorDelay);
       } else if (botao < 400) { //Abaixo
          mudaLetra(-1);
          delay(valorDelay);        
       } else if (botao < 600) { //Esquerda
          if (PosicaoX > 13) {
            PosicaoX = PosicaoX - 1;
            delay(valorDelay);
          }        
       } else if (botao < 800) { //Select
          numeroPaginaLCD = numeroPaginaLCD + 1;
          montaPagina = 0;
          delay(valorDelay);
       }
       lcd.setCursor(PosicaoX,0);
   } //fim numeroPaginaLCD == 2

   //######################################
   //## Pagina Alfabeto
   //## numeroPaginaLCD = 3
   //######################################
   
   if (numeroPaginaLCD == 3) {
       if (montaPagina == 0) {
          PosicaoX = 0;
          PosicaoY = 0;
          lcd.clear();
          configuraEnigmaMachine();
          exibeAlfabeto();
          montaPagina = 1;
       }
       int botao;  
       botao = analogRead(0);  //Leitura do valor da porta analógica A0
       if (botao < 100) {  
        //Direita
        if (PosicaoX < 12) {
          PosicaoX = PosicaoX + 1;
          delay(valorDelay); 
        } 
       }  
       else if (botao < 200) { 
        //Acima 
        if (PosicaoY == 1) {
          PosicaoY = PosicaoY - 1;
          delay(valorDelay); 
        } 
       }  
       else if (botao < 400){  
        //Abaixo  
        if (PosicaoY == 0) {
          PosicaoY = PosicaoY + 1;
          delay(valorDelay);  
        }
       }  
       else if (botao < 600){  
        //Esquerda
        if (PosicaoX > 0) {
          PosicaoX = PosicaoX - 1;
          delay(valorDelay); 
        } 
       }  
       else if (botao < 800){  
        //Select
        lcd.setCursor(15,0);
        criptoDescripto(PosicaoX,PosicaoY);
       }  
       lcd.setCursor(PosicaoX,PosicaoY);
   } //fim numeroPaginaLCD == 3
}

void apresentacao() {
  lcd.setCursor(00,00);lcd.print(" Maquina Enigma");
  lcd.setCursor(00,01);lcd.print("   Versao 1.0");  
}

void sequenciaDosRotores() {
  lcd.setCursor(00,00);lcd.print("Sequencia    ");
  lcd.print(PosicaoUm);
  lcd.print(PosicaoDois);
  lcd.print(PosicaoTres);
  lcd.setCursor(00,01);lcd.print("dos Rotores");
  lcd.blink();
}

void mudaRotor(int n) {
  lcd.noBlink();
  if (PosicaoX == 13){
      PosicaoUm = PosicaoUm + n;
      if (PosicaoUm < 1) {
        PosicaoUm = 1;
      } else if (PosicaoUm > 5) {
        PosicaoUm = 5;
      }
      lcd.print(PosicaoUm);
  } else if (PosicaoX == 14){
      PosicaoDois = PosicaoDois + n;
      if (PosicaoDois < 1) {
        PosicaoDois = 1;
      } else if (PosicaoDois > 5) {
        PosicaoDois = 5;
      }      
      lcd.print(PosicaoDois);
  } else {
      PosicaoTres = PosicaoTres + n;
      if (PosicaoTres < 1) {
        PosicaoTres = 1;
      } else if (PosicaoTres > 5) {
        PosicaoTres = 5;
      }          
      lcd.print(PosicaoTres);
  }
  lcd.setCursor(PosicaoX,0);
  lcd.blink();
}

void sequenciaInicial() {
  lcd.setCursor(00,00);lcd.print("Sequencia    ");
  lcd.print(alfabetoCompleto[LetraUm]);
  lcd.print(alfabetoCompleto[LetraDois]);
  lcd.print(alfabetoCompleto[LetraTres]);
  lcd.setCursor(00,01);lcd.print("Inicial");
  lcd.blink();
}

void mudaLetra(int n) {
  lcd.noBlink();
  if (PosicaoX == 13){
      LetraUm = LetraUm + n;
      if (LetraUm < 0) {
        LetraUm = 25;
      } else if (LetraUm > 25) {
        LetraUm = 0;
      }
      lcd.print(alfabetoCompleto[LetraUm]);
  } else if (PosicaoX == 14){
      LetraDois = LetraDois + n;
      if (LetraDois < 0) {
        LetraDois = 25;
      } else if (LetraDois > 25) {
        LetraDois = 0;
      }
      lcd.print(alfabetoCompleto[LetraDois]);
  } else {
      LetraTres = LetraTres + n;
      if (LetraTres < 0) {
        LetraTres = 25;
      } else if (LetraTres > 25) {
        LetraTres = 0;
      }
      lcd.print(alfabetoCompleto[LetraTres]);  
  }
  lcd.setCursor(PosicaoX,0);
  lcd.blink();
}

void exibeAlfabeto() {
  lcd.setCursor(00,00);lcd.print("ABCDEFGHIJKLM");
  lcd.setCursor(00,01);lcd.print("NOPQRSTUVWXYZ");
  lcd.setCursor(15,01);lcd.write(byte(0));
}

void configuraEnigmaMachine() {
  //Carrega Primeiro Rotor
  if (PosicaoUm == 1) {
    RotorNumeroUm[0] = Rotor1[0];
    RotorNumeroUm[1] = Rotor1[1];
  } else if (PosicaoUm == 2) {
    RotorNumeroUm[0] = Rotor2[0];
    RotorNumeroUm[1] = Rotor2[1];
  } else if (PosicaoUm == 3) {
    RotorNumeroUm[0] = Rotor3[0];
    RotorNumeroUm[1] = Rotor3[1];
  } else if (PosicaoUm == 4) {
    RotorNumeroUm[0] = Rotor4[0];
    RotorNumeroUm[1] = Rotor4[1];
  } else if (PosicaoUm == 5) {
    RotorNumeroUm[0] = Rotor5[0];
    RotorNumeroUm[1] = Rotor5[1];
  } 
  //Carrega Segundo Rotor
  if (PosicaoDois == 1) {
    RotorNumeroDois[0] = Rotor1[0];
    RotorNumeroDois[1] = Rotor1[1];
  } else if (PosicaoDois == 2) {
    RotorNumeroDois[0] = Rotor2[0];
    RotorNumeroDois[1] = Rotor2[1];
  } else if (PosicaoDois == 3) {
    RotorNumeroDois[0] = Rotor3[0];
    RotorNumeroDois[1] = Rotor3[1];
  } else if (PosicaoDois == 4) {
    RotorNumeroDois[0] = Rotor4[0];
    RotorNumeroDois[1] = Rotor4[1];
  } else if (PosicaoDois == 5) {
    RotorNumeroDois[0] = Rotor5[0];
    RotorNumeroDois[1] = Rotor5[1];
  }   
  //Carrega Terceiro Rotor
  if (PosicaoTres == 1) {
    RotorNumeroTres[0] = Rotor1[0];
    RotorNumeroTres[1] = Rotor1[1];
  } else if (PosicaoTres == 2) {
    RotorNumeroTres[0] = Rotor2[0];
    RotorNumeroTres[1] = Rotor2[1];
  } else if (PosicaoTres == 3) {
    RotorNumeroTres[0] = Rotor3[0];
    RotorNumeroTres[1] = Rotor3[1];
  } else if (PosicaoTres == 4) {
    RotorNumeroTres[0] = Rotor4[0];
    RotorNumeroTres[1] = Rotor4[1];
  } else if (PosicaoTres == 5) {
    RotorNumeroTres[0] = Rotor5[0];
    RotorNumeroTres[1] = Rotor5[1];
  } 
  //Posiciona Vetores nas Letras Iniciais
  for (int i=0; i <= 25; i++){
    if (RotorNumeroUm[0][0] == alfabetoCompleto[LetraUm]) {
      break;
    } else {
      moveRotor(RotorNumeroUm);
    }
  }
  for (int i=0; i <= 25; i++){
    if (RotorNumeroDois[0][0] == alfabetoCompleto[LetraDois]) {
      break;
    } else {
      moveRotor(RotorNumeroDois);
    }
  }
  for (int i=0; i <= 25; i++){
    if (RotorNumeroTres[0][0] == alfabetoCompleto[LetraTres]) {
      break;
    } else {
      moveRotor(RotorNumeroTres);
    }
  }
  Serial.print(RotorNumeroUm[0]);
  Serial.print("\n");
  Serial.print(RotorNumeroUm[1]);
  Serial.print("\n");  
  Serial.print(RotorNumeroDois[0]);
  Serial.print("\n");
  Serial.print(RotorNumeroDois[1]);
  Serial.print("\n");  
  Serial.print(RotorNumeroTres[0]);
  Serial.print("\n");  
  Serial.print(RotorNumeroTres[1]);  
}

void moveRotor(char** rotor) {
  char primeiraVogal = rotor[0][0];
  char primeiraVogalEspelho = rotor[1][0];
  for (int i=0; i <= 24; i++){
    rotor[0][i] = rotor[0][i+1];
    rotor[1][i] = rotor[1][i+1];
  }
  rotor[0][25] = primeiraVogal;
  rotor[1][25] = primeiraVogalEspelho;
}

void criptoDescripto(int x, int y) {
  //Em desenvolvimento ainda...
  //Incluido essa lógica apenas para testar a tela
  if (y == 0) {
    lcd.print(alfabetoLinha2[x]);
  } else if (y == 1) {
    lcd.print(alfabetoLinha1[x]);
  }
}

