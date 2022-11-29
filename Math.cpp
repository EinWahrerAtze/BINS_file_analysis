//
//  math.cpp
//  BINS_file_analysis_3.0
//
//  Created by Den Fedorov on 25.11.2022.
//

#include <cmath>
#include <numeric>
#include <algorithm>
#include "math.h"
#include "file.h"

namespace FL
{
	Math::Math() : _result {} {}
	
	Result Math::calculation(const std::vector<Row> & file)
	{
		std::size_t index {find_index(file, &Row::count)};
		if (index == 0)
		{
			throw std::invalid_argument {"Отсутствует выставка: "};
		}
		_result.thdg = convert(file.at(index).thdg);
		_result.roll = convert(file.at(index).roll);
		_result.pitch = convert(file.at(index).pitch);
		_result.heading = static_cast<unsigned int>(std::roundf(file.at(index).thdg));
		if (_result.heading == 360)
		{
			_result.heading = 0;
		}
		_result.duration = file.back().count;
		_result.deviation_X = deviation(file, &Row::gyro_X);
		_result.deviation_Y = deviation(file, &Row::gyro_Y);
		_result.deviation_Z = deviation(file, &Row::gyro_Z);
		_result.temperature_X = summ<int>(file, &Row::gyro_X_temperature) / static_cast<int>(file.size()) / 100;
		_result.temperature_Y = summ<int>(file, &Row::gyro_Y_temperature) / static_cast<int>(file.size()) / 100;
		_result.temperature_Z = summ<int>(file, &Row::gyro_Z_temperature) / static_cast<int>(file.size()) / 100;
		return _result;
	}
	
	Angle Math::convert(float value) noexcept
	{
		Angle angle {};
		angle.minute = std::modf(value, &angle.degree) * 60;
		angle.second = std::modf(angle.minute, &angle.minute) * 60;
		angle.second = std::roundf(angle.second);
		if (value < 0.0f)
		{
			angle.minute = -angle.minute;
			angle.second = -angle.second;
		}
		float fraction_value {std::roundf(value) - value};
		if (fraction_value < 0.0f)
		{
			fraction_value = -fraction_value;
		}
		angle.minute_error = std::modf(fraction_value, &angle.degree_error) * 60;
		angle.second_error = std::modf(angle.minute_error, &angle.minute_error) * 60;
		angle.second_error = std::roundf(angle.second_error);
		return angle;
	}
	
	std::size_t Math::find_index(const std::vector<Row> & file, const unsigned int Row:: * member) const noexcept
	{
		for (auto i {file.cbegin()}; i != file.cend(); ++i)
		{
			if ((*i).*member == _gc_time)
			{
				return std::distance(file.cbegin(), i);
			}
		}
		return 0;
	}
	
	float Math::deviation(const std::vector<Row> & file, const float Row:: * member) const noexcept
	{
		float average {summ<float>(file, member) / file.size()};
		std::vector<float> difference;
		difference.reserve(file.size());
		for (auto i {file.cbegin()}; i != file.cend(); ++i)
		{
			difference.push_back(static_cast<float>(std::pow((*i).*member - average, 2)));
		}
		average = std::reduce(difference.cbegin(), difference.cend(), 0.0f);
		average /= file.size() - 1;
		return std::sqrt(average);
	}
	
	template <typename T>
	T Math::summ(const std::vector<Row> & file, const T Row:: * member) const noexcept
	{
		T sum {};
		for (auto i = file.cbegin(); i != file.cend(); ++i)
		{
			sum += (*i).*member;
		}
		return sum;
	}
}
