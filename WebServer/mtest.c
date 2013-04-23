#include <stdio.h>

int main(int argc, char* argv){

	if(argc != 2){
		printf("Improper usage\n");
		return(1);
	}

	system("ls -l");
}
