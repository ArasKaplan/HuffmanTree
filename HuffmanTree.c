#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node{
	char harf;
	int freq;
	struct node *left,*right,*next;
};
struct node* insertBeforeRoot(struct node *root,struct node *ins){
	ins->next=root;
	root=ins;
	return root;//root un arkas�na yeni bir node geldi�inde root de�i�ece�i  i�in--
	//-- farkl� bir fonksiyon gerekiyor (returnu olan bir fonksiyon)
}

struct node* pullNode(struct node *prev){//elinize al�nacak node un bir �ncesi g�nderilecek
	struct node *temp;//�nceki node iki ilerideki node a ba�lan�r ve eldeki node un ili�i�i kesilir
	temp=prev->next;
	prev->next=prev->next->next;
	return temp; //node elinize d�ner
}

void insertNode(struct node *prev,struct node *ins){//eldeki node ve istenilen adresin bir �ncesi g�nderilir
	ins->next=prev->next;
	prev->next=ins;//bir �nceki adresin sonras� ve kendisi aras�na eldeki node konur
}


struct node* addNode(char harf){
	struct node *temp;
	temp=(struct node*)malloc(sizeof(struct node));
	temp->harf=harf;
	temp->next=NULL;
	temp->freq=1;
	temp->right=NULL;
	temp->left=NULL;
	return temp;
}

void search(struct node *root,char harf){
	struct node *temp;
	/*if((harf>='A')&&(harf<='Z')){//b�y�k k���k harf ayr�m� istenmiyorsa comment ayra�lar�n� kald�r�n
		harf=harf+32;
	}*/
	while(root!=NULL){
		if(root->harf==harf){
			root->freq++;
			return;
		}
		temp=root;
		root=root->next;
	}//harf bulunduysa maine d�n�lecek bulunmad�ysa while'�n ��k���nda yeni node eklenecek
	temp->next=addNode(harf);
}

struct node* insertionSort(struct node *root){//Yeni bir liste a�maya gerek yok!(E�er eleman �ncekinden k���kse a�a��daki i�lemler yap�ld���nda en fazla kendisinden bir �nceye kadar gelebilir.)
	struct node *main,*comp,*mainb;  //Bundan dolay� da yeni liste a�maya gerek yoktur.
	if(root==NULL || root->next==NULL)//�lk eleman yoksa ya da tek elemanl� bir liste ise de�i�im olmayacakt�r
		return root;
	main=root->next;
	mainb=root;
	comp=root;
	while(main!=NULL){//S�ralama son elemana kadar devam edecek
		if(main->freq<mainb->freq){//Singular linked list'te geri gitme olmad��� i�in, e�er eleman �nceki elmandan k���kse ba�tan ba�layarak kar��la�t�rma yap�l�r
			if(main->freq<root->freq){//Alttaki while ilk elemanla kar��la�t�rma yapmad��� i�in--
				main=pullNode(mainb);//--burada �zel olarak root ile kar��la�t�rma yap�l�yor
				root=insertBeforeRoot(root,main);
				main=mainb;//main g�ncellemesi olmazsa d�ng� zaten s�ralanm�� k�s�mdan devam eder
			}
			else{
			comp=root;
			while(main->freq>comp->next->freq){//�nceki eleman� tutmak yerine bir ilerideki elemana bak�yoruz
				comp=comp->next;//S�ray� bozan eleman�n b�y�k oldu�u elemanlar ge�ilir
			}
			main=pullNode(mainb);//whiledan ��k�ld��� anda elimizde olan node mainden k���k--
			insertNode(comp,main);//--bir ilerisi ise mainden b�y�kt�r
			main=mainb;//main g�ncellemesi olmazsa d�ng� zaten s�ralanm�� k�s�mdan devam eder
			}
		}
		mainb=main;
		main=main->next;
	}
	return root;
}
struct node* makeTree(struct node *root){
	struct node *temp,*comp,*first,*sec,*nw;
	temp=root;
	int counter=0;
	while(temp!=NULL){
		comp=root;
		if(counter==0){//ilk eleman al�n�rken sadece first adl� pointerda tutulur
			first=temp;
			temp=temp->next;
		}
		else if(counter==1){//2. eleman da al�n�nca  yeni node a��l�r ve yeni node un u�lar�na eklenir
			comp=root;
			sec=temp;
			nw=addNode('\0');
			nw->freq=first->freq+sec->freq;
			nw->left=first;
			nw->right=sec;
			while(comp->next!=NULL && nw->freq>=comp->next->freq ){//ard�ndan sortlanm�� listeye eklenir
				comp=comp->next;
			}
			insertNode(comp,nw);
			root=temp->next;
			temp=temp->next;
			first->next=NULL;
			sec->next=NULL;
		}
		counter++;
		counter=counter%2;
		}
		return root;
	}

 

void addToArray(struct node *root,int index,struct node array[],int *counter){
	array[index]=*root;
	*counter=*counter+1;
	if(root->left!=NULL)
		addToArray(root->left,2*index+1,array,counter);//indexleme i�lemleri soldakiler 2*index+1
	if(root->right!=NULL)
		addToArray(root->right,2*index+2,array,counter);//sa�dakiler 2*index+2
}

void printTree(struct node array[],int counter){
	int sifir=0;
	int z;
	int i=0;
	int x=1;
	while(i<counter || i<pow(2,x)-1){//counter= toplam node say�s�//
		if(array[i].freq==-1){
			printf("NULL");
			i++;
		}		
		else if(array[i].harf=='\0'){
		if(array[i].freq==0)
		printf(" ");//NULL yerine 0 ya da ' ' koyarsan�z tree yi bast�r�nca daha g�zel g�rebilirsiniz
		else
		printf("%d ",array[i].freq);
		i++;
		}
		else{
			if(array[i].harf==' ')
			printf("%dBosluk ",array[i].freq);
			else{
				printf("%d%c ",array[i].freq,array[i].harf);
			}
			i++;
		}
		if(i==pow(2,x)-1){//tree nin bulundu�u level�n�n son eleman�na kadar yazmas� i�in ve yeni sat�ra ge�me zaman�n� bulmak i�in
			printf("\n");
			if(i>counter)
			x--;
			x++;
		}
	}
}
int main(){
	printf("Enter the text: ");
	char temp[100];
	gets(temp);
	struct node *root;
	int i;
	root=addNode(temp[0]);
	for(i=1;i<strlen(temp);i++){//ilk eleman �nceden eklendi
		search(root,temp[i]);
	}
	struct node *tmp;
	tmp=root;
	printf("Before insertion sort:\n");//Bast�rma i�lemleri
	while(tmp!=NULL){
		if(tmp->harf==' '){
			printf("Bosluk->%d ",tmp->freq);
			tmp=tmp->next;
		}
		else{
		printf("% c->%d ",tmp->harf,tmp->freq);
		tmp=tmp->next;
	}
}
	root=insertionSort(root);
	tmp=root;
	printf("\nAfter insertion sort:\n");//Bast�rma i�lemleri
	while(tmp!=NULL){
		if(tmp->harf==' '){
			printf("Bosluk->%d ",tmp->freq);
			tmp=tmp->next;
		}
		else{
		printf("% c->%d ",tmp->harf,tmp->freq);
		tmp=tmp->next;
	}
	}
	root=makeTree(root);
	printf("\n \n");
	int counter=0;
	struct node *array=(struct node*)malloc(sizeof(struct node)*100);//Level order traverse k�sm�n� yapamad���m i�in ve internetten kopyalamak istemedi�im i�in b�yle bir ��z�m buldum
	addToArray(root,0,array,&counter);//heap tree kurallar�na g�re array e indeksleme yapt�m
	printTree(array,counter);
	printf("End of operations. Press any key to exit");
	getch();
	return 0;
}
