#include "MantissaAndExponent.h"


template<size_t N>
int DinoTryingToLearn::MantissaAndExponent::bitsetToDecimal(const std::bitset<N>& bits)
{
	return static_cast<int>(bits.to_ullong());
}

template<size_t N>
std::pair<std::bitset<1>, std::bitset<N - 1>> DinoTryingToLearn::MantissaAndExponent::ExtractBits(const std::bitset<N>& SignAndExtraBit)
{
	std::bitset<1> SignBit(SignAndExtraBit[N - 1]);
	std::cout << "Sign bit = " << SignBit << std::endl;

	// to get the exponent/mantissa bits
	// bit masking
	std::bitset<N> bitMasking((1ULL << (N - 1)) - 1);
	std::bitset<N - 1> MantissaOrExponentBitset((SignAndExtraBit & bitMasking).to_ullong());
	return std::make_pair(SignBit, MantissaOrExponentBitset);
}

// for sign bit,0 = positive, 1 = negative 
std::pair<int, int> DinoTryingToLearn::MantissaAndExponent::Formula(float floatingPointValue)
{
	// to get the sign bit of the floating point value
	int sign = 0;
	if (floatingPointValue >= 0) 
	{ 
		sign = 0; 
	}
	else 
	{
		sign = 1; 
	}

	std::bitset<1> signBit(sign);

	int exponent = std::ilogb(floatingPointValue);
	double mantissa = floatingPointValue / (std::scalbn(1.0, exponent));

	std::cout << "Step 1 (a): " << std::endl;
	std::cout << "Sign value (decimal) = " << sign << std::endl;
	std::cout << "Mantissa value (decimal) = " << mantissa << std::endl;
	std::cout << "Exponent value (decimal) = " << exponent << std::endl << std::endl;

	int bias = 127;
	// 127 is the (bias) and is interpreted as 0
	// anything above is positive, anything below it negative
	std::bitset<8> exponentBits(bias + exponent);

	int implicitLeadingVal;
	// checking if the mantissa value has a 1 in the front.
	if (mantissa > 1 && mantissa < 2)
	{
		mantissa -= 1;
		implicitLeadingVal = 23;
	}
	else
	{
		implicitLeadingVal = 1;
	}

	int precision = 23;
	std::bitset<23> mantissaBits;

	for (int i = 0; i < precision; ++i)
	{
		mantissa *= 2;
		if (mantissa >= 1) 
		{ 
			// setting the desired bit to 1
			mantissaBits.set(precision - 1 - i); 
			mantissa -= 1;
		}
	}
	
	std::cout << "Step 1 (b) : " << std::endl;
	std::cout << "Sign in Binary = " << sign << std::endl;
	std::cout << "Exponent in Binary = " << exponentBits << std::endl;
	std::cout << "Mantissa in binary = " << mantissaBits << std::endl << std::endl;

	std::cout << "Step 1 (c) : " << std::endl;
	std::cout << "Sign = " << sign << std::endl;
	std::cout << "Exponent = " << bitsetToDecimal(exponentBits) << std::endl;
	std::cout << "Mantissa = " << bitsetToDecimal(mantissaBits) << std::endl << std::endl;

	// formula to get from binary format to decimals
	// ((-1) ^ Sign) * ((2 ^ 23) + Mantissa) * (2 ^ (Exponent - 127 - 23)) = decimal value
	int encodeSignAndMantissa = bitsetToDecimal(addBitsets(signBit, mantissaBits));
	int encodeExponent = bitsetToDecimal(exponentBits) - bias;
	return std::make_pair(encodeSignAndMantissa, encodeExponent);
}

std::bitset<24> DinoTryingToLearn::MantissaAndExponent::addBitsets(const std::bitset<1> signBitset, const std::bitset<23> mantissaBitset)
{
	unsigned long long sign = signBitset.to_ullong();
	unsigned long long mantissa = mantissaBitset.to_ullong();
	unsigned long long sum = sign + mantissa;
	std::bitset<24> signAndMantissaBits(sum);
	return signAndMantissaBits;
}

void DinoTryingToLearn::MantissaAndExponent::GetFloatingPointValue(int exponent, int signAndMantissa)
{
	std::cout << "Step 2 (a) : " << std::endl;
	// converting mantissa base 10 to binary
	std::cout << "Incoming Mantissa value = " << signAndMantissa << std::endl << std::endl;
	std::bitset<24> SignAndMantissaBitset(signAndMantissa);

	std::cout << "Step 2 (b) : " << std::endl;
	std::cout << "Sign and Mantissa bitset (base 2) = " << SignAndMantissaBitset << std::endl << std::endl;
	auto extractSignAndMantissaBits = ExtractBits(SignAndMantissaBitset);

	std::cout << "Step 2 (c) : " << std::endl;
	// extracting the floating point value sign bit
	std::cout << "Checking the Sign Bit = " << extractSignAndMantissaBits.first << std::endl;
	// convert sign bitset to base 10
	int encodeSign = bitsetToDecimal(extractSignAndMantissaBits.first);
	std::cout << "Checking the Mantissa = " << extractSignAndMantissaBits.second << std::endl;
	// encode the mantissa value back to base 10
	int encodeMantissa = bitsetToDecimal(extractSignAndMantissaBits.second);
	std::cout << "Encode Mantissa value = " << encodeMantissa << std::endl << std::endl;
	

	// converting exponent base 10 to binary
	int bias = exponent + 127;
	std::cout << "Step 2 (d) : " << std::endl;
	std::cout << "Incoming Exponent Value = " << bias << std::endl;
	std::bitset<8> exponentBitset(exponent);
	std::cout << "The exponent value as bitset (base 2) = " << exponentBitset << std::endl << std::endl;
	//auto extractSignAndExponentBits = ExtractBits(exponentBitset);
	//// extracting the sign of the exponent
	//std::cout << "The Exponent Sign Bit = " << extractSignAndExponentBits.first << std::endl;
	//// extracting the exponent bits
	//std::cout << "The Exponent Bit = " << extractSignAndExponentBits.second << std::endl;
	int encodeExponent = bitsetToDecimal(exponentBitset);
	std::cout << "Step 2 (e) : " << std::endl;
	std::cout << "Encode Exponent value = " << encodeExponent << std::endl << std::endl;


	std::cout << "Step 2 (f) : " << std::endl;
	float floatingPointValue = FloatingPointValueFormula(encodeSign, encodeExponent, encodeMantissa);
	std::cout << "Floating Point Value = " << floatingPointValue << std::endl << std::endl;
}

float DinoTryingToLearn::MantissaAndExponent::FloatingPointValueFormula(int sign, int exponent, int mantissa)
{
	float results = pow(-1, sign) * (mantissa + pow(2,23)) * pow(2, exponent - 23);
	return results;
}

