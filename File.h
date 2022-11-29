//
//  file.hpp
//  BINS_file_analysis_3.0
//
//  Created by Denis Fedorov on 25.11.2022.
//

#pragma once
#include <map>
#include <vector>
#include <fstream>
#include <filesystem>
#include <string_view>

namespace FL
{
	struct Row
	{
		unsigned int count, mode;
		float system_time, mode_time;
		float thdg, roll, pitch;
		float heading, azimuth;
		float latitude, longtitude;
		float H, Ve, Vn, Vu;
		float dAt_X, dAt_Y, dAt_Z;
		float dVt_X, dVt_Y, dVt_Z;
		float gyro_X, gyro_Y, gyro_Z;
		float acc_X, acc_Y, acc_Z;
		float Ucplc_X, Ucplc_Y, Ucplc_Z;
		float Uhfo_X, Uhfo_Y, Uhfo_Z;
		float Fout_X, Fout_Y, Fout_Z;
		float Fdith_X, Fdith_Y, Fdith_Z;
		int gyro_X_temperature, gyro_Y_temperature, gyro_Z_temperature;
		unsigned int acc_X_temperature, acc_Y_temperature, acc_Z_temperature;
		unsigned int dpb_X_temperature, dpb_Y_temperature, dpb_Z_temperature;
		float drift_X, drift_Y, drift_Z;
		unsigned int faults;
		float D12, D13, D21, D23, D31, D32;
		float Mg1, Mg2, Mg3;
		float Wo1, Wo2, Wo3;
		float E12, E13, E21, E23, E31, E32;
		float Ma1, Ma2, Ma3;
		float Ao1, Ao2, Ao3;
		unsigned int reserve, crc8, error;
	};
	
	class File
	{
	protected:
		explicit File(std::string_view path);
		virtual ~File() = default;
		std::filesystem::path _path;
	};
	
	struct Result;
	class Save : public File
	{
	public:
		explicit Save(std::string_view path);
		void write(const std::vector<Row> & file);
		void write(const std::multimap<std::string, Result> & files);
	private:
		std::ofstream _fout;
	};
	
	class Load : public File
	{
	public:
		explicit Load(std::string_view path);
		virtual void find_start() = 0;
		virtual const std::vector<Row> & read() = 0;
	protected:
		std::ifstream _fin;
		std::vector<Row> _file;
		const unsigned int _start {60};
	};
	
	class DAT : public Load
	{
	public:
		explicit DAT(std::string_view path);
		void find_start() override;
		const std::vector<Row> & read() override;
	};
	
	class TXT : public Load
	{
	public:
		explicit TXT(std::string_view path);
		void find_start() override;
		const std::vector<Row> & read() override;
	};
}
