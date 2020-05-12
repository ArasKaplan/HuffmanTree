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
	return root;//root un arkasýna yeni bir node geldiðinde root deðiþeceði  için--
	//-- farklý bir fonksiyon gerekiyor (returnu olan bir fonksiyon)
}

struct node* pullNode(struct node *prev){//elinize alýnacak node un bir öncesi gönderilecek
	struct node *temp;//önceki node iki ilerideki node a baðlanýr ve eldeki node un iliþiði kesilir
	temp=prev->next;
	prev->next=prev->next->next;
	return temp; //node elinize döner
}

void insertNode(struct node *prev,struct node *ins){//eldeki node ve istenilen adresin bir öncesi gönderilir
	ins->next=prev->next;
	prev->next=ins;//bir önceki adresin sonrasý ve kendisi arasýna eldeki node konur
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
	/*if((harf>='A')&&(harf<='Z')){//büyük küçük harf ayrýmý istenmiyorsa comment ayraçlarýný kaldýrýn
		harf=harf+32;
	}*/
	while(root!=NULL){
		if(root->harf==harf){
			root->freq++;
			return;
		}
		temp=root;
		root=root->next;
	}//harf bulunduysa maine dönülecek bulunmadýysa while'ýn çýkýþýnda yeni node eklenecek
	temp->next=addNode(harf);
}

struct node* insertionSort(struct node *root){//Yeni bir liste açmaya gerek yok!(Eðer eleman öncekinden küçükse aþaðýdaki iþlemler yapýldýðýnda en fazla kendisinden bir önceye kadar gelebilir.)
	struct node *main,*comp,*mainb;  //Bundan dolayý da yeni liste açmaya gerek yoktur.
	if(root==NULL || root->next==NULL)//Ýlk eleman yoksa ya da tek elemanlý bir liste ise deðiþim olmayacaktýr
		return root;
	main=root->next;
	mainb=root;
	comp=root;
	while(main!=NULL){//Sýralama son elemana kadar devam edecek
		if(main->freq<mainb->freq){//Singular linked list'te geri gitme olmadýðý için, eðer eleman önceki elmandan küçükse baþtan baþlayarak karþýlaþtýrma yapýlýr
			if(main->freq<root->freq){//Alttaki while ilk elemanla karþýlaþtýrma yapmadýðý için--
				main=pullNode(mainb);//--burada özel olarak root ile karþýlaþtýrma yapýlýyor
				root=insertBeforeRoot(root,main);
				main=mainb;//main güncellemesi olmazsa döngü zaten sýralanmýþ kýsýmdan devam eder
			}
			else{
			comp=root;
			while(main->freq>comp->next->freq){//Önceki elemaný tutmak yerine bir ilerideki elemana bakýyoruz
				comp=comp->next;//Sýrayý bozan elemanýn büyük olduðu elemanlar geçilir
			}
			main=pullNode(mainb);//whiledan çýkýldýðý anda elimizde olan node mainden küçük--
			insertNode(comp,main);//--bir ilerisi ise mainden büyüktür
			main=mainb;//main güncellemesi olmazsa döngü zaten sýralanmýþ kýsýmdan devam eder
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
		if(counter==0){//ilk eleman alýnýrken sadece first adlý pointerda tutulur
			first=temp;
			temp=temp->next;
		}
		else if(counter==1){//2. eleman da alýnýnca  yeni node açýlýr ve yeni node un uçlarýna eklenir
			comp=root;
			sec=temp;
			nw=addNode('\0');
			nw->freq=first->freq+sec->freq;
			nw->left=first;
			nw->right=sec;
			while(comp->next!=NULL && nw->freq>=comp->next->freq ){//ardýndan sortlanmýþ listeye eklenir
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
		addToArray(root->left,2*index+1,array,counter);//indexleme iþlemleri soldakiler 2*index+1
	if(root->right!=NULL)
		addToArray(root->right,2*index+2,array,counter);//saðdakiler 2*index+2
}

void printTree(struct node array[],int counter){
	int sifir=0;
	int z;
	int i=0;
	int x=1;
	while(i<counter || i<pow(2,x)-1){//counter= toplam node sayýsý//
		if(array[i].freq==-1){
			printf("NULL");
			i++;
		}		
		else if(array[i].harf=='\0'){
		if(array[i].freq==0)
		printf(" ");//NULL yerine 0 ya da ' ' koyarsanýz tree yi bastýrýnca daha güzel görebilirsiniz
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
		if(i==pow(2,x)-1){//tree nin bulunduðu levelýnýn son elemanýna kadar yazmasý için ve yeni satýra geçme zamanýný bulmak için
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
	for(i=1;i<strlen(temp);i++){//ilk eleman önceden eklendi
		search(root,temp[i]);
	}
	struct node *tmp;
	tmp=root;
	printf("Before insertion sort:\n");//Bastýrma iþlemleri
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
	printf("\nAfter insertion sort:\n");//Bastýrma iþlemleri
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
	struct node *array=(struct node*)malloc(sizeof(struct node)*100);//Level order traverse kýsmýný yapamadýðým için ve internetten kopyalamak istemediðim için böyle bir çözüm buldum
	addToArray(root,0,array,&counter);//heap tree kurallarýna göre array e indeksleme yaptým
	printTree(array,counter);
	printf("End of operations. Press any key to exit");
	getch();
	return 0;
}
