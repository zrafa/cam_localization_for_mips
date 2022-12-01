#include "motor.h"
#include "serial.h"
#include <util/delay.h> 

/**********************************************************************
Protocolo de mensajes para comunicarse con el motor:
H10 (llevar motor hastra la posicion grado 10)
F05 (avanzar 5 grados)
B05 (retroceder 5 grados)
GET (que devuelva un int con la posicion del grado actual del motor)
RES (para hacer el INIT a la posicion grado 0)
 **********************************************************************/

char cadena[4];


int string_to_int(char *posicion){
	int i=0;
	int salida = 0;
	
	while (posicion[i] != '\0'){
		i++;
	}
	
	if (i == 0){ // cadena vacia
		salida = 0;
	}else{
			switch (i){
					case 1: salida = posicion[0]-48;break;
					case 2: salida = (posicion[0]-48)*10 + (posicion[1]-48) ;break;
					case 3: salida = (posicion[0]-48)*100 + (posicion[1]-48)*10 + (posicion[2]-48);break;
					default: salida = 0;
				}
	}
	return salida;
}

char* int_to_string(int posicion){
	if (posicion==0){
		cadena[0]='0';
		cadena[1]='\0';
	}else{
		if (posicion < 10){
			cadena[0]=posicion + 48;
			cadena[1]='\0';
		}else{
			if (posicion < 100){
				cadena[0]= ((int) (posicion / 10)) + 48;
				cadena[1]= (posicion % 10) + 48;
				cadena[2]='\0';
			}else{
				cadena[0]= ((int) (posicion / 100)) + 48;
				cadena[1]= ((int)((posicion % 100)/10)) + 48;
				cadena[2]= ((posicion % 100)%10) + 48;
				cadena[3]='\0';
			}
		}
	}
	return cadena;
}

int main(void){

	serial_init();
    motor_init();
    serial_put_str("OK\n");
	char* aux;

    
    char c,d,u; /* centena decena unidad*/
    int pos=0, pos_actual;
    
    while(1){
		char *posicion = serial_get_str();
        switch(posicion[0]){
            case 'g': case 'G': 
                pos_actual = get_posicion();
                _delay_ms(500);
                char* pos_cad = int_to_string(pos_actual);
                serial_put_str(pos_cad);
                serial_put_str("\n");
                break;
            
            case 'i': case 'I': 
                aux = &posicion[1];
                pos = string_to_int(aux);
			    incrementar(pos);
			    serial_put_str("OK\n");
                break;
            
            case 'd': case 'D': 
                aux = &posicion[1];
                pos = string_to_int(aux);
			    decrementar(pos);
			    serial_put_str("OK\n");
                break;

            case '0': case '1': case '2': case '3':case '4':case '5':case '6':case '7':case '8':case '9':
                pos = string_to_int(posicion);
			    set_posicion(pos);
			    serial_put_str("OK\n");
                break;
        }
		
	}
    return 0;
}


