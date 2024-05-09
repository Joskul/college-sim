#include "event.h"
#include "render.h"
#include <stddef.h>
#include <stdio.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

int main()
{
	path p1 = {
		.message = "Fight the god.",
		.sMessage = "You fought with the god",
		.energy = 20,
		.success = 1,
		.dest = NULL};
	path p2 = {
		.message = "RUN!!!",
		.sMessage = "You ran away from the god.",
		.energy = 5,
		.success = 2,
		.dest = NULL};
	path pathList[] = {p1, p2};
	event e = {
		.scene = "                                          \n"
				 "            @@@@@@@@@@@@@@@@@@@           \n"
				 "          @@@@@@@@@@@@@@@@@@@@@@@@        \n"
				 "       @@@@@@@@@@@@@@@@@@@@@@@@@@@@       \n"
				 "      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@     \n"
				 "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    \n"
				 "   @@@@@@@@@@@@@@#*#%@@@@@@@@@@@@@@@@@@   \n"
				 "  @@@@@@@@@@%-..         :%@@@@@@@@@@@@   \n"
				 "  @@@@@@@@@%.            ..#@@@@@@@@@@@@% \n"
				 "  @@@@@@@@@#..=@@@+    -%@@#@@@@@@@@@@@@  \n"
				 "   @@@@@@@@=+=.       ...-=#@@@@@@@@@@@   \n"
				 "   %@@@@@@-=#%@%#+:...*::::-*@@@@@@@@@%   \n"
				 "    @@@@@@@#-++#%#+#%@%#%#**=+@@@@@@@@    \n"
				 "     @@@@@.#+::-::*-.:%-.-=..+@@@@@@      \n"
				 "      +***.   ....   .+@%-..*@@@@@@       \n"
				 "      *:@%.   .+:*@*+%@@@@@@@@@@@@@       \n"
				 "       :#%.  .:....:+*#@@@@@@@@@@@@       \n"
				 "       .:#.  .@@@*+-=-*#@@@@@@@@#@        \n"
				 "        %@#.  :-++------*@@@@@@           \n"
				 "          @%-...  ....+@@@@@@@@           \n"
				 "           @@%=...:#@@%*:-@@@@            \n"
				 "             @@@*:-#@@%%@@@@              \n"
				 "               @@@@@@@@@@@@               \n"
				 "                   @@@@@                  \n"
				 "                                          \n",
		.message = "You have encountered the god, what would you do?",
		.choicesCount = 2,
		.choices = pathList,
		.timeout = 5};

	path p = renderEvent(e);

	if (p.success <= 1)
	{
		printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, p.sMessage);
	}
	else if (p.success <= 2)
	{
		printf("%s", p.sMessage);
	}
	else
	{
		printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, p.sMessage);
	}
	return 0;
}