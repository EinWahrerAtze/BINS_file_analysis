//
//  Interaction.h - main class to communicate with user
//  BINS_file_analysis
//
//  Created by Den Fedorov on 25.08.2022.
//

#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace fl
{
	class Math;
	class File;

	// reading from .dat or .txt files
	enum class Mode
	{
		DAT = 0,
		TXT
	};

	// menus to display
	enum class Menu
	{
		MAIN,
		READ,
		RESULT,
		RESULT_LIST,
		REMOVE,
		WRITE
	};

	class Interaction
	{
	public:
		Interaction();
		~Interaction();
		auto get_mode() const -> int;                      // get the active format
		auto set_mode() -> void;                           // set format of file to read
		auto set_index(char sign) -> void;                 // set index of added file to view or remove
		auto get_size() const->std::size_t;                // get informantion on how many files added
		auto check(const std::string & s) const -> int;    // user's input check
		auto menu(Menu menu) -> void;                      // main method to display menus
		auto remove(int n) -> void;                        // remove a certain or all files
		auto message(const std::string & s) -> void;       // a message to display to user
		auto read(const std::string & s) -> void;          // method to add new file/files
		auto write(const std::string & s) -> void;         // method to write analysis to .txt
	private:
		Mode _mode;                                        // reading format
		std::size_t _index;                                // index of added files
		mutable std::string _msg;                          // message to display
		std::vector<Math> _files;                          // vector of files
	};
}
