#include <avr/io.h>
#include <util/delay.h>               // for _delay_ms()


#define PIN_8 0b00000001 // PB0 -> pin 8 placa
#define PIN_9 0b00000010 // PB1 -> pin 9 placa
#define PIN_10 0b00000100 // PB2 -> pin 10 placa
#define PIN_11 0b00001000 // PB3 -> pin 11 placa
#define TOPE 0b00010000  // PB4 -> pin 12 placa

#define LED 0b00100000 // PB5 -> pin 13 placa

volatile unsigned char * puerto_b = (unsigned char *) 0x25;
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B */
volatile unsigned char * pin_b = (unsigned char *) 0x23;

const int retardo= 5;
const int MAX=350, MIN=0;
const float AJUSTE = 1.4222222222; #512 pasos por vueltas
int paso_actual, grado_actual;

void blink_led(int estado){
	if (estado == 1){
		*puerto_b = *puerto_b | LED;
	}else{
		*puerto_b = *puerto_b & (~LED);
	}
}

/* Apagado para que el motor no se caliente*/
void apagado(){
	*puerto_b = *puerto_b & (~PIN_8) & (~PIN_9) & (~PIN_10) & (~PIN_11);
}

void paso_derecha(){
	
	*puerto_b = *puerto_b | PIN_8 | PIN_9;
	*puerto_b = *puerto_b & (~PIN_10) & (~PIN_11);
	_delay_ms(retardo);
				            
	*puerto_b = *puerto_b | PIN_9 | PIN_10;
	*puerto_b = *puerto_b & (~PIN_8) & (~PIN_11);
	_delay_ms(retardo);
	
	*puerto_b = *puerto_b | PIN_10 | PIN_11;
	*puerto_b = *puerto_b & (~PIN_8) & (~PIN_9);
	_delay_ms(retardo);
	
	*puerto_b = *puerto_b | PIN_8 | PIN_11;
	*puerto_b = *puerto_b & (~PIN_9) & (~PIN_10);
	_delay_ms(retardo);
	
	apagado();
	paso_actual++;
}

void paso_izquierda(){
	
	*puerto_b = *puerto_b | PIN_10 | PIN_11;
	*puerto_b = *puerto_b & (~PIN_8) & (~PIN_9);
	_delay_ms(retardo);
				            
	*puerto_b = *puerto_b | PIN_9 | PIN_10;
	*puerto_b = *puerto_b & (~PIN_8) & (~PIN_11);
	_delay_ms(retardo);
	
	*puerto_b = *puerto_b | PIN_8 | PIN_9;
	*puerto_b = *puerto_b & (~PIN_10) & (~PIN_11);
	_delay_ms(retardo);
	
	*puerto_b = *puerto_b | PIN_8 | PIN_11;
	*puerto_b = *puerto_b & (~PIN_9) & (~PIN_10);
	_delay_ms(retardo);
	
	apagado();
	paso_actual--;
}


int get_posicion(){
	return grado_actual;
}

void set_posicion(int grado){
	int	grado_destino = grado % MAX;
	int paso_destino = floor(grado_destino*AJUSTE);
		if (paso_actual != paso_destino){
		    if (paso_actual < paso_destino){
			    while (paso_actual < paso_destino){
				    paso_derecha();
			    };
		    }else{
			    while (paso_actual > paso_destino){
				    paso_izquierda();
			    };
		    }
		}
        grado_actual = grado_destino;
}

void incrementar(int cant){
	int grado_destino = (grado_actual + cant) % MAX;
	set_posicion(grado_destino);
}

void decrementar(int cant){
	int grado_destino = MAX + ((grado_actual - cant) % MAX);
	set_posicion(grado_destino);
}

void motor_init(){
		volatile unsigned char entrada; // sensor de tope
		*puerto_b = 0;
		*puerto_b = *puerto_b | TOPE; // pin 12 se usa como entrada
		*(ddr_b) = *(ddr_b) | 0b00101111;
		
		entrada = *pin_b & TOPE;
		blink_led(1);/*enciendo led hasta que el motor vaya a la posicion inicial*/
		while (entrada == TOPE){
			paso_izquierda();
			entrada = *pin_b & TOPE;
		};
		paso_actual=0;
        grado_actual=0;
		blink_led(0);/*apaga led*/
}
