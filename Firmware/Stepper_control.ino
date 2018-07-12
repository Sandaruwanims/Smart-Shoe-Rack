void stepper_slider(int time_for_a_step, int steps, char direct){

  char temp = direct;
     
  if(temp=='+'){       
    int val = steps;
    if(val>=0 && val<=400){
      
      for(int a=val;a>0;a--){
        if(negative==1){
          if(i==7)
            i=0;
          else
            a=a+1;
            
          i=i+1;
          negative=0;
        }
            
        positive=1;
        if(i==0)      { digitalWrite(out0_1,HIGH);digitalWrite(out0_2,LOW);digitalWrite(out0_3,LOW);digitalWrite(out0_4,LOW);delay(time_for_a_step);  }
        else if(i==1) { digitalWrite(out0_1,HIGH);digitalWrite(out0_2,HIGH);digitalWrite(out0_3,LOW);digitalWrite(out0_4,LOW);delay(time_for_a_step); }
        else if(i==2) { digitalWrite(out0_1,LOW);digitalWrite(out0_2,HIGH);digitalWrite(out0_3,LOW);digitalWrite(out0_4,LOW);delay(time_for_a_step);  }
        else if(i==3) { digitalWrite(out0_1,LOW);digitalWrite(out0_2,HIGH);digitalWrite(out0_3,HIGH);digitalWrite(out0_4,LOW);delay(time_for_a_step); }
        else if(i==4) { digitalWrite(out0_1,LOW);digitalWrite(out0_2,LOW);digitalWrite(out0_3,HIGH);digitalWrite(out0_4,LOW);delay(time_for_a_step);  }
        else if(i==5) { digitalWrite(out0_1,LOW);digitalWrite(out0_2,LOW);digitalWrite(out0_3,HIGH);digitalWrite(out0_4,HIGH);delay(time_for_a_step); }
        else if(i==6) { digitalWrite(out0_1,LOW);digitalWrite(out0_2,LOW);digitalWrite(out0_3,LOW);digitalWrite(out0_4,HIGH);delay(time_for_a_step);  }
        else if(i==7) { digitalWrite(out0_1,HIGH);digitalWrite(out0_2,LOW);digitalWrite(out0_3,LOW);digitalWrite(out0_4,HIGH);delay(time_for_a_step); }
            
        if(i==7){
          i=0;continue;
        }
        i++;
      }
    }
      
    digitalWrite(out0_1,LOW);digitalWrite(out0_2,LOW);digitalWrite(out0_3,LOW);digitalWrite(out0_4,LOW);delay(time_for_a_step);  
    val=0; 
  
  }else if(temp=='-'){
    
     int val = steps;
     if(val>=0 && val<=400){
       for(int a=val;a>0;a--){

         if(positive==1){
           i=i-1;
           positive=0;
           a=a+1;
          }
         
         negative=1;            
         if(i==0)      { digitalWrite(out0_1,HIGH);digitalWrite(out0_2,LOW);digitalWrite(out0_3,LOW);digitalWrite(out0_4,LOW);delay(time_for_a_step);  }
         else if(i==1) { digitalWrite(out0_1,HIGH);digitalWrite(out0_2,HIGH);digitalWrite(out0_3,LOW);digitalWrite(out0_4,LOW);delay(time_for_a_step); }
         else if(i==2) { digitalWrite(out0_1,LOW);digitalWrite(out0_2,HIGH);digitalWrite(out0_3,LOW);digitalWrite(out0_4,LOW);delay(time_for_a_step);  }
         else if(i==3) { digitalWrite(out0_1,LOW);digitalWrite(out0_2,HIGH);digitalWrite(out0_3,HIGH);digitalWrite(out0_4,LOW);delay(time_for_a_step); }
         else if(i==4) { digitalWrite(out0_1,LOW);digitalWrite(out0_2,LOW);digitalWrite(out0_3,HIGH);digitalWrite(out0_4,LOW);delay(time_for_a_step);  }
         else if(i==5) { digitalWrite(out0_1,LOW);digitalWrite(out0_2,LOW);digitalWrite(out0_3,HIGH);digitalWrite(out0_4,HIGH);delay(time_for_a_step); }
         else if(i==6) { digitalWrite(out0_1,LOW);digitalWrite(out0_2,LOW);digitalWrite(out0_3,LOW);digitalWrite(out0_4,HIGH);delay(time_for_a_step);  }
         else if(i==7) { digitalWrite(out0_1,HIGH);digitalWrite(out0_2,LOW);digitalWrite(out0_3,LOW);digitalWrite(out0_4,HIGH);delay(time_for_a_step); }
         if(i==0){
           i=7;continue;
         }
         i--;
       }
     }
     
     digitalWrite(out0_1,LOW);digitalWrite(out0_2,LOW);digitalWrite(out0_3,LOW);digitalWrite(out0_4,LOW);delay(time_for_a_step);  
      val=0;
   }
   
}



void stepper_main(int steps, bool positive){
  if(positive==true){
    digitalWrite(dir_m,LOW);
    
    for(int i=0; i<steps; i++){
      digitalWrite(pul_m,HIGH);
      delay(1);
      digitalWrite(pul_m,LOW);
      delay(1);
    }
  }else{
    digitalWrite(dir_m,HIGH);
    
    for(int i=0; i<steps; i++){
      digitalWrite(pul_m,HIGH);
      delay(1);
      digitalWrite(pul_m,LOW);
      delay(1);
    }
  }
}




void stepper_updown(int steps, bool down){
  if(down==true){
    digitalWrite(dir_ud,HIGH); //go down
    
    for(int i=0; i<steps; i++){
      digitalWrite(pul_ud,HIGH);
      delay(1);
      digitalWrite(pul_ud,LOW);
      delay(1);
    }
  }else{
    digitalWrite(dir_ud,LOW); //go up
    
    for(int i=0; i<steps; i++){
      digitalWrite(pul_ud,HIGH);
      delay(1);
      digitalWrite(pul_ud,LOW);
      delay(1);
    }
  }
}

