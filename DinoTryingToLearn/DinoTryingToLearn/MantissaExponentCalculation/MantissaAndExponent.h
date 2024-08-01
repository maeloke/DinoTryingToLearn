#pragma once
#include <iostream>
#include <cmath>
#include <bitset>
#include <limits>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <string>

namespace DinoTryingToLearn
{

	class MantissaAndExponent
	{
	public:
		std::pair<int, int> Formula(float floatingPointValue);

		/// <summary> This template function is declared to convert binary values to decimal values </summary>
		/// <typeparam name="N"></typeparam>
		/// <param name="bitset"></param>
		/// <returns> </returns>
		template<size_t N>
		int bitsetToDecimal(const std::bitset<N>& bitset);

		std::bitset<24> addBitsets(const std::bitset<1> signBitset, const std::bitset<23> mantissaBitset);

		// exponent will send from 1 to 127
		void GetFloatingPointValue(int exponent, int signAndMantissa);

		//extract the mantissa and exponent bit
		template <size_t N>
		static std::pair<std::bitset<1>,std::bitset<N -1>> ExtractBits(const std::bitset<N>& SignAndExtraBit);

		float FloatingPointValueFormula(int sign, int exponent, int mantissa);


	};
}

//// sign and mantissa value as binary
//std::bitset<24> decimalToBinary(signAndMantissa);
//std::cout << "Sign & Mantissa Binary Value = " << decimalToBinary << std::endl;
////ExtractBits(signAndMantissa);
//// sign and mantissa val