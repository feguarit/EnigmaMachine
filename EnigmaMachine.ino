#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int valorDelay = 150;

int PosicaoX, PosicaoY;

int PosicaoUm = 1, PosicaoDois = 2, PosicaoTres = 3;
int LetraUm = 0, LetraDois = 0, LetraTres = 0;

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
    //Serial.begin(9600);//Serial.print(PosicaoX);
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

void criptoDescripto(int x, int y) {
  if (y == 0) {
    lcd.print(alfabetoLinha2[x]);
  } else if (y == 1) {
    lcd.print(alfabetoLinha1[x]);
  }
}

