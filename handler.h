#include "structs.h"
#include <stdio.h>

#define MAX_ARG_LEN 200

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

int checkMajorArgumenntValid(char* command, char* argument)
{
	return SUCCESS;
}

int checkArgumentValid(char* command, char* argument)
{
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
		if (checkMajorArgumenntValid(command, argument))
		{
			return WRONG_ARGUMENT_FAILURE;
		}
	}

	return SUCCESS;
}



int commandParserHandler(char* input)
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
			if (checkArgumentValid(command, istr))
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

			if (checkArgumentValid(command, istr))
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
