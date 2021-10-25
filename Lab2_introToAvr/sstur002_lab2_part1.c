int main(void){

	while(1){
		
		unsigned char input = PINA & 0x03;
		unsigned char output = 0x00;
		
		//if PA1 && !PA1 return 1
		if(input == 0x01){
			output = 0x01;
		}
		else{
			output = 0x00;
		}

		PORTB = output;
	}
	return 0;
}


