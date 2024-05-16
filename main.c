#include "event.h"
#include "render.h"
#include "eventLoader.h"

int main()
{
	// action p1 = {
	// 	.message = "Fight the god.",
	// 	.sMessage = "You fought with the god.",
	// 	.energy = 20,
	// 	.success = 1,
	// 	.dest = NULL};
	// action p2 = {
	// 	.message = "RUN!!!",
	// 	.sMessage = "You ran away from the god.",
	// 	.energy = 5,
	// 	.success = 2,
	// 	.dest = NULL};
	// action pathList[] = {p2, p1};
	// event e = {
	// 	.scene = "                                          \n"
	// 			 "            @@@@@@@@@@@@@@@@@@@           \n"
	// 			 "          @@@@@@@@@@@@@@@@@@@@@@@@        \n"
	// 			 "       @@@@@@@@@@@@@@@@@@@@@@@@@@@@       \n"
	// 			 "      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@     \n"
	// 			 "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    \n"
	// 			 "   @@@@@@@@@@@@@@#*#%@@@@@@@@@@@@@@@@@@   \n"
	// 			 "  @@@@@@@@@@%-..         :%@@@@@@@@@@@@   \n"
	// 			 "  @@@@@@@@@%.            ..#@@@@@@@@@@@@% \n"
	// 			 "  @@@@@@@@@#..=@@@+    -%@@#@@@@@@@@@@@@  \n"
	// 			 "   @@@@@@@@=+=.       ...-=#@@@@@@@@@@@   \n"
	// 			 "   %@@@@@@-=#%@%#+:...*::::-*@@@@@@@@@%   \n"
	// 			 "    @@@@@@@#-++#%#+#%@%#%#**=+@@@@@@@@    \n"
	// 			 "     @@@@@.#+::-::*-.:%-.-=..+@@@@@@      \n"
	// 			 "      +***.   ....   .+@%-..*@@@@@@       \n"
	// 			 "      *:@%.   .+:*@*+%@@@@@@@@@@@@@       \n"
	// 			 "       :#%.  .:....:+*#@@@@@@@@@@@@       \n"
	// 			 "       .:#.  .@@@*+-=-*#@@@@@@@@#@        \n"
	// 			 "        %@#.  :-++------*@@@@@@           \n"
	// 			 "          @%-...  ....+@@@@@@@@           \n"
	// 			 "           @@%=...:#@@%*:-@@@@            \n"
	// 			 "             @@@*:-#@@%%@@@@              \n"
	// 			 "               @@@@@@@@@@@@               \n"
	// 			 "                   @@@@@                  \n"
	// 			 "                                          \n",
	// 	.message = "You have encountered the god, what would you do?",
	// 	.aCount = 2,
	// 	.actions = pathList,
	// 	.timeout = 5};

	int numEvents = 0;
	event e = loadEvents("./events", &numEvents)[0];

	action p = renderEvent(e);

	renderAction(p);

	printf("%d Events found", numEvents);
	return 0;
}