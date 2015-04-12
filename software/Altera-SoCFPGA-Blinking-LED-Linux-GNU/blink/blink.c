/*
 * Copyright (c) 2013, Altera Corporation <www.altera.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - Neither the name of the Altera Corporation nor the
 *   names of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ALTERA CORPORATION BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <unistd.h>

int clear = 1;

void setLEDtrigger(int ledno, char* trigger, int size)
{
	FILE *fp;
	char dir[100];

	sprintf(dir, "/sys/class/leds/fpga_led%d/trigger", ledno);

	if ((fp = fopen(dir, "w")) == NULL) {
		printf("Failed to open the file %s\n", dir);
	}
	else {
		fwrite(trigger, 1, size, fp);
		fclose(fp);
	}
}

void setLEDBrightness(int ledno, int brightness)
{
	FILE *fp;
	char dir[100];
	char brightness_char[10];

	sprintf(dir, "/sys/class/leds/fpga_led%d/brightness", brightness);

	if ((fp = fopen(dir, "w")) == NULL) {
		printf("Failed to open the file %s\n", dir);
	}
	else {
		fwrite(brightness_char, 1, sizeof(brightness_char), fp);
		fclose(fp);
	}
}

void clear_led(int led)
{
	char trigger[] = "none";
	setLEDtrigger(led, trigger, sizeof(trigger));
	setLEDBrightness(led, 0);
}

int main(int argc, char** argv)
{
	FILE *fp;
	int led, delay_ms, i;
	char trigger[] = "timer";
	char dir[100];
	char delay[10];
	int blink_interval_ms;
	
	for (i = 1; i < argc; i++) {
		if (strcmp("--help", argv[i]) == 0) {
			printf("Usage %s: <LED number> <Blink delay (in ms)>\n"
				, argv[0]);
			return -1;
		}
	}

	if (argc != 3) {
		printf("Usage %s: <LED number> <Blink delay (in ms)>\n"
			, argv[0]);
		return -1;
	}
	else {
		led = atoi(argv[1]);
		delay_ms = atoi(argv[2]);
		if (led < 0 || led > 3) {
			printf("Invalid LED number. Valid LED range is 0-3\n");
			return -1;
		}
		if (delay_ms <= 0) {
			printf("Invalid blink delay.\n");
			return -1;
		}
	}
	
	/* Checking if scrolling is still happening 
	   if it is, we will inform user, and bail
	*/
	char get_fifo_scroll[2], seconds_bet_toggle[10];
	sprintf(get_fifo_scroll, "0");
	fp = fopen("/home/root/.altera/frequency_fifo_scroll", "w");
	if (fp == NULL) {
		printf("Failed opening fifo frequency_fifo_scroll\n");
		return -1;
	}
	fputs(get_fifo_scroll, fp);
	fclose(fp);
	fp = fopen("/home/root/.altera/get_scroll_fifo", "r");
	if (fp == NULL) {
		printf("Failed opening fifo get_scroll_fifo\n");
		return -1;
	}
	fgets(seconds_bet_toggle, 10, fp);
	fclose(fp);
	if (atoi(seconds_bet_toggle) > 0) {
		printf("LED is scrolling.\n"); 
		printf("Disable scroll_client before changing blink delay\n");
		return -1;
	}

	/* Blinking LED */
	clear_led(led);
	blink_interval_ms = delay_ms;
	
	/* Setting the trigger to blinking */
	setLEDtrigger(led, trigger, sizeof(trigger));
	/* Setting the delay */
	sprintf(dir, "/sys/class/leds/fpga_led%d/delay_on", led);
	if ((fp = fopen(dir, "w")) == NULL) {
		printf("Failed to open the file %s\n" , dir);
	}
	else {
		sprintf(delay, "%d", blink_interval_ms);
		fwrite(delay, 1, sizeof(delay), fp);
		fclose(fp);
	}
	sprintf(dir, "/sys/class/leds/fpga_led%d/delay_off", led);
	if ((fp = fopen(dir, "w")) == NULL) {
		printf("Failed to open the file %s\n" , dir);
	}
	else {
		sprintf(delay, "%d", blink_interval_ms);
		fwrite(delay, 1, sizeof(delay), fp);
		fclose(fp);
	}

	return 0;
}
