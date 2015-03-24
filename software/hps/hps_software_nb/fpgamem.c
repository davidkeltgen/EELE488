/****************************************************************************
 * Author: David Keltgen                                                    *
 * Company: Montana State University                                        *
 * File Name: fpgamem.c                                                     *
 * Date:  March 17 2015                                                     *
 * Description:                                                             * 
 *				*
 *				*
 *				*
 ****************************************************************************/


#include "fpgamem.h"




/* 2^16 = 65536 memory addresses = 0x10000*/
/* since each address is 4 bytes, 0x40000 */


void delay()
{
 //   int idx = 0;
//    for(idx = 0 ; idx < 1024*768 ; idx ++)
        usleep(55688);
}


/* Need to write to unsigned memory */

int fpga_mem_write(void)
{
	char msg[256];
	int i = 0;
	int fd = 0;
	int wridx = 0;
	int rdidx = 0;
	int usec1, usec2, usec3;

	void *map_base = NULL, *virt_addr = NULL;

	struct timeval tpstart,tpend;
	float timeuse;

	const uint32_t ALT_LWFPGA_BASE         = 0xFF200000;
	const uint32_t ALT_LWFPGA_SYSID_OFFSET = 0x00010000;
	//const uint32_t ALT_LWFPGA_LED_OFFSET   = 0x00010040;
	const uint32_t ALT_LWFPGA_MEM_OFFSET   = 0x00040000;

	off_t target = ALT_LWFPGA_BASE ;

	char theTime[255];

	int wrarray[0x10000];
	int rdarray[0x10000];

	if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1)
		FATAL;
	record("FPGAMEM: /dev/mem opened.\n"); fflush(stdout);

	map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
	//map_base = mmap(0, 0x10100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target);

	if(map_base == (void *) -1)
		FATAL;
	sprintf(msg, "FPGAMEM: Memory mapped at address %p.\n", map_base); fflush(stdout); record(msg);

	virt_addr = map_base + (target & MAP_MASK);

	// Attempt to read the system ID peripheral
	uint32_t sysid = (*((unsigned long*) (virt_addr+ALT_LWFPGA_SYSID_OFFSET)) ) ;
	sprintf(msg, "FPGAMEM: LWFPGA Slave => System ID Peripheral value = 0x%x.\n", (unsigned int)sysid); record(msg);

	record("FPGAMEM: Writing to memory ...\n");
	void* access_addr;

		/*micro time*/
		struct  timeval tv;
		struct  timezone *tz ;
		struct  tm *tm_s = malloc(sizeof (struct tm));
		gettimeofday(&tv, &tz);
		tm_s = (struct tm *)localtime(&tv.tv_sec);
		sprintf(msg, "FPGAMEM: Before Write:              %d:%02d:%02d:%03d\n", tm_s->tm_hour, tm_s->tm_min, tm_s->tm_sec, (int)tv.tv_usec); record(msg);
		usec1 = (int)tv.tv_usec;
		/* 2^16 = 65536 memory addresses = 0x10000 */
		for( wridx = 0 ; wridx <= 0x00010000; wridx++) {

			wrarray[wridx] = wridx;
			uint32_t gray = wridx;
			access_addr = (virt_addr + (ALT_LWFPGA_MEM_OFFSET + (wridx * 4)));
			*((unsigned long*) (access_addr))= gray;
		}


		gettimeofday(&tv, &tz);
		tm_s = (struct tm *)localtime(&tv.tv_sec);
		sprintf(msg, "FPGAMEM: After Write, Before Read: %d:%02d:%02d:%03d\n", tm_s->tm_hour, tm_s->tm_min, tm_s->tm_sec, (int)tv.tv_usec); record(msg);
		usec2 = (int)tv.tv_usec;

		/*Read the values now */
		/* 2^16 = 65536 memory addresses */
		for( rdidx = 0 ; rdidx <= 0x00010000; rdidx++) {

			/*access address will range from 0x40000 to 0x80000*/
			access_addr = (virt_addr + (ALT_LWFPGA_MEM_OFFSET + (rdidx * 4)));
			rdarray[rdidx] = *((unsigned long*) (access_addr));

		}

		gettimeofday(&tv, &tz);
		tm_s = (struct tm *)localtime(&tv.tv_sec);
		sprintf(msg, "FPGAMEM: After Read:               %d:%02d:%02d:%03d\n", tm_s->tm_hour, tm_s->tm_min, tm_s->tm_sec, (int)tv.tv_usec); record(msg);
		usec3 = (int)tv.tv_usec;

		sprintf(msg, "FPGAMEM: Time to Write: %d\n", (usec2 - usec1)); record(msg);
		sprintf(msg, "FPGAMEM: Time to Read : %d\n\n", (usec3 - usec2)); record(msg);

	/*Check to make sure that the value that should have been written matches the
	 * value that was read
	 */
	//for(i = 0; i < 0x00010000; i++)
	//{
	//	sprintf(msg,"write value: 0x%X  read value: 0x%X index: 0x%X\n", wrarray[i], rdarray[i], i); record(msg);
	//}

	if(munmap(map_base, MAP_SIZE) == -1) FATAL;
	close(fd);

	return 0;
}




