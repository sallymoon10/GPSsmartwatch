const int homeButton = 7;
const int noButton= 8;

int homeButtonState= 0;
int noButtonState=0;

int userResponse(){
  homeButtonState= digitalRead(homeButton);
  noButtonState= digitalRead(noButton);
  
  if(homeButtonState == HIGH){
    userResponse= 1;
  }
  else if (noButtonState == HIGH){
    userResponse=0;
  }
  else{
    userResponse=0;
  }
}



