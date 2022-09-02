//
//  main.cpp
//  BINS_file_analysis
//
//  Created by Den Fedorov on 25.08.2022.
//

#include "Interaction.h"
#include "File.h"
#include "Math.h"
#include <iostream>
#include <filesystem>
#if defined(_WIN32)
#include <Windows.h>
#endif

void clear()
{
#if defined(_WIN32)
	system("cls");
	SetConsoleOutputCP(65001);
#else
	system("clear");
#endif
}

auto main(int argc, const char * argv[]) -> int
{
#ifdef _WIN32
	setlocale(LC_ALL, "ru_RU.UTF-8");
//	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(65001);
	SetConsoleCP(1251);
#else
	system("clear");
#endif

	std::cout << "Добро пожаловать в программу анализа файлов! ";
	// user's input
	std::string input;
	fl::Interaction interaction;
	// main loop
	while (true)
	{
		interaction.menu(fl::Menu::MAIN);
		getline(std::cin, input);

		switch (interaction.check(input))
		{
			// add new file
			case 'a':
			case 'A':
			{
				std::string extentions[2] = { ".dat", ".txt" };

				while (true)
				{
					clear();
					interaction.menu(fl::Menu::READ);
					getline(std::cin, input);

					if (input.empty())
					{
						continue;
					}

					switch (input.front())
					{	// add all files in folder and subfolders
						case 'a':
						case 'A':
						{
							// in case file's name begins with 'a'
							if (input.size() > 1)
							{
								// get_mode() returns '0' or '1'
								input += extentions[interaction.get_mode()];
								// read() reads file with given name and extestion
								interaction.read(input);
								continue;
							}
							else
							{
								// '.\' is base path to be passed in read() as part of filename
								std::string filename{ ".\\" };
								// for conversion from std::path to std::string
								std::filesystem::path temp;
								// get current path where program is located
								std::filesystem::path this_path{ std::filesystem::current_path() };
								// check folder and all the subfolders with recursive direcory iterator for .txt or .dat files
								for (std::filesystem::directory_entry entry : std::filesystem::recursive_directory_iterator(this_path))
								{
									if (entry.path().filename().extension().string() == extentions[interaction.get_mode()])
									{
										// get only rest of path where file found (.\subfolder\file.xxx)
										temp = std::filesystem::relative(entry);
										// corvert it to std::string
										filename += temp.string();
										interaction.read(filename);
										filename = ".\\";
									}
								}

								if (interaction.get_size() == 0)
								{
									interaction.message("Нет файлов с расширением " + extentions[interaction.get_mode()] + '!');
									continue;
								}
								else
								{
									interaction.message("Все файлы добавлены!");
									continue;
								}
							}
						}
						// change format (.dat or .txt)
						case 'c':
						case 'C':
						{
							interaction.set_mode();
							continue;
						}
						// go back to main menu
						case 'x':
						case 'X':
						{
							if (interaction.get_size() != 0)
							{
								interaction.message("Файлов добавлено: " + std::to_string(interaction.get_size()));
							}

							break;
						}
						// default choice if user wants to add custom file
						default:
						{
							input += extentions[interaction.get_mode()];
							interaction.read(input);
							continue;
						}
					}

					clear();
					break;
				}

				break;
			}
			// show analysis
			case 'q':
			case 'Q':
			{
				clear();
				// // in case no files added
				if (interaction.get_size() == 0)
				{
					interaction.message("Нет добавленных файлов!");
					break;
				}
				else
				{
					while (true)
					{
						clear();
						interaction.menu(fl::Menu::RESULT);
						getline(std::cin, input);

						switch (interaction.check(input))
						{
							// show all added files on one screen
							case 's':
							case 'S':
							{
								clear();

								while (true)
								{
									interaction.menu(fl::Menu::RESULT_LIST);
									getline(std::cin, input);

									switch (interaction.check(input))
									{
										case 'x':
										case 'X':
										{
											break;
										}
										default:
										{
											clear();
											interaction.message("ÕÂ‚ÂÌ˚È ‚‚Ó‰!");
											continue;
										}
									}

									break;
								}

								continue;
							}
							// go backwards (--index)
							case 'q':
							case 'Q':
							{
								interaction.set_index('-');
								continue;
							}
							// go forward (++index)
							case 'w':
							case 'W':
							{
								interaction.set_index('+');
								continue;
							}
							// go back to main menu
							case 'x':
							case 'X':
							{
								break;
							}
							default:
							{
								interaction.message("---!");
								continue;
							}
						}

						break;
					}

					clear();
					continue;
				}
			}
			// delete files if needed
			case 'd':
			case 'D':
			{
				clear();
				// in case no files added
				if (interaction.get_size() == 0)
				{
					interaction.message("Нет добавленных файлов!");
					break;
				}
				else
				{
					while (true)
					{
						interaction.menu(fl::Menu::REMOVE);
						getline(std::cin, input);

						switch (interaction.check(input))
						{
							case 'x':
							case 'X':
							{
								break;
							}
							default:
							{
								try
								{
									interaction.remove(interaction.check(input));
									clear();
									continue;
								}
								catch (const std::runtime_error & ex)
								{
									interaction.message(ex.what());
									clear();
									continue;
								}
							}
						}

						clear();
						break;
					}
				}

				break;
			}
			case 'w':
			case 'W':
			{
				clear();
				// in case no files added
				if (interaction.get_size() == 0)
				{
					interaction.message("Добавьте файлы чтобы записать!");
					break;
				}
				else
				{
					interaction.menu(fl::Menu::WRITE);
					getline(std::cin, input);

					input += ".txt";

					try
					{
						interaction.write(input);
						interaction.message("Файл " + input + " успешно записан!");
						clear();
						break;
					}
					catch (const std::runtime_error & ex)
					{
						interaction.message(ex.what());
					}
				}

				break;
			}
			case 'x':
			case 'X':
			{
				clear();
				std::cout << "Пока!\n";
				exit(EXIT_SUCCESS);
			}
			default:
			{
				clear();
				interaction.message("Неправильный ввод!");
				continue;
			}
		}
		// go back at the start of main loop
		continue;
	}

	return 0;
}