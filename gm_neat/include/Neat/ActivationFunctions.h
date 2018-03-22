#pragma once 

#include <cmath>

namespace NEAT {

//////////////////////////////////////////////////////////
// Enumeration for all possible activation function types
//////////////////////////////////////////////////////////
enum ActivationFunction : unsigned int
{
	SIGNED_SIGMOID = 0,   // Sigmoid function   (default) (blurred cutting plane)
	UNSIGNED_SIGMOID,
	TANH,
	TANH_CUBIC,
	SIGNED_STEP,          // Treshold (0 or 1)  (cutting plane)
	UNSIGNED_STEP,
	SIGNED_GAUSS,         // Gaussian           (symettry)
	UNSIGNED_GAUSS,
	ABS,                  // Absolute value |x| (another symettry)
	SIGNED_SINE,          // Sine wave          (smooth repetition)
	UNSIGNED_SINE,
	LINEAR,               // Linear f(x)=x      (combining coordinate frames only)

	RELU,                 // Rectifiers
	SOFTPLUS,
	MAX_FUNCTION,
};

typedef double(*fnActivationType)(double aX, double aSlope, double aShift);

double af_sigmoid_unsigned(double aX, double aSlope, double aShift);
double af_sigmoid_signed(double aX, double aSlope, double aShift);
double af_tanh(double aX, double aSlope, double aShift);
double af_tanh_cubic(double aX, double aSlope, double aShift);
double af_step_signed(double aX, double aSlope, double aShift);
double af_step_unsigned(double aX, double aSlope, double aShift);
double af_gauss_signed(double aX, double aSlope, double aShift);
double af_gauss_unsigned(double aX, double aSlope, double aShift);
double af_abs(double aX, double aSlope, double aShift);
double af_sine_signed(double aX, double aFreq, double aShift);
double af_sine_unsigned(double aX, double aFreq, double aShift);
double af_linear(double aX, double aSlope, double aShift);
double af_relu(double aX, double aSlope, double aShift);
double af_softplus(double aX, double aSlope, double aShift);

double unsigned_sigmoid_derivative(double x);
double tanh_derivative(double x);


extern const fnActivationType ActivationFunctions[ActivationFunction::MAX_FUNCTION];

}