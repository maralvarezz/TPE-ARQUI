#ifndef INTERRUPS_H_
#define INTERRUPS_H_

#include "idtLoader.h"

//Handler de teclado
void syscallHandler(void);

//hace el llamado a la interrupcion de teclado y hace el end of interrupt
void interrupcion_teclado(void);

//Handler de timer
void _irq00Handler(void);

//excepción de división por cero
void exception_zero_division(void);

//excepción de código de operación inválido
void exception_op_code(void);

//código para hacer el guardado de los registros en ese momento
void guardar_registros(void);

//limpia la bandera de interrupciones y deshabulita las mismas
void _cli(void);

//establece la bandera de interrupciones, habilitando las interrupciones.
void _sti(void);

//esta función habilita las interrupciones, detiene la CPU hasta que ocurra una interrupción
void _hlt(void);

//esta función configura la máscara del PIC maestro con el valor proporcionado en el registro di
void picMasterMask(uint8_t mask);

//esta función configura la máscara del PIC esclavo con el valor proporcionado en el registro di
void picSlaveMask(uint8_t mask);

//Termina la ejecución de la cpu.
void haltcpu(void);

#endif
