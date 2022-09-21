int minutes = 0;
int hour = 10;
int seconds = 0;
int date = 4;
int month = 8;
int year = 2000;

void timeUpdate(){
  
   minutes++;
  if(minutes >59){
    minutes = 0;
    hour ++;
  }

  if(hour > 23){
    hour = 0;
    date ++;
  }
 if(month == 9 || month == 4 || month == 6 || month == 11){
  if(date >30){
    date = 1;
    month++ ;
  }
  }else if(month == 2){
    if(date >28){
    date = 1;
    month++ ;
    }
  }else{
    if(date >31){
    date = 1;
    month++ ;
  }
 }
}
