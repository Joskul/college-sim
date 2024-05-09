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
	action p1 = {
		.message = "Fight the god.",
		.sMessage = "You fought with the god.",
		.energy = 20,
		.success = 1,
		.dest = NULL};
	action p2 = {
		.message = "RUN!!!",
		.sMessage = "You ran away from the god.",
		.energy = 5,
		.success = 2,
		.dest = NULL};
	action pathList[] = {p2, p1};
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
		.aCount = 2,
		.actions = pathList,
		.timeout = 5};

	action p = renderEvent(e);

	renderAction(p);
	return 0;
}