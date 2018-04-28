// --- Commande d'un StepStick/Driver A4988 ----------------------
// A4988_Test.ino
//
// Commande d'un moteur pas-à-pas à l'aide d'un pilote A4988 avec
//     Arduino.
//
// Un projet www.mchobby.be (vente de kit et composant)
// Meurisse D. - Licence CC-SA-BY
//
// Un tutoriel http://mchobby.be/wiki/index.php?title=A4988
// Ou Acheter un StepStick A4988
//    http://shop.mchobby.be/product.php?id_product=349
//

#define pinEnable 50 // Activation du driver/pilote
#define pinStep    40 // Signal de PAS (avancement)
#define pinDir     41 // Direction 


void setup(){
  Serial.begin(9600);
  Serial.println("Test A4988");
  
  pinMode( pinEnable, OUTPUT );
  pinMode( pinDir   , OUTPUT );
  pinMode( pinStep  , OUTPUT );
}

void loop(){
  int i = 0;
  
  digitalWrite( pinDir   , HIGH); // Direction avant
  digitalWrite( pinStep  , LOW);  // Initialisation de la broche step
  
  // Avance de 200 pas
  for( i=0; i<200; i++){
    Serial.println( i );
    digitalWrite( pinStep, HIGH );
    delay( 10 );
    digitalWrite( pinStep, LOW );
    delay( 10 );
  } 
  
  // Changer de direction
  digitalWrite( pinDir   , LOW); // Direction avant
  
  // Refaire 200 pas dans l'autre sens
  for( i=0; i<200; i++){
    Serial.println( i );
    digitalWrite( pinStep, HIGH );
    delay( 1 );
    digitalWrite( pinStep, LOW );
    delay( 1 );
  } 
  
  delay( 5000 );
}
