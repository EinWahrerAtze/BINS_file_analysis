//
//  math.h
//  BINS_file_analysis_3.0
//
//  Created by Den Fedorov on 25.11.2022.
//

#pragma once
#include <memory>
#include <vector>

namespace FL
{
	struct Angle
	{
		float degree;
		float minute;
		float second;
		float degree_error;
		float minute_error;
		float second_error;
	};
	
	struct Result
	{
		Angle thdg;
		Angle roll;
		Angle pitch;
		unsigned int heading;
		unsigned int duration;
		float deviation_X;
		float deviation_Y;
		float deviation_Z;
		int temperature_X;
		int temperature_Y;
		int temperature_Z;
	};
	
	struct Row;
	class Load;
	class Math
	{
	public:
		Math();
		Result calculation(const std::vector<Row> & file);
	private:
		Angle convert(float value) noexcept;
		std::size_t find_index(const std::vector<Row> & file, const unsigned int Row::* member) const noexcept;
		float deviation(const std::vector<Row> & file, const float Row:: * member) const noexcept;
		template <typename T>
		T summ(const std::vector<Row> & file, const T Row:: * member) const noexcept;
	private:
		Result _result;
		const unsigned int _gc_time {600};
	};
}
