/*
 * printer.h
 *
 *  Created on: Apr 18, 2019
 *      Author: diegomtassis
 */

#ifndef INC_PRINTER_H_
#define INC_PRINTER_H_

#include <genesis.h>

#define WAIT_50			50
#define WAIT_750		750
#define WAIT_1100	 	1100

void printerOn();
void printerOff();
void clearScreen();

void print(const char *text);
void println(const char *text);

#endif /* INC_PRINTER_H_ */
