Initial RKI port to the microblaze kcu105_qemu target.


Here are the compiler and linker options extracted from a waf build:

'microblaze-rtems6-gcc', 
'-MMD', 
'-Wall', 
'-Wmissing-prototypes', 
'-Wimplicit-function-declaration', 
'-Wstrict-prototypes', 
'-Wnested-externs', 

'-mlittle-endian', 
'-mno-xl-soft-div', 
'-mno-xl-soft-mul', 
'-Wl,-EL', 

'-O0', 
'-g', 

'-fdata-sections', 
'-ffunction-sections', 

'-Icpukit/include', 
'-I../../../cpukit/include',
'-Icpukit/score/cpu/microblaze/include', 
'-I../../../cpukit/score/cpu/microblaze/include', 
'-Ibsps/include', 
'-I../../../bsps/include', 
'-Ibsps/microblaze/include', 
'-I../../../bsps/microblaze/include', 
'-Ibsps/microblaze/microblaze_fpga/include', 
'-I../../../bsps/microblaze/microblaze_fpga/include', 
'-Itestsuites/support/include', 
'-I../../../testsuites/support/include', 
'../../../testsuites/samples/hello/init.c', 
'-c', '-oinitc.444.o', 
'-DHAVE_CONFIG_H=1']


'microblaze-rtems6-gcc', 
'testsuites/samples/hello/init.c.444.o', 
'-o/home/alan/rtems/rtems-src/rtems/build/microblaze/kcu105_qemu/testsuites/samples/hello.exe', 

'-Wl,-Bstatic', 
'-L.', 
'-lrtemscpu', 
'-lrtemsbsp', 
'-lrtemstest', 
'-Wl,-Bdynamic', 
'-qrtems', 

'-mlittle-endian', 
'-mno-xl-soft-div', 
'-mno-xl-soft-mul', 
'-Wl,-EL', 

'-Wl,--gc-sections', 

'-L/home/alan/rtems/rtems-src/rtems/bsps/microblaze/shared/start', 
'-L/home/alan/rtems/rtems-src/rtems/bsps/microblaze/microblaze_fpga/start', 

'-Wl,--wrap=printf', 
'-Wl,--wrap=puts', 
'-Wl,--wrap=putchar']

