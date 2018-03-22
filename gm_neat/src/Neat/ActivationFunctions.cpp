#include "Neat/ActivationFunctions.h"

namespace NEAT {


/////////////////////////////////////
// The set of activation functions //
/////////////////////////////////////

double af_sigmoid_unsigned(double aX, double aSlope, double aShift)
{
	return 1.0 / (1.0 + exp(-aSlope * aX - aShift));
}

double af_sigmoid_signed(double aX, double aSlope, double aShift)
{
	double tY = af_sigmoid_unsigned(aX, aSlope, aShift);
	return (tY - 0.5) * 2.0;
}

double af_tanh(double aX, double aSlope, double aShift)
{
	return tanh(aX * aSlope);
}

double af_tanh_cubic(double aX, double aSlope, double aShift)
{
	return tanh(aX * aX * aX * aSlope);
}

double af_step_signed(double aX, double aSlope, double aShift)
{
	double tY;
	if (aX > aShift)
	{
		tY = 1.0;
	}
	else
	{
		tY = -1.0;
	}

	return tY;
}

double af_step_unsigned(double aX, double aSlope, double aShift)
{
	if (aX > (0.5 + aShift))
	{
		return 1.0;
	}
	else
	{
		return 0.0;
	}
}

double af_gauss_signed(double aX, double aSlope, double aShift)
{
	double tY = exp(-aSlope * aX * aX + aShift); // TODO: Need separate a, b per activation function
	return (tY - 0.5)*2.0;
}

double af_gauss_unsigned(double aX, double aSlope, double aShift)
{
	return exp(-aSlope * aX * aX + aShift);
}

double af_abs(double aX, double aSlope, double aShift)
{
	return ((aX + aShift) < 0.0) ? -(aX + aShift) : (aX + aShift);
}

double af_sine_signed(double aX, double aFreq, double aShift)
{
	return sin(aX * aFreq + aShift);
}

double af_sine_unsigned(double aX, double aFreq, double aShift)
{
	double tY = sin((aX * aFreq + aShift));
	return (tY + 1.0) / 2.0;
}


double af_linear(double aX, double aSlope, double aShift)
{
	return (aX + aShift);
}


double af_relu(double aX, double aSlope, double aShift)
{
	return (aX > 0) ? aX : 0;
}


double af_softplus(double aX, double aSlope, double aShift)
{
	return log(1 + exp(aX));
}

double unsigned_sigmoid_derivative(double x)
{
	return x * (1 - x);
}

double tanh_derivative(double x)
{
	return 1 - x * x;
}

const fnActivationType ActivationFunctions[ActivationFunction::MAX_FUNCTION] =
{
	af_sigmoid_signed,
	af_sigmoid_unsigned,
	af_tanh,
	af_tanh_cubic,
	af_step_signed,          // Treshold (0 or 1)  (cutting plane)
	af_step_unsigned,
	af_gauss_signed,         // Gaussian           (symettry)
	af_gauss_unsigned,
	af_abs,                  // Absolute value |x| (another symettry)
	af_sine_signed,          // Sine wave          (smooth repetition)
	af_sine_unsigned,
	af_linear,               // Linear f(x)=x      (combining coordinate frames only)
	af_relu,                 // Rectifiers
	af_softplus,
};

}