//liste.h par Baptiste Thémine

#ifndef LISTE
#define LISTE
#include <iostream>
using namespace std;
#include <typeinfo>
#define isclass(x) (typeid(x)!=typeid(char) && typeid(x)!=typeid(int) && typeid(x)!=typeid(double))

/** Prototypes de fonctions

 - Opérateurs -
Liste& operator=(const Liste<Type>&);
Liste operator+(const Liste<Type>&)const;
Liste& operator+=(const Liste<Type>&);
bool operator==(const Liste<Type>&)const;
bool operator!=(const Liste<Type>&)const;
friend ostream& operator<<(ostream&, const Liste<Type>&);
Type& operator[](const char*);
const Type& operator[](const char*)const;

 - Modificateurs -
void push(const Type&);
Type pop(int);
void sort();
void rsort();
void clear();

 - Accesseurs -
Type& front();
const Type& front()const;
Type& back();
const Type& back()const;
Type& at(int);
const Type& at(int)const;

 - Fonctions foreach -
int foreach()const;
Type& get();
const Type& get()const;
void reset()const;

 - Fonctions de test -
int size()const;
int indexOf(const char*)const;
int indexOf(const char*,int)const;
bool contains(const Type&)const;

**/

//fonctions.h
char* copier(const char*);

template <typename Type>
class Liste{
private :
	//Liste chaînée
	typedef struct LinkedList{
		Type data;
		char *label;
		struct LinkedList *next;
	}LinkedList;
	LinkedList *liste;
	int listsize;
	//Variables foreach
	mutable LinkedList *iterator;
	mutable int index;
	
	//Fonctions de liste chaînée
	LinkedList* parcourir(LinkedList *maillon)const{
		if(maillon->next==NULL) return maillon;
		else return parcourir(maillon->next);}
	
	LinkedList* parcourir(LinkedList *maillon, int n)const{
		if(maillon->next==NULL || n<=0) return maillon;
		else return parcourir(maillon->next,n-1);}
	
	void inserer(LinkedList *&maillon1, LinkedList *&maillon2){
		LinkedList *temp = maillon1;
		maillon1 = maillon2;
		maillon1->next = temp;}
	
	void liberer(LinkedList *maillon){
		if(maillon){
			liberer(maillon->next);
			free(maillon->label);
			delete maillon;}}

public :
	//Constructeurs & destructeur
	Liste():liste(NULL),iterator(NULL),listsize(0),index(0){}
	
	Liste(const Liste<Type> &liste){
		this->liste = NULL;
		iterator = NULL;
		listsize = 0;
		index = 0;
		while(liste.foreach()) push(liste.get());}
	
	~Liste(){
		liberer(liste);
		liste = NULL;
		iterator = NULL;
		listsize = 0;
		index = 0;}
	
	//Opérateurs
	Liste& operator=(const Liste<Type> &liste){
		this->~Liste();
		while(liste.foreach()) push(liste.get());
		return *this;}
	
	Liste operator+(const Liste<Type> &add)const{
		Liste liste = *this;
		while(add.foreach()) liste.push(add.get());
		return liste;}
	
	Liste& operator+=(const Liste<Type> &liste){
		while(liste.foreach()) push(liste.get());
		return *this;}
	
	bool operator==(const Liste<Type> &liste)const{
		if(liste.size()!=listsize) return false;
		while(liste.foreach() && this->foreach()){
			if(!(liste.get()==this->get())){
				liste.reset();
				this->reset();
				return false;}}
		liste.reset();
		this->reset();
		return true;}
	
	bool operator!=(const Liste<Type> &liste)const{
		if(liste.size()!=listsize) return true;
		while(liste.foreach() && this->foreach()){
			if(!(liste.get()==this->get())){
				liste.reset();
				this->reset();
				return true;}}
		liste.reset();
		this->reset();
		return false;}
	
	friend ostream& operator<<(ostream &os, const Liste<Type> &liste){
		if(liste.size()>0 && isclass(liste.front())){
			os << "----------------------------------------" << endl << endl;
			while(liste.foreach()){
				os << liste.get() << endl;
				os << "----------------------------------------" << endl << endl;}}
		else{
			while(liste.foreach()) os << liste.get() << " ";
			os << endl;}
		return os;}
	
	Type& operator[](const char *str){
		LinkedList *maillon = liste;
		while(maillon){
			if(maillon->label && !strcmp(maillon->label,str)) return maillon->data;
			maillon = maillon->next;}
		push(Type());
		maillon = parcourir(liste);
		maillon->label = copier(str);
		return maillon->data;}
	
	const Type& operator[](const char *str)const{
		LinkedList *maillon = liste;
		while(maillon){
			if(maillon->label && !strcmp(maillon->label,str)) return maillon->data;
			maillon = maillon->next;}
		push(Type());
		maillon = parcourir(liste);
		maillon->label = copier(str);
		return maillon->data;}
	
	//Modificateurs
	void push(const Type &val){
		listsize++;
		if(liste){
			LinkedList *maillon = parcourir(liste);
			maillon->next = new LinkedList();
			maillon = maillon->next;
			maillon->data = val;
			maillon->label = NULL;
			maillon->next = NULL;}
		else{
			liste = new LinkedList();
			liste->data = val;
			liste->label = NULL;
			liste->next = NULL;}}
	
	Type pop(int n){
		listsize--;
		if(n==0 || liste->next==NULL){
			Type val = liste->data;
			LinkedList *temp = liste;
			liste = liste->next;
			delete temp;
			return val;}
		else{
			LinkedList *maillon = parcourir(liste,n);
			Type val = maillon->next->data;
			LinkedList *temp = maillon->next;
			maillon->next = maillon->next->next;
			delete temp;
			return val;}}
	
	void sort(){
		if(liste){
			LinkedList *next = liste->next;
			LinkedList *sort = liste;
			sort->next = NULL;
			liste = next;
			while(liste){
				next = liste->next;
				bool test=true;
				if(liste->data<sort->data){
					inserer(sort,liste);
					test = false;}
				for(LinkedList *maillon = sort; test; maillon = maillon->next){
					if(maillon->next==NULL || !(liste->data<maillon->data) && liste->data<maillon->next->data){
						inserer(maillon->next,liste);
						test = false;}}
				liste = next;}
			liste = sort;}}
	
	void rsort(){
		if(liste){
			LinkedList *next = liste->next;
			LinkedList *sort = liste;
			sort->next = NULL;
			liste = next;
			while(liste){
				next = liste->next;
				bool test=true;
				if(!(liste->data<sort->data)){
					inserer(sort,liste);
					test = false;}
				for(LinkedList *maillon = sort; test; maillon = maillon->next){
					if(maillon->next==NULL || liste->data<maillon->data && !(liste->data<maillon->next->data)){
						inserer(maillon->next,liste);
						test = false;}}
				liste = next;}
			liste = sort;}}
	
	void clear(){
		this->~Liste();}
	
	//Accesseurs
	Type& front(){
		return liste->data;}
	
	const Type& front()const{
		return liste->data;}
	
	Type& back(){
		return parcourir(liste)->data;}
	
	const Type& back()const{
		return parcourir(liste)->data;}
	
	Type& at(int n){
		return parcourir(liste,n)->data;}
	
	const Type& at(int n)const{
		return parcourir(liste,n)->data;}
	
	//Fonctions foreach
	int foreach()const{
		if(iterator) iterator = iterator->next;
		else iterator = liste;
		if(iterator) index++;
		else index = 0;
		return index;}
	
	Type& get(){
		return iterator->data;}
	
	const Type& get()const{
		return iterator->data;}
	
	void reset()const{
		iterator = NULL;
		index = 0;}
	
	//Fonctions de test
	int size()const{
		return listsize;}
	
	int indexOf(const char *id)const{
		LinkedList *maillon = liste;
		for(int i=0; maillon; i++){
			if(!strcmp(maillon->data.getid(),id)) return i;
			maillon = maillon->next;}
		return -1;}
	
	int indexOf(const char *id, int n)const{
		LinkedList *maillon = liste;
		for(int i=0; maillon; i++){
			if(!strncmp(maillon->data.getid(),id,n)) return i;
			maillon = maillon->next;}
		return -1;}
	
	bool contains(const Type &val)const{
		while(foreach()){
			if(get()==val){
				reset();
				return true;}}
				reset();
		return false;}
};

#endif
