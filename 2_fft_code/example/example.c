/*
 * Test for realfft(3).
 */

#define		N	8
#define 	pi	3.1415926535897932384626434

double sin (), cos ();
char *malloc ();

main ()
{
	unsigned i, j;

	double in [N], out [N];

	printf ("Example #1:\n");
	for (i = 0; i < N; i++)
		in [i] = i;
	printsamp (in, N);

	realfft (in, N, out);
	printf ("After a fast fft\n");
	printampl (out, N);

	/* check */
	printf ("A reverse slow ft gives:\n");
	srft (out, N, in);
	printsamp (in, N);

	printf ("And the reverse fast ft yields:\n");
	realrft (out, N, in);
	printsamp (in, N);

	printf ("\n\nExample #2\n");
	for (i = 0; i < N; i++) {
		in [i] = 0;
		for (j = 0; j <= N / 2; j++)
			in [i] += cos (2 * pi * i * j / N) +
				  sin (2 * pi * i * j / N);
	}
	printsamp (in, N);

	realfft (in, N, out);
	printf ("After a forward fast ft:\n");
	printampl (out, N);

	/* check */
	printf ("A reverse slow ft yields:\n");
	srft (out, N, in);
	printsamp (in, N);

	printf ("And a reverse fast ft gives:\n");
	realrft (out, N, in);
	printsamp (in, N);
}

printampl (ampl, n)
double *ampl;
unsigned n;
{
	unsigned i;

	printf ("Amplitudes\n");

	if (n == 0)
		return;

	printf ("%f (dc)\n", ampl [0]);
	for (i = 1; i < (n + 1) / 2; i++)
		printf ("%f, %f (%u-th harmonic)\n", ampl [2 * i - 1],
						     ampl [2 * i], i);
	if (n % 2 == 0)
		printf ("%f (Nyquist)\n", ampl [n - 1]);

	printf ("\n");
}

printsamp (samp, n)
double *samp;
unsigned n;
{
	unsigned i;
	printf ("Samples\n");

	for (i = 0; i < n; i++)
		printf ("%f\n", samp [i]);
	
	printf ("\n");
}

/*
 * Slow reverse fourier transform.  In [0] contains dc, in [n - 1] Nyquist.
 * This is just a gimmick to compare with realfft(3).
 */
srft (in, n, out)
double *in;
unsigned n;
double *out;
{
	unsigned i, j;

	for (i = 0; i < n; i++) {
		out [i] = in [0];			/* dc */
		for (j = 1; j < (n + 1) / 2; j++)	/* j-th harmonic */
			out [i] += in [2 * j - 1] * cos (2 * pi * i * j / n) +
				   in [2 * j] * sin (2 * pi * i * j / n);
		if (n % 2 == 0)				/* Nyquist */
			out [i] += in [n - 1] * cos (2 * pi * i * j / n);
	}
}
