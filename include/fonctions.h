
char* lirestr(FILE *file){
	char temp[100];
	fgets(temp,100,file);
	if(char *index = strchr(temp,'\n')) *index = 0;
	char *str = (char*)malloc(sizeof(char)*(strlen(temp)+1));
	strcpy(str,temp);
	return str;}

int convertir(const char *str, const char *filter){
	int n;
	sscanf(str,filter,&n);
	return n;}

char* copier(const char *str){
	char *strbis;
	if(str){
		strbis = (char*)malloc(sizeof(char)*(strlen(str)+1));
		strcpy(strbis,str);}
	else strbis = NULL;
	return strbis;}
