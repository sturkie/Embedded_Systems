
int main(void){

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	//DDRC = 0xFF; PORTC = 0x00;
	
	//unsigned char input = PINA & 0x0F;
	//unsigned char countAvailable;
	//unsigned char counter = 0x00;
	

	while(1){
		
		unsigned char input = PINA & 0x0F;
	//unsigned char countAvailable;
	unsigned char counter = 0x00;
		
		for(int i = 0; i < 4; i++){
			if((input & 0x01) == 0x00){
				counter++;
			}
			input = input >> 1;
		}
		
		if(counter > 0){
			PORTB = counter;
		}
		else{
			PORTB = 0x80;
		}
		
		//PORTB = counter;
		
	}


	return 0;
}
