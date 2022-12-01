/**********************************************************************
 *
 * Filename:    motor.h
 * 
 * API para la aplicacion embebida 
 *
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

void motor_init(void);
int get_posicion(void);
void set_posicion(int);
void incrementar(int);
void decrementar(int);
void blink_led(int);

