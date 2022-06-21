#include "structs.h"
#include <stdio.h>

#define MAX_ARG_LEN 200

#define OBJECT_WRONG 0
#define OBJECT_FOLDER 1
#define OBJECT_FILE 2

int checkCommandValid(char* command)
{
    for (size_t i = 0; i < COMMAND_COUNT; i++)
    {
        if (strcmp(allowedCommands[i], command) == 0)
        {
            return SUCCESS;
        }
    }
    
    return FAILURE;
}

int checkMinorArgumentValid(char* command, char* argument)
{
	if (argument[1] == 'l' || argument[1] == 'r')
	{
		if (strlen(argument) == 2)
		{
			if (!strcmp(command, "ls"))
			{
				if (argument[1] != 'l')
					return FAILURE;
			}

			else if (!strcmp(command, "rm"))
			{
				if (argument[1] != 'r')
					return FAILURE;
			}

			else
			{
				return FAILURE;
			}

			return SUCCESS;
		}

		else
		{
			return FAILURE;
		}
	}

	else
		return FAILURE;
}

int checkMajorArgumenntValid(char* argument, Folder* RootFolder, Folder* CurrentFolder, Folder* ResultFolder, File* ResultFile)
{
	Folder* ptr;
	char* path = (char*) malloc(MAX_COMMAND_LEN);

	strcpy(path, argument);
	
	for (size_t i = 0; i < strlen(path); i++)
	{
		if(path[i] == '\n')
		{
			path[i] = '\0';
		}
	}

	if (argument[0] == '/')
	{
		// Абсолютный путь
		ptr = RootFolder;
	}

	else
	{
		// Относительный путь
		ptr = CurrentFolder;
	}

	char *sep = "/", *istr;
	istr = strtok(path, sep);

	int foundFlag;
	while (istr != NULL)
	{	
		foundFlag = 1;
		for (size_t i = 0; i < CurrentFolder->folders_count_cur; i++)
		{
			if (!strcmp(CurrentFolder->folders[i].filename, istr))
			{
				foundFlag = 0;
				ptr = &CurrentFolder->folders[i];
				break;
			}
		}
		
		if(foundFlag)
		{
			int isFileFlag = 0;
			for (size_t i = 0; i < strlen(istr); i++)
			{
				if(istr[i] == '.')
				{
					isFileFlag = 1;
					break;
				}
			}

			if (isFileFlag)
			{
				char* filename = (char*) malloc(filename_lenth + 1);
				char* extension = (char*) malloc(extinsion_lenth + 1);
				int extFlag = 0;

				int writeCount = 0;

				for (size_t i = 0; i < strlen(istr); i++) // Отделяем имя файла от расширения
				{
					if (istr[i] == '.')
					{
						extFlag = 1;
						filename[writeCount + 1] = '\0';
						writeCount = 0;
						continue;
					}
					
					if(extFlag)
					{
						filename[writeCount] = istr[i];
					}

					else
					{
						extension[writeCount] = istr[i];
					}

					writeCount++;
				}

				for (size_t i = 0; i < ptr->files_count_cur; i++)
				{
					if (!strcmp(ptr->files[i].filename, filename) && !strcmp(ptr->files[i].extension, extension))
					{
						free(path);
						free(filename);
						free(extension);

						ResultFile = &ptr->files[i];
						return OBJECT_FILE;
					}
				}

				free(filename);
				free(extension);
			}
			
			printf("Cannot resolve %s\n", istr);
			return WRONG_ARGUMENT_FAILURE;
		}

		istr = strtok(NULL, sep);
	}

	free(path);
	ResultFolder = ptr;
	return OBJECT_FOLDER;
}

int checkArgumentValid(char* command, char* argument, Folder* RootFolder, Folder* CurrentFolder, Folder* resultFolder, File* resultFile)
{
	Folder* _ResultFolder;
	File* _ResultFile;

	int iResult;

	if(argument == NULL)
	{
		return WRONG_ARGUMENT_FAILURE;
	}

	if(argument[0] == '-')
	{
		if(checkMinorArgumentValid(command, argument))
		{
			return WRONG_OPTION;
		}
	}

	else
	{
		// Обрабатываем объект
		iResult = checkMajorArgumenntValid(argument, RootFolder, CurrentFolder, _ResultFolder, _ResultFile);
		if (iResult == WRONG_ARGUMENT_FAILURE)
		{
			return WRONG_ARGUMENT_FAILURE;
		}

		if (iResult == OBJECT_FILE)
		{
			resultFile = _ResultFile;
		}

		if (iResult == OBJECT_FOLDER)
		{
			resultFolder = _ResultFolder;
		}
	}
	return SUCCESS;
}



int commandParserHandler(char* input, Folder* RootFolder, Folder* CurrentFolder)
{
	int result = SUCCESS; // Если что-то пойдет не так, то он изменится

	char* sep = " ";
	char* str = (char*) malloc(MAX_COMMAND_LEN), *istr;

	int i = 0; // Счетчик обработанных лексемм
	
	strcpy(str, input);
	istr = strtok(str, sep);

	char* command = (char*) malloc(MAX_COMMAND_LEN);
	char* arg1 = (char*) malloc(MAX_COMMAND_LEN);
	char* arg2 = (char*) malloc(MAX_COMMAND_LEN);

	int optionFlag = 0;

	File* ResultFile = NULL;
	Folder* ResultFolder = NULL;

	while(istr != NULL)
	{
		// Обрабатываем команду/аргумент
		switch (i)
		{
		case 0:
			// команда
            if (checkCommandValid(istr)) // Если команда неправильная
			{
				result = FAILURE;
				goto cleanup;
			}
			strcpy(command, istr);
			break;
		
		case 1:
			// аргумент 1
			if (checkArgumentValid(command, istr, RootFolder, CurrentFolder, ResultFolder, ResultFile))
			{
				result = WRONG_OPTION;
				goto cleanup;
			}

			if (istr[0] == '-')
				optionFlag = 1;

			strcpy(arg1, istr);
			break;

		case 2:
			// аргумент 2
			if (!optionFlag)
			{
				result = WRONG_ARGUMENT_FAILURE;
				goto cleanup;
			}

			if (checkArgumentValid(command, istr, RootFolder, CurrentFolder, ResultFolder, ResultFile))
			{
				result = WRONG_OPTION;
				goto cleanup;
			}
			
			strcpy (arg2, istr);
			break;
		
		default:
			break;
		}

		i++;
		istr = strtok(NULL, sep); // Выделяем следующую часть
	}

	printf("%s, %s, %s", command, arg1, arg2);

	cleanup: free(str);
	free(command);
	free(arg1);
	free(arg2);
	
	return result;
}