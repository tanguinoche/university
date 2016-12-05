#include <cini.h>

bool commence_par(char chaine[], char motif[]);

int main(int argc, char **argv)
{
	bool b;
	char tab1[]={'b','o','n','j','o','u','r'};
	char tab2[]={'b','o','n','j','o','u','r'};
	
	b=commence_par(tab1, tab2);
	if(b){ printf("ok"); }
	return 0;
}

bool commence_par(char chaine[], char motif[]){
	if(motif[0]!='\0'){
		return false;
	}else{
		if(chaine[0]==motif[0]){
	commence_par(chaine+1, motif+1);
	return true;
}else{
	return false;
}
}
return false;
}
