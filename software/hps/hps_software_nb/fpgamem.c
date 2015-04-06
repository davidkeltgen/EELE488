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




//const uint32_t DARK_OFFSET;
//const uint32_t RESPONSE_OFFSET;

/* Need to write to unsigned memory */

int fpga_mem_write(void)
{
	char msg[256];
        char theTime[256];
	int i = 0;
	int fd = 0;
	int wridx = 0;
	int rdidx = 0;
	int usec1, usec2, usec3;

	void *map_base = NULL, *virt_addr = NULL;
        
        const uint32_t FPGA_SYSID_OFFSET        = 0x00010000;
        //const uint32_t FPGA_LED_OFFSET        = 0x00010040;
        //const uint32_t FPGA_MEM_OFFSET        = 0x00040000;
        const uint32_t FPGA_BASE                = 0xFF200000;
        const uint32_t REGRESSION_OFFSET        ;
        const uint32_t ENABLE_OFFSET            = REGRESSION_OFFSET;
        const uint32_t MEANS_OFFSET             = REGRESSION_OFFSET + 0x00002000;
        const uint32_t STANDARDS_OFFSET         = REGRESSION_OFFSET + 0x00004000;
        const uint32_t CLASS_OFFSET             = REGRESSION_OFFSET + 0x00100000;

	off_t target = FPGA_BASE;	

	if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1)
		FATAL;
	record("FPGABLOCKMEM: /dev/mem opened.\n"); fflush(stdout);

        /* Memory map the regression component.*/
        /* Will be used for means, standard deviation, coefficients*/
	map_base = mmap(0, REGRESSION_MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~REGRESSION_MAP_MASK);
	//map_base = mmap(0, 0x10100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target);

	if(map_base == (void *) -1)
		FATAL;
	sprintf(msg, "FPGAMEM: Memory mapped at address %p.\n", map_base); fflush(stdout); record(msg);

	virt_addr = map_base + (target & REGRESSION_MAP_MASK);

	// Attempt to read the system ID peripheral
	uint32_t sysid = (*((unsigned long*) (virt_addr+FPGA_SYSID_OFFSET)) ) ;
	sprintf(msg, "FPGAMEM: LWFPGA Slave => System ID Peripheral value = 0x%x.\n", (unsigned int)sysid); record(msg);

	record("FPGAMEM: Writing to memory ...\n");
	void* access_addr;

        /*micro time*/
        struct timeval tv;
        struct  timezone *tz ;
        struct  tm *tm_s = malloc(sizeof (struct tm));
        gettimeofday(&tv, &tz);
        tm_s = (struct tm *)localtime(&tv.tv_sec);
        usec1 = (int)tv.tv_usec;


        /* Means matrix is 4 bytes times 1088 registers (4352 bytes total) */
        for( wridx = 0 ; wridx <= MEANS_MATRIX_SIZE; wridx++) {
                access_addr = (virt_addr + (MEANS_OFFSET + (wridx * 4)));
                *((unsigned long*) (access_addr))= means_fixed[wridx];
        }


        /* standard devation matrix is 4 bytes times 1088 registers (4352 bytes total) */
        for( wridx = 0 ; wridx <= STANDARDS_MATRIX_SIZE; wridx++) {
                access_addr = (virt_addr + (STANDARDS_OFFSET + (wridx * 4)));
                *((unsigned long*) (access_addr))= standards_fixed[wridx];
        }

        /* classification matrix is 4 bytes times 1088 times 50 registers (4352 bytes total) */
        int j;
        for( wridx = 0 ; wridx <= CLASS_MATRIX_SIZE; wridx++) {
            for(j = 0; j < 50; j++)
            {
                access_addr = (virt_addr + (CLASS_OFFSET + (wridx * 4)));
                *((unsigned long*) (access_addr))= class_fixed[wridx][j];

            }
        }

        gettimeofday(&tv, &tz);
        tm_s = (struct tm *)localtime(&tv.tv_sec);
        usec2 = (int)tv.tv_usec;

        record("FPGAMEM: Reading from memory ...\n");
        
        /*Read the values now */
        /* 1088\ memory addresses */
        for( rdidx = 0 ; rdidx <= MEANS_MATRIX_SIZE; rdidx++) {

                /*access address will range from 0x40000 to 0x80000*/
                sprintf(msg,"means[%d]: %d\n", rdidx, *((unsigned long*)(virt_addr + (MEANS_OFFSET + (rdidx * 4))))); record(msg);
        }

        /* 1088 memory addresses */
        for(rdidx = 0 ; rdidx <= MEANS_MATRIX_SIZE; rdidx++) {

                /*access address will range from 0x40000 to 0x80000*/
                sprintf(msg,"standards[%d]: %d\n", rdidx, *((unsigned long*)(virt_addr + (STANDARDS_OFFSET + (rdidx * 4))))); record(msg);
        }

         /* 1088 memory addresses */
        for(rdidx = 0 ; rdidx <= CLASS_MATRIX_SIZE; rdidx++) {
            for(j = 0; j < NUM_CLASSES; j++)
                /*access address will range from 0x40000 to 0x80000*/
                sprintf(msg,"class[%d][%d]:      %d\n", rdidx, j ,*((unsigned long*)(virt_addr + (CLASS_OFFSET + (rdidx * j * 4))))); record(msg);
        }

        gettimeofday(&tv, &tz);
        tm_s = (struct tm *)localtime(&tv.tv_sec);
        usec3 = (int)tv.tv_usec;

        sprintf(msg, "FPGAMEM: Time to Write: %d\n", (usec2 - usec1)); record(msg);
        sprintf(msg, "FPGAMEM: Time to Read : %d\n\n", (usec3 - usec2)); record(msg);

        /* Done with writing classification parameters to onchip memory, tell regression component it can start computing */
        
        access_addr = (virt_addr + (ENABLE_OFFSET));
        *((unsigned long*) (access_addr))= 0x00000001;
        
        
        /* Write to DRAM */
        
	if(munmap(map_base, REGRESSION_MAP_SIZE) == -1) FATAL;
	close(fd);
        
	return 0;
}

int fpga_mem_read(void)
{
    
    
    const uint32_t FPGA_BASE                = 0xFF200000;
    const uint32_t REGRESSION_OFFSET        ;
    const uint32_t ENABLE_CALC              = REGRESSION_OFFSET + 0x00000004;
    const uint32_t CALC_COMPLETE            = REGRESSION_OFFSET + 0x00000008;
    const uint32_t INNER_PRODUCT_OFFSET     = REGRESSION_OFFSET + 0x00200000;
    const uint32_t COUNTER_OFFSET           = REGRESSION_OFFSET; // plus something
    
    off_t target = FPGA_BASE;
    
    void *map_base = NULL, *virt_addr = NULL;
    virt_addr = map_base + (target & REGRESSION_MAP_MASK);
    int calc_done;
    
    
    for(;;)
    {
        //
        void* access_addr;
       
        //while(1)
        //{
                /* Enable interrupt pending? */
          //      access_addr = (virt_addr + ENABLE_CALC);
          //      *((unsigned long*) (access_addr))= 0x00000001;
        
                 /* Read the calc complete flag*/
        //        calc_done = *((unsigned long*)(virt_addr + (CALC_COMPLETE)));
        
                 /* If calc complete is 1, read the values*/
          //      if()
                
                 /* Clear that bit?*/
          //}
        /* Read the number of frames*/
        uint32_t num_frames = *((unsigned long*)(virt_addr + (COUNTER_OFFSET)));
        sleep(1);
    }
    
    
    
    
    
}




