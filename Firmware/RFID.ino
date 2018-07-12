void read_tag(){
  if (!RFID_Reader.PICC_IsNewCardPresent()){
    return;
  }

  if(!RFID_Reader.PICC_ReadCardSerial()){
    return;
  }

  for(byte i=0; i<4; i++){
    nUID_PICC[i] = RFID_Reader.uid.uidByte[i];
  }

  String RFIDID = "";
  
  for (byte i=0; i<RFID_Reader.uid.size; i++) {
    RFIDID += RFID_Reader.uid.uidByte[i] < 0x10 ? "0" : "";
    RFIDID += String(RFID_Reader.uid.uidByte[i], HEX);
  }

  RFIDID.trim();
  RFIDID.toUpperCase();
  
  RFID_Reader.PICC_HaltA();
  RFID_Reader.PCD_StopCrypto1();

  //find the block according to the RFID tag
  int count = -1;
  for(int i=0; i<12; i++){
    if(RFIDID == IDs[i]){
      count = i;
      break;
    }
  }
  
  if(count != -1){
    if(shoes[count] == 0){
      //no shoes in the block
      //1.signal to put the shoes on tray
      digitalWrite(led_w ,HIGH);
      digitalWrite(led_r ,HIGH);
      
      //2.place the shoes in the rack
      //--I.Find the block is up or down
      if(count > 5){
        //go down
        stepper_updown(updown_diff, true);   
      }else{
        stepper_updown(small_step, true);  
      }
    
      //rotate the rack
      rotate_rack(count);
    
      //get the tray
      stepper_slider(4, 200, '+');
      stepper_updown(small_step, false);
      stepper_slider(4, 200, '-');
      
      //3.Bring the tray up
      if(count > 5){
        stepper_updown(updown_diff-small_step, false);
      }
      digitalWrite(led_w ,LOW);
      delay(5000);
      digitalWrite(led_r ,LOW);
      
      shoes[count] = 1;
      if(count > 5){
        stepper_updown(updown_diff-small_step, true);

        stepper_slider(4, 200, '+');
        stepper_updown(small_step, true);
        stepper_slider(4, 200, '-');
        stepper_updown(updown_diff, false);
        
        current_block = count - 6;
      }else{
        stepper_slider(4, 200, '+');
        stepper_updown(small_step, true);
        stepper_slider(4, 200, '-');
        stepper_updown(small_step, false);
        
        current_block = count; 
      }

      
    }else{
      digitalWrite(led_g ,HIGH);
      //have shoes in the block
      
      //1.go and bring the shoes

      //--I.Find the block is up or down
      if(count > 5){
        //go down
        stepper_updown(updown_diff, true);   
      }else{
        stepper_updown(small_step, true);  
      }

      //rotate the rack
      rotate_rack(count);
    
      //take the shoes
      stepper_slider(4, 200, '+');
      stepper_updown(small_step, false);
      stepper_slider(4, 200, '-');
      
      //3.Bring the shoes up
      if(count > 5){
        stepper_updown(updown_diff-small_step, false);
      }

      digitalWrite(led_w ,HIGH);
      delay(5000);
      digitalWrite(led_w ,LOW);
      
      shoes[count] = 0;
      if(count > 5){

        stepper_updown(updown_diff-small_step , true);
        
        stepper_slider(4, 200, '+');
        stepper_updown(small_step, true);
        stepper_slider(4, 200, '-');
        stepper_updown(updown_diff, false);
        
        current_block = count - 6;
      }else{

        //stepper_updown(updown_diff, true);


        stepper_slider(4, 200, '+');
        stepper_updown(small_step, true);
        stepper_slider(4, 200, '-');
        stepper_updown(small_step, false);
        
        current_block = count;
      }
      
      //2.signal to remove shoes on rack
      digitalWrite(led_g ,LOW);
    }
  }
}




void rotate_rack(int count){
  int blocks_tobe_rotated = 0;
  
  if(count > 5){
    count = count - 6;  
  }
   
  //select the suitable direction for rack rotation
  if(count != current_block){
      
    blocks_tobe_rotated = path_p(count,current_block);
    if(blocks_tobe_rotated <= 3){
      //rotate low direction (--->) '+'
      stepper_main(block_step*blocks_tobe_rotated, true);
        
    }else{
      blocks_tobe_rotated = path_n(count,current_block);
      //rotate high direction (<---) '-'
      stepper_main(block_step*blocks_tobe_rotated, false);
        
    }
  }
}





int path_p(int count, int current_b){
  int helper = current_b;
  int num_blocks = 0;
  while(true){
      helper = (helper+1)%6; 
      num_blocks++;
      
      if(helper == count){
         return num_blocks;
         break;
      }
  }
}


int path_n(int count, int current_b){
  int helper = current_b;
  int num_blocks = 0;
  while(true){
      helper = (helper-1)%6; 
      num_blocks++;
      
      if(helper == count){
         return num_blocks;
         break;
      }
  }
}
