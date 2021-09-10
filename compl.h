#pragma once
struct cmpl
{
	double Re, Im;

	cmpl operator+(const cmpl B)
	{
		Re += B.Re;
		Im += B.Im;
		return *this;
	}

	cmpl operator*(const cmpl B)
	{
		Re = Re * B.Re - Im * B.Im;
		Im = Re * B.Im - Im * B.Re;
		return *this;
	}

	float operator!( void )
	{
		return Re * Re + Im * Im;
	}

	cmpl(float a, float b)
	{
		Re = a, Im = b;
	}

	cmpl(void)
	{
		Re = Im = 0;
	}

	int Julia(const cmpl &C)
	{
		int n = 0;
		while (n <= 255 && !*this <= 4)
		{
			cmpl Z0 = *this;
			*this = Z0*Z0 + C;
			n++;
		}
		return n;
	}
};