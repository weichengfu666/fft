CC = aarch64-linux-gnu-gcc
fft:fft_test.o fftmisc.o fourierf.o
	$(CC) -o fft fft_test.o fftmisc.o fourierf.o -lm
fft_test.o:fft_test.c
	$(CC) -c fft_test.c
fftmisc.o:fftmisc.c
	$(CC) -c fftmisc.c
fourierf.o:fourierf.c
	$(CC) -c fourierf.c
clean:
	rm *.o
.PHONY:clean
	
