//
//  Math.cpp
//  BINS_file_analysis
//
//  Created by Den Fedorov on 27.08.2022.
//

#pragma once
#include "Math.h"
#include "File.h"

fl::Math::Math(const std::string & filename, const Read & file)
{

	_filename = filename;
	// find the first '\' from the end end remove all the characters from beginning to found '\'
	_filename.erase(_filename.begin(), (std::find(_filename.rbegin(), _filename.rend(), '\\')).base());
	// duration of file equals to vector's last value
	_duration = static_cast<unsigned int>(file._count.back());
	// find index of value '600'
	_gc_index = static_cast<unsigned int>(std::find(file._count.begin(), file._count.end(), 600) - file._count.begin());
	// convert heading, roll and pitch
	convert(_thdg, file._thdg);
	convert(_roll, file._roll);
	convert(_pitch, file._pitch);

	_heading = static_cast<unsigned int>(roundf(file._thdg[_gc_index]));

	if (_heading == 360)
	{
		_heading = 0;
	}
	// calculate standart deviation
	_X_deviation = deviation(file._gyro_X);
	_Y_deviation = deviation(file._gyro_Y);
	_Z_deviation = deviation(file._gyro_Z);
	// average gyroscope temperature
	_X_tempreture = static_cast<int>(std::reduce(file._t_gyro_X.begin(), file._t_gyro_X.end(), 0.0f) / _duration / 100);
	_Y_tempreture = static_cast<int>(std::reduce(file._t_gyro_Y.begin(), file._t_gyro_Y.end(), 0.0f) / _duration / 100);
	_Z_tempreture = static_cast<int>(std::reduce(file._t_gyro_Z.begin(), file._t_gyro_Z.end(), 0.0f) / _duration / 100);
}

fl::Math::~Math()
{
};

auto fl::Math::convert(Result & res, const std::vector<float> & v) -> void
{
	// modf returns integer (degree) and fractional (minutes) values
	res._minutes = (std::modf(v.at(_gc_index), &res._degrees)) * 60;
	// same here, but integer part goes to minutes, fractional to seconds
	res._seconds = (std::modf(res._minutes, &res._minutes)) * 60;
	res._seconds = roundf(res._seconds);
	// change sign if values are negative
	if (v[_gc_index] < 0)
	{
		res._minutes = -res._minutes;
		res._seconds = -res._seconds;
	}

	float fraction_value = roundf(v[_gc_index]) - v[_gc_index];

	if (fraction_value < 0)
	{
		fraction_value = -fraction_value;
	}

	res._minutes_error = (std::modf(fraction_value, &res._degrees_error)) * 60;
	res._seconds_error = (std::modf(res._minutes_error, &res._minutes_error)) * 60;
	res._seconds_error = roundf(res._seconds_error);
}

auto fl::Math::deviation(const std::vector<float> & v) -> float
{
	int index{ 0 };
	// calculate real duration of file
	std::size_t real_duration = v.size();
	// average value of vector
	float average{ std::reduce(v.begin(), v.end(), 0.0f) / real_duration };
	// new vector to store difference
	std::vector<float> difference(real_duration);
	// simple lamdba to calculate some math
	auto lambda{ [&average, &v, &index](float & d) -> void
	{
		d = v[index] - average;
		d *= d;
		++index;
	} };

	std::for_each(difference.begin(), difference.end(), lambda);
	average = std::reduce(difference.begin(), difference.end(), 0.0f);
	average /= real_duration - 1;

	return sqrtf(average);
}
