//
//  Math.h - class to do all the calculation and store variables
//  BINS_file_analysis
//
//  Created by Den Fedorov on 25.08.2022.
//

#pragma once
#include <numeric>
#include <vector>
#include <string>
#include <algorithm>


namespace fl
{
	class Read;
	class Write;
	class Interaction;

	class Math
	{
	public:
		~Math();
	private:
		friend class Interaction;
		friend class Read;
		friend class Write;
		// functor to use with std::sort function
		struct
		{
			auto operator()(const Math & lhs, const Math & rhs) -> bool
			{
				return lhs._heading < rhs._heading;
			}
		} compare;

		// convert the gyrocompass results to integer degrees-minutes-seconds values
		struct Result
		{
			float _degrees;
			float _minutes;
			float _seconds;
			float _degrees_error;
			float _minutes_error;
			float _seconds_error;
		};

		Math(const std::string & filename, const Read & file);

		Result _thdg;
		Result _roll;
		Result _pitch;

		std::string _filename;
		unsigned int _duration;
		unsigned int _gc_index;         // index of value "600" in the '_count' vector
		unsigned int _heading;
		float _X_deviation;
		float _Y_deviation;
		float _Z_deviation;
		int _X_tempreture;
		int _Y_tempreture;
		int _Z_tempreture;
		// convert results to integer values
		auto convert(Result & res, const std::vector<float> & v) -> void;
		// standart deviation of X, Y and Z gyroscopes
		auto deviation(const std::vector<float> & v) -> float;
	};
}
