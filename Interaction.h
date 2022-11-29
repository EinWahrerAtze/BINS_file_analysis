//
//  interaction.h
//  BINS_file_analysis_3.0
//
//  Created by Denis Fedorov on 25.11.2022.
//

#pragma once
#include <map>
#include <set>
#include <memory>
#include <vector>
#include <string>
#include <string_view>
#include <filesystem>
#include "math.h"

namespace FL
{
	class Menu;
	class Interaction
	{
		friend class Short;
		friend class Long;
		friend class Convert;
		friend class Write;
		friend class Help;
	public:
		Interaction();
		~Interaction();
		void run() noexcept;
	private:
		void check_directory(std::string_view path) noexcept;
		void add(std::set<std::string>::iterator path) noexcept;
		void add(const std::filesystem::path & path) noexcept;
	private:
		enum class Format
		{
			DAT,
			TXT
		};
		Format _format;
		std::unique_ptr<Menu> _menu;
		std::set<std::string> _paths;
		std::vector<std::string> _errors;
		std::vector<std::string> _converted_files;
		std::multimap<std::string, Result> _files;
	};
}
