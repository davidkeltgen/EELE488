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
        const uint32_t FPGA_BASE                = 0xC0000000; //fullweight bridge
        const uint32_t REGRESSION_OFFSET        = 0x00000000; //actually mem_0
        const uint32_t ENABLE_OFFSET            = REGRESSION_OFFSET;
        const uint32_t MEANS_OFFSET             = (REGRESSION_OFFSET + 0x00002000);
        const uint32_t STANDARDS_OFFSET         = (REGRESSION_OFFSET + 0x00004000);
        const uint32_t CLASS_OFFSET             = (REGRESSION_OFFSET + 0x00100000);
        const uint32_t IP_OFFSET				= (REGRESSION_OFFSET + 0x00200000);

        //const uint32_t COUNTER_OFFSET           = (REGRESSION_OFFSET + 0x001352C8); // 54450 registers * 4 bytes per register
        const uint32_t COUNTER_OFFSET           = (REGRESSION_OFFSET + 0x00000043);   																			// plus 0x00100000 offset

	off_t target = FPGA_BASE;

	record("Going to open mem\n");

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
	//uint32_t sysid = (*((unsigned long*) (virt_addr+FPGA_SYSID_OFFSET)) ) ;
	//sprintf(msg, "FPGAMEM: LWFPGA Slave => System ID Peripheral value = 0x%x.\n", (unsigned int)sysid); record(msg);

	record("FPGAMEM: Writing to memory ...\n");
	void* access_addr;

        /*micro time*/
        struct timeval tv;
        struct  timezone *tz ;
        struct  tm *tm_s = malloc(sizeof (struct tm));
        gettimeofday(&tv, &tz);
        tm_s = (struct tm *)localtime(&tv.tv_sec);
        usec1 = (int)tv.tv_usec;

        uint32_t testarr[512];
        for(i = 0; i < 512; i++)
        {
        	testarr[i] = i;
        }

        //for(i = 0; i < MEANS_MATRIX_SIZE; i++)
        //{
        ///	printf("standards_fixed before: %d\n", standards_fixed[i]);
        //}



        /* Means matrix is 4 bytes times 1088 registers (4352 bytes total) */
        for( wridx = 0 ; wridx < MEANS_MATRIX_SIZE; wridx++) {
                access_addr = (virt_addr + (MEANS_OFFSET + (wridx * 4)));
                *((unsigned long*) (access_addr))= means_fixed[wridx];
                //*((unsigned long*) (access_addr))= testarr[wridx];
        }


        /* standard devation matrix is 4 bytes times 1088 registers (4352 bytes total) */
        for( wridx = 0 ; wridx < STANDARDS_MATRIX_SIZE; wridx++) {
                access_addr = (virt_addr + (STANDARDS_OFFSET + (wridx * 4)));
                *((unsigned long*) (access_addr))= standards_fixed[wridx];
        }
//
//        /* classification matrix is 4 bytes times 1088 times 50 registers (4352 bytes total) */
//        uint32_t counter = 0;
//        while(counter < (CLASS_MATRIX_SIZE * 50))
//        {
//           access_addr = (virt_addr + (CLASS_OFFSET + (counter * 4) ));
//            //printf("access addr: %08X\n", access_addr);
//            *((unsigned long*) (access_addr))= 2;
//            counter++;
//        }


       // int j;
       // for( wridx = 0 ; wridx < CLASS_MATRIX_SIZE; wridx++) {
       //     for(j = 0; j < 10; j++)
        //    {


         //   }
       // }

        //printf("counter: %d\n", counter);

        gettimeofday(&tv, &tz);
        tm_s = (struct tm *)localtime(&tv.tv_sec);
        usec2 = (int)tv.tv_usec;

        record("FPGAMEM: Reading from memory ...\n");
        int readarray[MEANS_MATRIX_SIZE];

        /*Read the values now */

        /*  memory addresses */
        int var;
        for( rdidx = 0 ; rdidx < MEANS_MATRIX_SIZE; rdidx++) {

                /*access address will range from 0x40000 to 0x80000*/
        		access_addr = (virt_addr + (MEANS_OFFSET + (rdidx * 4)));
        		var = *((unsigned long*) (access_addr));
        }

        /*  memory addresses */
        for(rdidx = 0 ; rdidx < STANDARDS_MATRIX_SIZE; rdidx++) {

                /*access address will range from 0x40000 to 0x80000*/
    		access_addr = (virt_addr + (STANDARDS_OFFSET + (rdidx * 4)));
    		var = *((unsigned long*) (access_addr));
        }



        gettimeofday(&tv, &tz);
        tm_s = (struct tm *)localtime(&tv.tv_sec);
        usec3 = (int)tv.tv_usec;

        sprintf(msg, "FPGAMEM: Time to Write: %f ms\n", (usec2 - usec1) / 1000.0 ); record(msg);
        sprintf(msg, "FPGAMEM: Time to Read : %f ms\n\n", (usec3 - usec2) / 1000.0); record(msg);

        for( rdidx = 0 ; rdidx < MEANS_MATRIX_SIZE; rdidx++) {

                /*access address will range from 0x40000 to 0x80000*/
        		access_addr = (virt_addr + (MEANS_OFFSET + (rdidx * 4)));
        		readarray[rdidx] = *((unsigned long*) (access_addr));
                sprintf(msg,"means[%d]: %08X, %08X \n", rdidx, means_fixed[rdidx], readarray[rdidx]); record(msg);
        }

        for( rdidx = 0 ; rdidx < STANDARDS_MATRIX_SIZE; rdidx++) {

                /*access address will range from 0x40000 to 0x80000*/
        		access_addr = (virt_addr + (STANDARDS_OFFSET + (rdidx * 4)));
        		readarray[rdidx] = *((unsigned long*) (access_addr));
                sprintf(msg,"standards[%d]: %08X, %08X \n", rdidx, standards_fixed[rdidx], readarray[rdidx]); record(msg);
        }

		access_addr = (virt_addr + (ENABLE_OFFSET));
		uint32_t classes = *((unsigned long*) (access_addr));
		sprintf(msg,"classes?: %08X\n", classes); record(msg);

		access_addr = (virt_addr + (ENABLE_OFFSET));
				*((unsigned long*) (access_addr))= 0x00000001;

        /* 1088 memory addresses */
//        int counter = 0; int j;
//       for(rdidx = 0 ; rdidx < CLASS_MATRIX_SIZE; rdidx++) {
//           for(j = 0; j < 50; j++)
//           {
//               /*access address will range from 0x40000 to 0x80000*/
//           	access_addr = (virt_addr + (CLASS_OFFSET + (counter * 4)));
//           	var = *((unsigned long*) (access_addr));
//               sprintf(msg,"class[%d][%d]:      %d\n", rdidx, j , var); record(msg);
//               counter++;
//           }
//       }

       access_addr = (virt_addr + (0x00000040));
	   uint32_t rows = *((unsigned long*) (access_addr));
	   sprintf(msg,"rows: %08X\n", rows); record(msg);

        /* Done with writing classification parameters to onchip memory, tell camera, dram and regression */
        /*  components that they can start running */
        while(1)
        {
        	access_addr = (virt_addr + (COUNTER_OFFSET));
			uint32_t num_frames = *((unsigned long*) (access_addr));
			sprintf(msg,"FRAME COUNT: %08X\n", num_frames); record(msg);

           	access_addr = (virt_addr + (ENABLE_OFFSET));
           	var = *((unsigned long*) (access_addr));
               sprintf(msg,"enable: %d\n", var); record(msg);



               for(rdidx = 0 ; rdidx < 102400; rdidx++) {

                       /*access address will range from 0x40000 to 0x80000*/
                   	access_addr = (virt_addr + (IP_OFFSET + (rdidx * 4)));
                   	var = *((unsigned long*) (access_addr));
                       sprintf(msg,"inner product[%d]: %d\n", rdidx, var); record(msg);

               }
               sleep(30);
        }


        
        //while(1)
        //{

//        	access_addr = (virt_addr + (0x00000108));
//        	       // *((unsigned long*) (access_addr))= 0x00000001;
//

//
//        	 access_addr = (virt_addr + (ENABLE_OFFSET));
//        	        uint32_t is_enable = *((unsigned long*) (access_addr));
//        	        sprintf(msg,"enable?: %08X\n", is_enable); record(msg);
//
//        	access_addr = (virt_addr + (COUNTER_OFFSET));
//			uint32_t num_frames = *((unsigned long*) (access_addr));
			//sprintf(msg,"FRAME COUNT: %08X\n", num_frames); record(msg);
			//sleep(10);

        //}

        /* Write to DRAM */
        
	if(munmap(map_base, REGRESSION_MAP_SIZE) == -1) FATAL;
	close(fd);
        
	return 0;
}

int fpga_mem_read(void)
{
    printf("inside fpga_mem_read\n");
	int fd = 0;
    const uint32_t FPGA_BASE                = 0xC0000000;
    const uint32_t REGRESSION_OFFSET        = 0x00000000;
    const uint32_t ENABLE_CALC              = (REGRESSION_OFFSET + 0x00000004); // write a 1 to turn on interrupts
    const uint32_t CALC_COMPLETE            = (REGRESSION_OFFSET + 0x00000008); // write a 1 to this address to clear the interrupt
    const uint32_t INNER_PRODUCT_OFFSET     = (REGRESSION_OFFSET + 0x00200000);
    //const uint32_t COUNTER_OFFSET           = (REGRESSION_OFFSET + 0x0010D4B6);

    off_t target = FPGA_BASE;
    
    void *map_base = NULL, *virt_addr = NULL;

    map_base = mmap(0, REGRESSION_MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~REGRESSION_MAP_MASK);
    virt_addr = map_base + (target & REGRESSION_MAP_MASK);
    int calc_done;
    printf("flag1\n");

    
    
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
        access_addr = (virt_addr + (REGRESSION_OFFSET));
        printf("flag2\n");
        uint32_t num_frames = *((unsigned long*) (access_addr));
        printf("FRAME COUNT: %08X", num_frames);
        printf("flag3\n");
        sleep(1);
    }

    return 0;
    
    
    
    
}




